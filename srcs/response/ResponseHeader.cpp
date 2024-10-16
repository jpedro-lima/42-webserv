/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseHeader.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:24:27 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/16 17:45:10 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ResponseHeader.hpp"

ResponseHeader::~ResponseHeader(void) {}

ResponseHeader::ResponseHeader(void) {
	this->_allow = "";
	this->_contentLanguage = "";
	this->_contentLength = "";
	this->_contentLocation = "";
	this->_contentType = "";
	this->_date = "";
	this->_lastModified = "";
	this->_location = "";
	this->_retryAfter = "";
	this->_server = "";
	this->_transferEncoding = "";
	this->_wwwAuthenticate = "";
	initErrorMap();
}

void	ResponseHeader::initErrorMap() {
	this->_errors[100] = "Continue";
	this->_errors[200] = "OK";
	this->_errors[201] = "Created";
	this->_errors[204] = "No Content";
	this->_errors[400] = "Bad Request";
	this->_errors[403] = "Forbidden";
	this->_errors[404] = "Not Found";
	this->_errors[405] = "Method Not Allowed";
	this->_errors[413] = "Payload Too Large";
	this->_errors[500] = "Internal Server Error";
	this->_errors[301] = "Moved Permanently";
}

std::string	ResponseHeader::getHeader(size_t size, const std::string& path, \
		int code, std::string type, const std::string& contentLocation, const std::string& lang) {
	std::string	header;

	setValues(size, path, code, type, contentLocation, lang);
	std::stringstream tmp;
	tmp << code;
	header = "HTTP/1.1 " + tmp.str() + " " + getStatusMessage(code) + "\r\n";
	header += writeHeader();
	return (header);
}

std::string	ResponseHeader::notAllowed(std::set<std::string> methods, int code) {
	std::string	header;

	setAllow(methods);

	if (code == 405)
		header = "HTTP/1.1 405 Method Not Allowed\r\n";
	else if (code == 413)
		header = "HTTP/1.1 413 Payload Too Large\r\n";
	header += writeHeader();
	return (header);
}

std::string	ResponseHeader::writeHeader(void) {
	std::string	header = "";

	if (this->_allow != "")
		header += "Allow: " + this->_allow + "\r\n";
	if (this->_contentLanguage != "")
		header += "Content-Language: " + this->_contentLanguage + "\r\n";
	if (this->_contentLength != "")
		header += "Content-Length: " + this->_contentLength + "\r\n";
	if (this->_contentLocation != "")
		header += "Content-Location: " + this->_contentLocation + "\r\n";
	if (this->_contentType != "")
		header += "Content-Type: " + this->_contentType + "\r\n";
	if (this->_date != "")
		header += "Date: " + this->_date + "\r\n";
	if (this->_lastModified != "")
		header += "Last-Modified: " + this->_lastModified + "\r\n";
	if (this->_location != "")
		header += "Location: " + this->_location + "\r\n";
	if (this->_retryAfter != "")
		header += "Retry-After: " + this->_retryAfter + "\r\n";
	if (this->_server != "")
		header += "Server: " + this->_server + "\r\n";
	if (this->_transferEncoding != "")
		header += "Transfer-Encoding: " + this->_transferEncoding + "\r\n";
	if (this->_wwwAuthenticate != "")
		header += "WWW-Authenticate: " + this->_wwwAuthenticate + "\r\n";
	return (header);
}

std::string	ResponseHeader::getStatusMessage(int code) {
	if (this->_errors.find(code) != this->_errors.end())
		return (this->_errors[code]);
	return ("Unknown Code");
}

void	ResponseHeader::setValues(size_t size, const std::string& path, int code, \
		std::string type, const std::string& contentLocation, const std::string& lang) {
	setAllow();
	setContentLanguage(lang);
	setContentLength(size);
	setContentLocation(contentLocation, code);
	setContentType(type, path);
	setDate();
	setLastModified(path);
	setLocation(code, path);
	setRetryAfter(code, 3);
	setServer();
	setTransferEncoding();
	setWwwAuthenticate(code);
}

void	ResponseHeader::setAllow(std::set<std::string> methods) {
	std::set<std::string>::iterator it = methods.begin();

	while (it != methods.end()) {
		this->_allow += *(it++);

		if (it != methods.end())
			this->_allow += ", ";
	}
}

void	ResponseHeader::setAllow(const std::string& allow) {
	this->_allow = allow;
}

void	ResponseHeader::setContentLanguage(const std::string& lang) {
	this->_contentLanguage = lang;
}

void	ResponseHeader::setContentLength(size_t size) {
	std::stringstream tmp;
	tmp << size;
	this->_contentLength = tmp.str();
}

void	ResponseHeader::setContentLocation(const std::string& path, int code) {
	(void)code;
	this->_contentLocation = path;
}

void	ResponseHeader::setContentType(std::string type, std::string path) {
	if (type != "") {
		this->_contentType = type;
		return ;
	}
	type = path.substr(path.rfind(".") + 1, path.size() - path.rfind("."));
	if (type == "html" || type == "py" || type == "php")
		this->_contentType = "text/html";
	else if (type == "css")
		this->_contentType = "text/css";
	else if (type == "js")
		this->_contentType = "text/javascript";
	else if (type == "jpeg" || type == "jpg")
		this->_contentType = "image/jpeg";
	else if (type == "png")
		this->_contentType = "image/png";
	else if (type == "bmp")
		this->_contentType = "image/bmp";
	else
		this->_contentType = "text/plain";
}

void	ResponseHeader::setDate(void) {
	char			buffer[100];
	struct timeval	tv;
	struct tm		*tm;

	gettimeofday(&tv, NULL);
	tm = gmtime(&tv.tv_sec);
	strftime(buffer, 100, "%a, %d %b %Y %H:%M:%S GMT", tm);
	this->_date = std::string(buffer);
}

void	ResponseHeader::setLastModified(const std::string& path) {
	char			buffer[100];
	struct stat		stats;
	struct tm		*tm;

	if (stat(path.c_str(), &stats) == 0) {
		tm = gmtime(&stats.st_mtime);
		strftime(buffer, 100, "%a, %d %b %Y %H:%M:%S GMT", tm);
		this->_lastModified = std::string(buffer);
	}
}

void	ResponseHeader::setLocation(int code, const std::string& redirect) {
	if (code == 201 || code / 100 == 3) {
		this->_location = redirect;
	}
}

void	ResponseHeader::setRetryAfter(int code, int sec) {
	if (code == 503 || code == 429 || code == 301) {
		std::stringstream tmp;
		tmp << sec;
		this->_retryAfter = tmp.str();
	}
}

void	ResponseHeader::setServer(void) {
	this->_server = "Weebserv/1.0.0 (Unix)";
}

void	ResponseHeader::setTransferEncoding(void) {
	this->_transferEncoding = "identity";
}

void	ResponseHeader::setWwwAuthenticate(int code) {
	if (code == 401)
		this->_wwwAuthenticate = "Basic realm=\"Access requires authentification\" charset=\"UTF-8\"";
}
