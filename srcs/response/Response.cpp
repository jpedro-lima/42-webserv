/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 22:58:15 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/14 00:18:14 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::~Response(void) {}

Response::Response(void) : _method(this->_initMethods()) {}

mapRequest	Response::_initMethods() {
	mapRequest	map;

	map["GET"] = &Response::getMethod;
	map["POST"] = &Response::postMethod;
	map["PUT"] = &Response::putMethod;
	map["DELETE"] = &Response::deleteMethod;
	map["OPTIONS"] = &Response::optionsMethod;
	map["TRACE"] = &Response::traceMethod;
	return (map);
}

void	Response::call(Request & request, RequestConfig &requestConf) {
	this->_errorMap = requestConf.getErrorPage();
	this->_isAutoIndex = requestConf.getAutoIndex();
	this->_code = request.getRet();
	this->_hostPort.host = requestConf.getHostPort().host;
	this->_hostPort.port = requestConf.getHostPort().port;
	this->_path = requestConf.getPath();
	this->_setupAllowedMethods(requestConf);

	if (this->_method.find(request.getMethod()) == this->_method.end())
		this->_code = 405;
	else if (requestConf.getClientBodyBufferSize() < request.getBody().size())
		this->_code = 413;
	if (this->_code == 405 || this->_code == 413) {
		ResponseHeader	head;
		this->_header = head.notAllowed(requestConf.getAllowedMethods(), this->_code) + "\r\n";
		this->_response = this->_header + this->readHtml(this->_errorMap[this->_code]);
		return ;
	}
	(this->*Response::_method[request.getMethod()])(request, requestConf);

}

int	Response::readContent(void) {
	std::ifstream		file;
	std::stringstream	buffer;

	this->_response = "";
	if (Utils::pathIsFile(this->_path)) {
		file.open(this->_path.c_str(), std::ifstream::in);
		if (file.is_open() == false)
		{
			this->_response = this->readHtml(this->_errorMap[403]);
			return (403);
		}

		buffer << file.rdbuf();
		this->_response = buffer.str();

		file.close();
	} else if (this->_isAutoIndex) {
		buffer << AutoIndexGenerator::getPage(this->_path.c_str(),\
			std::string(this->_hostPort.host), this->_hostPort.port);
		this->_response = buffer.str();
		_type = "text/html";
	} else {
		this->_response = this->readHtml(this->_errorMap[404]);
		return (404);
	}
	return (200);
}

int	Response::writeContent(std::string content) {
	std::ofstream	file;

	if (Utils::pathIsFile(this->_path))
	{
		file.open(this->_path.c_str());
		file << content;
		file.close();
		return (204);
	} else {
		file.open(this->_path.c_str(), std::ofstream::out | std::ofstream::trunc);
		if (file.is_open() == false)
			return (403);
		file << content;
		file.close();
		return (201);
	}
}

std::string	Response::readHtml(const std::string &path) {
	std::ofstream		file;
	std::stringstream	buffer;

	if (!Utils::pathIsFile(path))
		return ("<!DOCTYPE html>\n<html><title>404</title><body>There was an error finding your error page</body></html>\n");

	file.open(path.c_str(), std::ifstream::in);
	if (file.is_open() == false)
		return ("<!DOCTYPE html>\n<html><title>404</title><body>There was an error finding your error page</body></html>\n");
	buffer << file.rdbuf();
	file.close();
	this->_type = "text/html";
	return (buffer.str());
}

void	Response::_setupAllowedMethods(const RequestConfig &requestConf) {
	std::set<std::string>	allowed = requestConf.getAllowedMethods();

	for (mapRequest::iterator it = this->_method.begin(); it != this->_method.end(); it++)	{
		if (allowed.find(it->first) == allowed.end()) {
			this->_method.erase(it);
			it = this->_method.begin();
		}
	}

}

const std::string	&Response::getHeader(void) { return (this->_header);}
const std::string	&Response::getResponse(void) { return (this->_response);}
