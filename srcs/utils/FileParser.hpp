/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:36:29 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/19 10:24:22 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEPARSER_HPP
# define FILEPARSER_HPP

# include "Webserv.hpp"
//# define parseMap std::map<std::string, void (FileParser::*)(std::string configText)>

typedef struct	s_listen {
	unsigned int	host;
	int				port;
}				t_listen;

class FileParser {
public:
	~FileParser();
	FileParser(std::string configText);

	std::string	grapServers(const std::string configText);
	void	grapListen(const std::string configText);
	void	grapRoot(const std::string configText);
	void	grapServerName(const std::string configText);
	void	grapErrorPages(const std::string configText);
	void	grapClienteBodyBuffer(const std::string configText);
	void	grapAllowedMethods(const std::string configText);
	void	grapIndex(const std::string configText);
	void	grapAutoIndex(const std::string configText);
	void	grapLocation(const std::string configText);
//	void	grapCGIParam(const std::string configText);
//	void	grapCGIPass(const std::string configText);

	class	ExceptionInvalidArguments: public std::exception {
		virtual const char	*what() const throw();
	};
private:
};

#endif //FILEPARSER_HPP