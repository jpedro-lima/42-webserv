/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestUtils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:58:51 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/13 01:57:04 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

std::ostream	&operator<<(std::ostream &out, const Request &request) {
	std::map<std::string, std::string>::const_iterator	it;

	out << "Method : " << request.getMethod() << " |\tHTTP version : ";
	out << request.getVersion() << '\n';
	out << "Port : " << request.getPort() << '\n';
	out << "Path : " << request.getPath() << '\n';

	for (it = request.getHeaders().begin(); it != request.getHeaders().end(); it++)
		out << it->first << ": " << it->second << '\n';

	out << '\n' << "Request body :\n" << request.getBody() << '\n';

	return out;
}

void	Request::resetHeaders() {
	this->_headers.clear();

	this->_headers["Accept-Charsets"] = "";
	this->_headers["Accept-Language"] = "";
	this->_headers["Allow"] = "";
	this->_headers["Auth-Scheme"] = "";
	this->_headers["Authorization"] = "";
	this->_headers["Content-Language"] = "";
	this->_headers["Content-Length"] = "";
	this->_headers["Content-Location"] = "";
	this->_headers["Content-Type"] = "";
	this->_headers["Date"] = "";
	this->_headers["Host"] = "";
	this->_headers["Last-Modified"] = "";
	this->_headers["Location"] = "";
	this->_headers["Referer"] = "";
	this->_headers["Retry-After"] = "";
	this->_headers["Server"] = "";
	this->_headers["Transfer-Encoding"] = "";
	this->_headers["User-Agent"] = "";
	this->_headers["Www-Authenticate"] = "";
	this->_headers["Connection"] = "close";
}

int	Request::parse(const std::string& str) {
	std::string		key;
	std::string		value;
	std::string		line;
	size_t			i(0);

	this->readFirstLine(nextLine(str, i));
	while ((line = nextLine(str, i)) != "\r" && line != "" && this->_ret != 400)
	{
		key = Utils::readKey(line);
		value = Utils::readValue(line);
		if (this->_headers.count(key))
			this->_headers[key] = value;
		if (key.find("Secret") != std::string::npos)
			this->_env_for_cgi[formatHeaderForCGI(key)] = value;
	}
	if (this->_headers["Www-Authenticate"] != "")
		this->_env_for_cgi["Www-Authenticate"] = this->_headers["Www-Authenticate"];
	this->setLang();
	this->setBody(str.substr(i, std::string::npos));
	this->findQuery();
	return (this->_ret);
}

int	Request::readFirstLine(const std::string& str) {
	size_t	i;
	std::string	line;

	i = str.find_first_of('\n');
	line = str.substr(0, i);
	i = line.find_first_of(' ');

	if (i == std::string::npos) {
		this->_ret = 400;
		std::cerr << RED << "RFL no space after method" << RESET << std::endl;
		return 400;
	}
	this->_method.assign(line, 0, i);
	return (this->readPath(line, i));
}

int	Request::readPath(const std::string& line, size_t i) {
	size_t	j;

	if ((j = line.find_first_not_of(' ', i)) == std::string::npos) {
		this->_ret = 400;
		std::cerr << RED << "No PATH / HTTP version" << RESET << std::endl;
		return 400;
	}
	if ((i = line.find_first_of(' ', j)) == std::string::npos)
	{
		this->_ret = 400;
		std::cerr << RED << "No HTTP version" << RESET << std::endl;
		return 400;
	}
	this->_path.assign(line, j, i - j);
	return (this->readVersion(line, i));
}

int	Request::readVersion(const std::string& line, size_t i) {
	if ((i = line.find_first_not_of(' ', i)) == std::string::npos) {
		this->_ret = 400;
		std::cerr << RED << "No HTTP version" << RESET << std::endl;
		return 400;
	}
	if (line[i] == 'H' && line[i + 1] == 'T' && line[i + 2] == 'T' &&
			line[i + 3] == 'P' && line[i + 4] == '/')
		this->_version.assign(line, i + 5, 3);
	if (this->_version != "1.0" && this->_version != "1.1") {
		this->_ret = 400;
		std::cerr << RED << "BAD HTTP VERSION (" << this->_version << ")" << RESET << std::endl;
		return (this->_ret);
	}
	return (this->checkMethod());
}

int	Request::checkMethod() {
	for (size_t i = 0; i < this->methods.size(); i++) {	
		if (this->methods[i] == this->_method)
			return this->_ret;
	}
	std::cerr << RED << "Invalid method requested" << RESET << std::endl;
	this->_ret = 400;
	return (this->_ret);
}

int	Request::checkPort() {
	size_t i = this->_headers["Host"].find_first_of(':');

	if (i == std::string::npos)
		this->_port = 80;
	else
	{
		std::string tmp(this->_headers["Host"], i + 1);
		this->_port = atoi(tmp.c_str());
	}
	return (this->_port);
}

std::string	Request::nextLine(const std::string &str, size_t& i) {
	std::string		ret;
	size_t			j;

	if (i == std::string::npos)
		return "";
	j = str.find_first_of('\n', i);
	ret = str.substr(i, j - i);
	if (ret[ret.size() - 1] == '\r')
		ret.erase(ret.length()-1);
	i = (j == std::string::npos ? j : j + 1);
	return ret;
}

void	Request::setLang() {
	std::vector<std::string>	token;
	std::string					header;
	size_t						i;

	if ((header = this->_headers["Accept-Language"]) != "")
	{
		token = Utils::split(header, ',');
		for (std::vector<std::string>::iterator it = token.begin(); it != token.end(); it++)
		{
			float			weight = 0.0;
			std::string		lang;

			lang = (*it).substr(0, (*it).find_first_of('-'));
			Utils::strip(lang, ' ');
			if ( (i = lang.find_last_of(';') ) != std::string::npos) {
				weight = atof( (*it).substr(i + 4).c_str() );
			}
			lang.resize(i > 2 ? 2 : i);
			this->_lang.push_back(std::pair<std::string, float>(lang, weight));
		}
		this->_lang.sort(Request::compareFunction);
	}
}

void	Request::stripAll() {
	Utils::strip(this->_method, '\n');
	Utils::strip(this->_method, '\r');
	Utils::strip(this->_method, ' ');
	Utils::strip(this->_version, '\n');
	Utils::strip(this->_version, '\r');
	Utils::strip(this->_version, ' ');
	Utils::strip(this->_path, '\n');
	Utils::strip(this->_path, '\r');
	Utils::strip(this->_path, ' ');
}

void	Request::findQuery() {
	size_t		i;

	i = this->_path.find_first_of('?');
	if (i != std::string::npos)
	{
		this->_query.assign(this->_path, i + 1, std::string::npos);
		this->_path = this->_path.substr(0, i);
	}
}

std::string	Request::formatHeaderForCGI(std::string& key) {
//	to_upper(key);
	std::transform(key.begin(), key.end(), key.begin(), ::toupper);
	for (size_t i = 0 ; i < key.size() ; i++) {
		if (key[i] == '-')
			key[i] = '_';
	}
	return "HTTP_" + key;
}

bool Request::compareFunction(const std::pair<std::string, float> first, const std::pair<std::string, float> second) {
  return ( first.second > second.second );
}
