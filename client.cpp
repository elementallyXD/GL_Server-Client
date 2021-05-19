#include "client.h"

void client::ConnectToServer(const std::string& host, const std::string& port)
{
	std::cout << "\tCONNECTING TO " << host << ":" << port << std::endl;
	ep = boost::asio::connect(socket_, resolver.resolve(host, port));
	std::cout << "\tSUCCESSFULLY CONNECTED\n" << std::endl;
}

void client::Send(const std::vector<std::string>& message)
{
	char* buf = request;
	for (size_t i = 0; i < message.size(); ++i)
	{
		for (size_t c = 0; c < std::strlen(message[i].c_str()); c++)
			*buf++ = message[i][c];
		*buf++ = ' ';
	}
	*buf++ = '\0';

	request_length = std::strlen(request);
	boost::asio::write(socket_, boost::asio::buffer(request, request_length));

	std::cout << "\tCLIENT MSG SEND TO " << ep.address() << ":" << ep.port() << "\tDATA: " << request << std::endl;
}