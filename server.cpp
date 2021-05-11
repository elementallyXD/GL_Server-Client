#include "server.h"

void session::do_read() 
{
    auto self(shared_from_this());

    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                tcp::endpoint remote_ep = socket_.remote_endpoint();
                
                std::cout << "\tSERVER [CLIENT ID: " << session_id <<"]> GET FROM IP: " << remote_ep.address() << "\tDATA:";
                std::cout.write(data_, length);
                std::cout << std::endl;

                do_write(length);
            }
        });
}

void session::do_write(std::size_t size) 
{
    auto self(shared_from_this());

    boost::asio::async_write(socket_, boost::asio::buffer(data_, size),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                tcp::endpoint remote_ep = socket_.remote_endpoint();
                std::cout << "\tSERVER [CLIENT ID: " << session_id <<"]> SEND TO IP: " << remote_ep.address() << "\tDATA:";
                std::cout.write(data_, length);
                std::cout << std::endl << std::endl;
                
                do_read();
            }
        });
}

void server::do_accept()
{
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
            if (!ec)
            {
                std::make_shared<session>(std::move(socket), ++session_id)->start();
            }

            do_accept();
        });
}
