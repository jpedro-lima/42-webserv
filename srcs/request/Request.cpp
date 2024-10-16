/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 22:58:08 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/13 01:46:22 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

Request::~Request(void) {}

Request::Request(const std::string& str) :
	_method (""), _version(""), _ret(200), _body(""), _port(80), _path(""), _query(""), _raw(str)
{
	this->resetHeaders();
	this->_env_for_cgi.clear();
	this->parse(str);
	if (this->_ret != 200)
		throw Exceptions::ExceptionRequestParse();
}

std::vector<std::string>	Request::initMethods() {
	std::vector<std::string>	methods;

	methods.push_back("GET");
	methods.push_back("HEAD");
	methods.push_back("POST");
	methods.push_back("PUT");
	methods.push_back("DELETE");
	methods.push_back("OPTIONS");
	methods.push_back("TRACE" );
	return (methods);
}

std::vector<std::string>	Request::methods = Request::initMethods();

Request&	Request::operator=(const Request &request)
{
	this->_headers = request.getHeaders();
	this->_env_for_cgi = request.getEnv();
	this->_method = request.getMethod();
	this->_version = request.getVersion();
	this->_ret = request.getRet();
	this->_body = request.getBody();
	this->_port = request.getPort();
	this->_path = request.getPath();

	return (*this);
}

//GETTERS
const std::map<std::string, std::string>			&Request::getHeaders() const {return this->_headers;}
const std::map<std::string, std::string>			&Request::getEnv() const {return this->_env_for_cgi;}
const std::string									&Request::getMethod() const {return this->_method;}
const std::string									&Request::getVersion() const {return this->_version;}
const int											&Request::getRet() const {return this->_ret;}
const std::string									&Request::getBody() const {return this->_body;}
const int											&Request::getPort() const {return this->_port;}
const std::string									&Request::getPath() const {return this->_path;}
const std::string									&Request::getQuery() const {return this->_query;}
const std::string									&Request::getRaw() const {return this->_raw;}
const std::list<std::pair<std::string, float> >		&Request::getLang() const {return this->_lang;}


//SETTERS
void	Request::setBody(const std::string& str) {
	char	strip[] = {'\n', '\r'};

	this->_body.assign(str);
	for (int i = 0; i < 4; i++)
		if (this->_body.size() > 0 && this->_body[this->_body.size() - 1] == strip[i % 2])
			this->_body.erase(this->_body.length()-1);
		else
			break ;
}

void	Request::setRet(int ret) {this->_ret = ret;}
void	Request::setMethod(const std::string &method) {this->_method = method;}

