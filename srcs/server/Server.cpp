/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:53:35 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/07 22:25:24 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::~Server(void) {}

Server::Server(void) {}

Server::Server(t_listen listen) {
	this->_requests.clear();
	this->_fd = 0;
	this->_listen = listen;
	this->_addr.sin_family = AF_INET;
	this->_addr.sin_port = htons(this->_listen.port);
	this->_addr.sin_addr.s_addr = INADDR_ANY;
	if (this->_listen.host != "0.0.0.0" )
		this->_addr.sin_addr.s_addr = inet_addr(this->_listen.host.c_str());
}

void	Server::setup(void)
{
	if ((this->_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		throw Exceptions::ExceptionServerSocket();
	if (bind(this->_fd, (struct sockaddr*)&this->_addr, sizeof(this->_addr)) == -1)
		throw Exceptions::ExceptionServerBind();
	if (listen(this->_fd, 1000) == -1)
		throw Exceptions::ExceptionServerListen();
}

void	Server::readClientRequest(int socket)
{
	char	buffer[RECV_SIZE] = {0};

	if (recv(socket, buffer, RECV_SIZE - 1, 0) == -1) {
		std::cout << "HERE" << std::endl;
		this->close(socket);
		throw Exceptions::FailedReadClientRequest();
	}
	this->_requests[socket] += std::string(buffer);

}

void		Server::processRequest(int socket, Config *conf) {
// 	RequestConfig	requestConf;
// 	Response		response;
// 	std::string		recvd = "";

(void)conf;
	if (_requests[socket].find("Transfer-Encoding: chunked") != std::string::npos &&
		_requests[socket].find("Transfer-Encoding: chunked") < _requests[socket].find("\r\n\r\n"))
		this->processChunk(socket);

// 	if (OUT)
// 	{
// 		if (_requests[socket].size() < 1000)
// 			std::cout << "\nRequest :" << std::endl << "[" << YELLOW << _requests[socket] << RESET << "]" << std::endl;
// 		else
// 			std::cout << "\nRequest :" << std::endl << "[" << YELLOW << _requests[socket].substr(0, 1000) << "..." << _requests[socket].substr(_requests[socket].size() - 10, 15) << RESET << "]" << std::endl;
// 	}

// 	if (_requests[socket] != "")
// 	{
// 		Request			request(_requests[socket]);

// 		if (request.getRet() != 200)
// 			request.setMethod("GET");

// 		requestConf = conf.getConfigForRequest(this->_listen,  request.getPath(), request.getHeaders().at("Host"), request.getMethod(), request);

// 		response.call(request, requestConf);

 		_requests.erase(socket);
		std::string str = "HTTP/1.0 200 OK\r\n\r\nHello World\n";
		_requests.insert(std::make_pair(socket, str));
		
// 		_requests.insert(std::make_pair(socket, response.getResponse()));
// 	}
}

void		Server::processChunk(int socket)
{
	std::string	head = _requests[socket].substr(0, _requests[socket].find("\r\n\r\n"));
	std::string	chunks = _requests[socket].substr(_requests[socket].find("\r\n\r\n") + 4, _requests[socket].size() - 1);
	std::string	subchunk = chunks.substr(0, 100);
	std::string	body = "";
	int			chunksize = strtol(subchunk.c_str(), NULL, 16);
	size_t		i = 0;

	while (chunksize)
	{
		i = chunks.find("\r\n", i) + 2;
		body += chunks.substr(i, chunksize);
		i += chunksize + 2;
		subchunk = chunks.substr(i, 100);
		chunksize = strtol(subchunk.c_str(), NULL, 16);
	}
	_requests[socket] = head + "\r\n\r\n" + body + "\r\n\r\n";
}

//Utils
void	Server::close(int socket) {
	if (socket > 0)
		::close(socket);
	_requests.erase(socket);
}

void	Server::sendResponse(int socket) {
	std::string	str = _requests[socket];
	send(socket, str.c_str(), str.size(), 0);
}

//GET
int			Server::getFd(void) const {return(this->_fd);}
sockaddr_in	Server::getSockAddr(void) const {return(this->_addr);}

