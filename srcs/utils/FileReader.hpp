/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileReader.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 23:18:32 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/22 05:15:08 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEREADER_HPP
# define FILEREADER_HPP

#include "Webserv.hpp"

class FileReader {
public:
	FileReader(const char *filename);
	~FileReader(void);

	static std::string	readFile(const char *filename);
	std::string	getFullFileText(void) const;

	class	FileNotFoundException: public std::exception{
		virtual const char	*what() const throw();
	};

	class	ConfigFileErrorException: public std::exception{
		virtual const char	*what() const throw();
	};
private:
	std::string	_fullFile;

	void		checkerConfigFile(void) const;
};

#endif //FILEREADER_HPP