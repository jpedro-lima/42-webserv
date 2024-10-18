/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestConfig.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:54:31 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/17 12:27:00 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestConfig.hpp"

RequestConfig::~RequestConfig(void) {}

RequestConfig::RequestConfig(void) {}

RequestConfig::RequestConfig(ConfigServer &config, Request &request, \
		const std::string &path,  const std::string &method, std::string &locationName):
	_error_page(config.getErrorPages()),
	_client_body_buffer_size(config.getBufferSize()),
	_cgi_param(config.getCGIParam()),
	_cgi_pass(config.getCGIPass()),
	_allowed_methods(config.getAllowedMethods()),
	_lang(""),
	_autoindex(config.getAutoIndex()),
	_redirect(config.getRedirect())
{
	std::string	root = config.getRoot();
	std::string	ret;

	std::vector<std::string> conf_index = config.getIndex();
	for (std::vector<std::string>::iterator it = conf_index.begin();\
		it != conf_index.end(); it++) {
		std::vector<std::string>::iterator it2 = _index.begin();
		for (it2 = _index.begin(); it2 != _index.end(); it2++) {
				if (*it == *it2)
					break;
			}
			if (it2 == _index.end())
				_index.push_back(*it);
	}
	if (locationName[0] != '*') {
		ret = root + path.substr(locationName.length());
		this->_contentLocation = Utils::removeAdjacentSlashes(path.substr(locationName.length()));
	}
	else {
		ret = root + path;
		this->_contentLocation = Utils::removeAdjacentSlashes(path);
	}
	this->_path = Utils::removeAdjacentSlashes(ret);
	std::string indexPath;
	if (!Utils::pathIsFile(this->_path) && method == "GET") {
		if ((indexPath = this->addIndex(request)) != "") {
			config = config.getLocationForRequest(indexPath, locationName);
			this->_cgi_param = config.getCGIParam();
			this->_cgi_pass = config.getCGIPass();
		}
	}
}

// GETTERS
const std::string							&RequestConfig::getContentLocation() const {return (this->_contentLocation);}
const std::string							&RequestConfig::getPath() const {return (this->_path);}
const std::map<int, std::string>			&RequestConfig::getErrorPage() const {return (this->_error_page);}
const unsigned long							&RequestConfig::getClientBodyBufferSize() const {return (this->_client_body_buffer_size);}
const std::map<std::string, std::string>	&RequestConfig::getCgiParam() const {return (this->_cgi_param);}
const std::string							&RequestConfig::getCgiPass() const {return (this->_cgi_pass);}
const std::string							&RequestConfig::getLang() const {return (this->_lang);}
const std::set<std::string>					&RequestConfig::getAllowedMethods() const {return (this->_allowed_methods);}
const t_listen								&RequestConfig::getHostPort() const {return (this->_hostPort);}
const bool  								&RequestConfig::getAutoIndex() const {return (this->_autoindex);}
const std::pair<int, std::string>			&RequestConfig::getRedirect() const {return (this->_redirect);}

//SETTERS
void	RequestConfig::setPath(int code) {
	this->_path = this->_error_page[code];
}
void	RequestConfig::setPath(const std::string &path) {this->_path = path;}
void	RequestConfig::setContentLocation(const std::string &path) {this->_contentLocation = path;}
void	RequestConfig::setHostPort(const t_listen listen) {this->_hostPort = listen;}

std::string	RequestConfig::addIndex(Request& request) {
	std::vector<std::string>::iterator							it;
	std::list<std::pair<std::string, float> >::const_iterator	lang;
	std::string													path;

	it = this->_index.begin();
	while(it != this->_index.end()) // Check with language prefs
	{
		for (lang = request.getLang().begin(); lang != request.getLang().end(); lang++)
		{
			path = this->_path;
			if (path[path.size() - 1] != '/')
				path += "/";
			if ((*it).find('.') != (*it).npos)
				path += (*it).substr(0, (*it).find_last_of('.') + 1) + lang->first + (*it).substr((*it).find_last_of('.'));
			if (Utils::pathIsFile(path))
			{
				this->_path = path;
				if (this->_contentLocation.size() && this->_contentLocation[this->_contentLocation.size() - 1] != '/')
					this->_contentLocation += "/";
				if ((*it).find('.') != (*it).npos)
					this->_contentLocation += (*it).substr(0, (*it).find_last_of('.') + 1) + lang->first + (*it).substr((*it).find_last_of('.'));
				return this->_path;
			}
		}
		it++;
	}

	it = this->_index.begin();
	while(it != this->_index.end())
	{
		path = this->_path;
		if (path[path.size() - 1] != '/')
			path += "/";
		path += *it;
		if (Utils::pathIsFile(path))
		{
			this->_path = path;
			if (this->_contentLocation[this->_contentLocation.size() - 1] != '/')
				this->_contentLocation += "/";
			this->_contentLocation += *it;
			return this->_path;
		}
		it++;
	}
	return "";
}

std::ostream	&operator<<(std::ostream &out, RequestConfig &request) {
	out << "path: " << request._path << std::endl;
	out << "content_location: " << request._contentLocation << std::endl;
	out << "error_page:" << std::endl;
	for (std::map<int, std::string>::iterator i = request._error_page.begin(); i != request._error_page.end(); i++) {
		out << "\t" << i->first << " " << i->second << std::endl;
	}
	out << "client_body_buffer_size: " << request._client_body_buffer_size << std::endl;
	out << "cgi_param:" << std::endl;
	for (std::map<std::string, std::string>::iterator i = request._cgi_param.begin() ; i != request._cgi_param.end(); i++)
		out << "\t" << i->first << "=" << i->second << std::endl;
	out << "cgi_pass: " << request._cgi_pass << std::endl;
	out << "allowed_methods:" << std::endl;
	for (std::set<std::string>::iterator i = request._allowed_methods.begin(); i != request._allowed_methods.end(); i++)
		out << "\t" << *i << std::endl;
	out << "index:" << std::endl;
	for (std::vector<std::string>::iterator i = request._index.begin(); i != request._index.end(); i++)
		out << "\t" << *i << std::endl;
	out << "autoindex: " << (request._autoindex ? "on" : "off") << std::endl;
	return out;
}
