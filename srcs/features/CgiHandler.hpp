/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:17:41 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/13 20:31:26 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HANDLER_HPP
# define CGI_HANDLER_HPP

# include "Webserv.hpp"

# include "Config.hpp"
# include "Request.hpp"
# include "RequestConfig.hpp"

class CgiHandler {
public:
	~CgiHandler(void);
	CgiHandler(Request &request, RequestConfig &config);

	std::string		executeCgi(const std::string &scriptName);

private:
	CgiHandler(void);
	void								_initEnv(Request &request, RequestConfig &config);
	char								**_getEnvAsCstrArray() const;
	char								**_getArgs(const std::string &scriptName);
	int									_getSocket(unsigned int port);
	int									_connectSocket(unsigned int port);
	std::map<std::string, std::string>	_env;
	std::string							_body;
};

#endif
