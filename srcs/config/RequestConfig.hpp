/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestConfig.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:43:20 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/11 11:15:37 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTCONFIG_HPP
# define REQUESTCONFIG_HPP

# include "Webserv.hpp"
# include "Request.hpp"
# include "Config.hpp"

typedef struct	s_listen	t_listen;

class RequestConfig {
public:
	~RequestConfig(void);
	RequestConfig(void);

	RequestConfig(ConfigServer &config, Request &request, const std::string &path, \
		const std::string &method, std::string &locationName);

	friend std::ostream	&operator<<(std::ostream &out, RequestConfig &request);

	//GETERS
	const std::string							&getContentLocation() const;
	const std::string							&getPath() const;
	const std::map<int, std::string>			&getErrorPage() const;
	const unsigned long							&getClientBodyBufferSize() const;
	const std::map<std::string, std::string>	&getCgiParam() const;
	const std::string							&getCgiPass() const;
	const std::string							&getLang() const;
	const std::set<std::string>					&getAllowedMethods() const;
	const t_listen								&getHostPort() const;
	const bool									&getAutoIndex() const;

	//SETTERS
	void	setPath(int code);
	void	setPath(const std::string&);
	void	setContentLocation(const std::string &path);
	void	setHostPort(const t_listen hostPort);

	//UTILS
	std::string							addIndex(Request& request);

private:
	std::string							_contentLocation;
	std::string							_path;
	std::map<int, std::string>			_error_page;
	unsigned long						_client_body_buffer_size;
	std::map<std::string, std::string>	_cgi_param;
	std::string							_cgi_pass;
	std::set<std::string>				_allowed_methods;
	t_listen							_hostPort;
	std::string							_lang;
	std::vector<std::string>			_index;
	bool								_autoindex;
};

#endif //REQUESTCONFIG_HPP