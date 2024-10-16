/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 22:58:17 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/13 13:25:03 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "Webserv.hpp"

# include "ResponseHeader.hpp"
# include "Request.hpp"
# include "RequestConfig.hpp"
# include "CgiHandler.hpp"
# include "AutoIndexGenerator.hpp"

# define mapRequest std::map<std::string, void (Response::*)(Request &, RequestConfig &)> 

class Response {
public:
	Response(void);
	Response(const Response & src);
	~Response(void);

	Response & operator=(const Response & src);

	const std::string	&getHeader(void);
	const std::string	&getResponse(void);
	void				call(Request & request, RequestConfig & requestConf);

	int				readContent(void);
	int				writeContent(std::string content);
	std::string		readHtml(const std::string& path);

	//UTILS
	void	getMethod(Request & request, RequestConfig & requestConf);
	void	headMethod(Request & request, RequestConfig & requestConf);
	void	postMethod(Request & request, RequestConfig & requestConf);
	void	putMethod(Request & request, RequestConfig & requestConf);
	void	deleteMethod(Request & request, RequestConfig & requestConf);
	void	optionsMethod(Request & request, RequestConfig & requestConf);
	void	traceMethod(Request & request, RequestConfig & requestConf);

private:
	std::string					_header;
	std::string					_response;
	std::string					_path;
	int							_code;
	std::string					_type;
	bool						_isAutoIndex;
	t_listen					_hostPort;
	std::map<int, std::string>	_errorMap;
	mapRequest					_method;

	mapRequest	_initMethods();
	void		_setupAllowedMethods(const RequestConfig &requestConf);
};

#endif