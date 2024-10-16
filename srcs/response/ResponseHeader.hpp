/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseHeader.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:31:10 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/10 22:02:52 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSEHEADER_HPP
# define RESPONSEHEADER_HPP

# include "Webserv.hpp"

class ResponseHeader {
public:
	ResponseHeader(void);
	ResponseHeader(const ResponseHeader & src);
	~ResponseHeader(void);

	ResponseHeader & operator=(const ResponseHeader & src);

	//SETTERS
	void	setAllow(std::set<std::string> methods);
	void	setAllow(const std::string& allow = "");
	void	setContentLanguage(const std::string& lang = "");
	void	setContentLength(size_t size);
	void	setContentLocation(const std::string& path, int code);
	void	setContentType(std::string type, std::string path);
	void	setDate(void);
	void	setLastModified(const std::string& path);
	void	setLocation(int code, const std::string& redirect);
	void	setRetryAfter(int code, int sec);
	void	setServer(void);
	void	setTransferEncoding(void);
	void	setWwwAuthenticate(int code);

	std::string		getHeader(size_t size, const std::string& path, int code, std::string type, const std::string& contentLocation, const std::string& lang);
	std::string		notAllowed(std::set<std::string> methods, int code);
	std::string		writeHeader(void);
	void			setValues(size_t size, const std::string& path, int code, std::string type, const std::string& contentLocation, const std::string& lang);
	std::string		getStatusMessage(int code);

private:
	std::string					_allow;
	std::string					_contentLanguage;
	std::string					_contentLength;
	std::string					_contentLocation;
	std::string					_contentType;
	std::string					_date;
	std::string					_lastModified;
	std::string					_location;
	std::string					_retryAfter;
	std::string					_server;
	std::string					_transferEncoding;
	std::string					_wwwAuthenticate;
	std::map<int, std::string>	_errors;

	void						initErrorMap();
};

#endif
