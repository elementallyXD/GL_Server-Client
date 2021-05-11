#pragma once
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class session : public std::enable_shared_from_this<session>
{
public:
    session(tcp::socket socket, const unsigned int& id):
        socket_(std::move(socket)),
        session_id(id)
    {
    }

    void start()
    {
        do_read();
    }

    ~session() noexcept
    {
        boost::system::error_code ec;

        if (socket_.is_open()) 
        {
            socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
            socket_.close(ec);
            if (ec) {
                std::cerr << "Close socket error: " << ec.message() << std::endl;
            }
        }
    }

private:
    void do_read();
    void do_write(std::size_t size);

    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length];
    unsigned int session_id;
};

class server
{
public:
    server(boost::asio::io_context& io_context, const unsigned int port) : 
        acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), 
        session_id(0)
    {
        do_accept();
    }

private:
    void do_accept();
    
    tcp::acceptor acceptor_;
    unsigned int session_id;
};