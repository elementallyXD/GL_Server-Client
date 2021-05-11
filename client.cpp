#include "client.h"

void client::ConnectToServer(char* host, char* port) 
{
	const unsigned int port_number = std::atoi(port);
	std::cout << "CONNECT TO " << host << ":" << port_number << std::endl;
	if (port_number > 0 && port_number < 65536) 
	{
		ep = boost::asio::connect(socket_, resolver.resolve(host, port));
		std::cout << "SUCCESSFULLY CONNECTED" << std::endl;
	}
	else {
		std::cout << "UNABLE TO CONNECT" << std::endl;
		throw std::runtime_error("Error: Invalid Port. Port must be greter than 0 and less than 65536\n");
	}
}

void client::Send() 
{
	std::cout << "CLIENT> SEND MSG: ";
	std::cin.getline(request, max_length);
	
	request_length = std::strlen(request);
	boost::asio::write(socket_, boost::asio::buffer(request, request_length));
	
	std::cout << "CLIENT> MSG SEND TO " << ep.address() << ":" << ep.port() << "\tDATA: " << request << std::endl;
}

void client::GetReply()
{
	char reply[max_length];

	size_t reply_length = boost::asio::read(
		socket_,
		boost::asio::buffer(reply, request_length)
	);

	std::cout << "CLIENT> REPLY: ";
	std::cout.write(reply, reply_length);
	std::cout << std::endl;
}