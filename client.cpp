#include "client.h"

void client::ConnectToServer(char* host, char* port) 
{
	const unsigned int port_number = std::atoi(port);
	
	if (port_number > 0 && port_number < 65536)
		boost::asio::connect(socket_, resolver.resolve(host, port));
	else {
		throw std::runtime_error("Error: Invalid Port.\n");
	}
}

void client::Send() 
{
	std::cout << "CLIENT> Enter message: ";

	std::cin.getline(request, max_length);
	request_length = std::strlen(request);
	boost::asio::write(socket_, boost::asio::buffer(request, request_length));
}

void client::GetReply()
{
	char reply[max_length];

	size_t reply_length = boost::asio::read(
		socket_,
		boost::asio::buffer(reply, request_length)
	);

	std::cout << "CLIENT> Reply is: ";
	std::cout.write(reply, reply_length);
	std::cout << std::endl;
}