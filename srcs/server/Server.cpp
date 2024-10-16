/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:53:35 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/16 08:38:14 by joapedr2         ###   ########.fr       */
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
		this->close(socket);
		throw Exceptions::FailedReadClientRequest();
	}
	this->_requests[socket] += std::string(buffer);

}

void	Server::processRequest(int socket, Config *conf) {
 	RequestConfig	requestConf;
 	Response		response;


	if (this->_requests[socket].find("Transfer-Encoding: chunked") != std::string::npos &&
		this->_requests[socket].find("Transfer-Encoding: chunked") < this->_requests[socket].find("\r\n\r\n"))
		this->processChunk(socket);

	if (this->_requests[socket] != "")
	{
		Request			request(this->_requests[socket]);
		
		if (request.getRet() != 200)
			request.setMethod("GET");

		std::cout << "\nRequest :" << std::endl;
		std::cout << YELLOW << _requests[socket] << RESET << std::endl;
		requestConf = conf->getConfigForRequest(this->_listen, request);
		
		response.call(request, requestConf);
		std::cout << "\nResponse :" << std::endl;
		std::cout << MAGENTA << response.getHeader() <<RESET<< std::endl;
 		this->_requests.erase(socket);
 		this->_requests.insert(std::make_pair(socket, response.getResponse()));
 	}
}

void	Server::processChunk(int socket)
{
	std::string	head = this->_requests[socket].substr(0, this->_requests[socket].find("\r\n\r\n"));
	std::string	chunks = this->_requests[socket].substr(this->_requests[socket].find("\r\n\r\n") + 4, this->_requests[socket].size() - 1);
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
	this->_requests[socket] = head + "\r\n\r\n" + body + "\r\n\r\n";
}

//UTILS
void	Server::close(int socket) {
	if (socket > 0)
		::close(socket);
	this->_requests.erase(socket);
}

void	Server::sendResponse(int socket) {
	std::string	str = this->_requests[socket];
	int	size = send(socket, str.c_str(), str.size(), 0);
	if (size == -1) {
		this->close(socket);
		throw Exceptions::ExceptionSendResponse();
	}
	if (size == (int)str.length())
		_requests.erase(socket);
}

void	Server::clear(void) {
	if (this->_fd > 0)
		::close(this->_fd);
	this->_fd = -1;
}

//GET
int			Server::getFd(void) const {return(this->_fd);}
sockaddr_in	Server::getSockAddr(void) const {return(this->_addr);}

void	Server::setRequest(std::pair<int, std::string> newRequest) {this->_requests.insert(newRequest);}
