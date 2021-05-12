#pragma once
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class client
{
public:
	client() :
		socket_(io_service),
		resolver(io_service),
		request_length(0)
	{
	}

	void ConnectToServer(std::string& host, std::string& port);
	void Send(std::vector<std::string>& message);
	void GetReply();

	~client() noexcept
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
	enum { max_length = 1024 };
	boost::asio::io_service io_service;

	tcp::socket socket_;
	tcp::resolver resolver;
	tcp::endpoint ep;

	char request[max_length];
	size_t request_length;
};


