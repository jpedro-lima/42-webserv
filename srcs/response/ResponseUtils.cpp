/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseUtils.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:26:36 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/15 17:41:38 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

void	Response::getMethod(Request & request, RequestConfig & requestConf) {
	ResponseHeader	head;

	if (requestConf.getCgiPass() != "") {
		CgiHandler	cgi(request, requestConf);
		size_t		i = 0;
		size_t		j = this->_response.size() - 2;

		this->_response = cgi.executeCgi(requestConf.getCgiPass());
		while (this->_response.find("\r\n\r\n", i) != std::string::npos || this->_response.find("\r\n", i) == i)
		{
			std::string	str = this->_response.substr(i, this->_response.find("\r\n", i) - i);
			if (str.find("Status: ") == 0)
				this->_code = std::atoi(str.substr(8, 3).c_str());
			else if (str.find("Content-type: ") == 0)
				_type = str.substr(14, str.size());
			i += str.size() + 2;
		}
		while (this->_response.find("\r\n", j) == j)
			j -= 2;
		this->_response = this->_response.substr(i, j - i);
	}
	else if (this->_code == 200)
		this->_code = readContent();
	else
		this->_response = this->readHtml(_errorMap[this->_code]);
	if (this->_code == 500)
		this->_response = this->readHtml(_errorMap[this->_code]);

	this->_header = head.getHeader(this->_response.size(), _path, this->_code, _type, requestConf.getContentLocation(), requestConf.getLang()) + "\r\n";
	this->_response = this->_header + this->_response;
}

void	Response::headMethod(Request & request, RequestConfig & requestConf) {
	(void)request;
	ResponseHeader	head;
	
	this->_code = readContent();
	this->_header = head.getHeader(this->_response.size(), _path, this->_code, _type, requestConf.getContentLocation(), requestConf.getLang()) + "\r\n";
	this->_response = this->_header;
}

void	Response::postMethod(Request & request, RequestConfig & requestConf) {
	ResponseHeader	head;

	if (requestConf.getCgiPass() != "")
	{
		CgiHandler	cgi(request, requestConf);
		size_t		i = 0;
		size_t		j = this->_response.size() - 2;

		this->_response = cgi.executeCgi(requestConf.getCgiPass());
		while (this->_response.find("\r\n\r\n", i) != std::string::npos || this->_response.find("\r\n", i) == i)
		{
			std::string	str = this->_response.substr(i, this->_response.find("\r\n", i) - i);
			if (str.find("Status: ") == 0)
				this->_code = std::atoi(str.substr(8, 3).c_str());
			else if (str.find("Content-Type: ") == 0)
				_type = str.substr(14, str.size());
			i += str.size() + 2;
		}
		while (this->_response.find("\r\n", j) == j)
			j -= 2;

		this->_response = this->_response.substr(i, j - i);
	} else {
		this->_code = 204;
		this->_response = "";
	}
		
	if (this->_code == 500)
		this->_response = this->readHtml(this->_errorMap[this->_code]);
	this->_header = head.getHeader(this->_response.size(), this->_path, this->_code, _type, requestConf.getContentLocation(), requestConf.getLang()) + "\r\n";
	this->_response = this->_header + this->_response;
}


void	Response::putMethod(Request & request, RequestConfig &requestConf) {
	ResponseHeader	head;
	std::string		content;

	content = request.getBody();
	this->_response = "";
	this->_code = writeContent(content);
	if (this->_code != 201 && this->_code != 204)
		this->_response = this->readHtml(this->_errorMap[this->_code]);
	this->_header = head.getHeader(this->_response.size(), this->_path, this->_code, _type, requestConf.getContentLocation(), requestConf.getLang()) + "\r\n";
	this->_response = this->_header + this->_response;
}


void	Response::deleteMethod(Request & request, RequestConfig & requestConf) {
	ResponseHeader	head;
	(void)request;

	this->_response = "";
	if (Utils::pathIsFile(this->_path))
	{
		if (remove(this->_path.c_str()) == 0)
			this->_code = 204;
		else
			this->_code = 403;
	}
	else
		this->_code = 404;
	if (this->_code == 403 || this->_code == 404)
		this->_response = this->readHtml(this->_errorMap[this->_code]);
	this->_header = head.getHeader(this->_response.size(), this->_path, this->_code, _type, requestConf.getContentLocation(), requestConf.getLang()) + "\r\n";
	this->_response = this->_header + this->_response;
}

void	Response::optionsMethod(Request & request, RequestConfig & requestConf) {
	ResponseHeader	head;
	(void)request;

	this->_code = readContent();
	this->_header = head.getHeader(this->_response.size(), this->_path, this->_code, _type, requestConf.getContentLocation(), requestConf.getLang()) + "\r\n";
	this->_response = this->_header;
}

void	Response::traceMethod(Request & request, RequestConfig & requestConf) {
	(void)requestConf;
	this->_response = request.getRaw();
}