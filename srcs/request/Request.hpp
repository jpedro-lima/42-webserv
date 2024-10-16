/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 22:58:12 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/10 15:39:22 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include "Webserv.hpp"

class Request {
public:
	~Request(void);
	Request(void);
	Request(const std::string& str);

	Request	&operator=(const Request&);

	/*** GETTERS ***/
	const std::map<std::string, std::string>			&getHeaders() const;
	const std::map<std::string, std::string>			&getEnv() const;
	const std::string									&getMethod() const;
	const std::string									&getVersion() const;
	const int											&getRet() const;
	const std::string									&getBody() const;
	const int											&getPort() const;
	const std::string									&getPath() const;
	const std::string									&getQuery() const;
	const std::string									&getRaw() const;
	const std::list<std::pair<std::string, float> >		&getLang() const;

	/*** SETTERS **/
	void	setBody(const std::string& line);
	void	setRet(int);
	void	setMethod(const std::string &method);

	/*** UTILS ****/
	int		parse(const std::string& str);
	void	resetHeaders();
	void	stripAll();
	void	displayHeaders() const;
	static bool	compareFunction(const std::pair<std::string, float> first, const std::pair<std::string, float> second);

	static std::vector<std::string>		initMethods();

private:
	std::string									_method;
	std::string									_version;
	std::map<std::string, std::string>			_headers;
	std::map<std::string, std::string>			_env_for_cgi;
	int											_ret;
	std::string									_body;
	int											_port;
	std::string									_path;
	std::string									_query;
	std::list<std::pair<std::string, float> >	_lang;
	const std::string&							_raw;

	/*** PARSING ***/
	int			readFirstLine(const std::string& line);
	int			readPath(const std::string& line, size_t i);
	int			readVersion(const std::string& line, size_t i);
	int			checkMethod();
	int			checkPort();
	void		findQuery();
	std::string	formatHeaderForCGI(std::string& key);
	std::string	nextLine(const std::string &str, size_t& i);
	void		setLang();


	/*** AVAILABLE HTTP METHODS ***/
	static	std::vector<std::string>	methods;

};

std::ostream	&operator<<(std::ostream &out, const Request &request);
#endif //REQUEST_HPP