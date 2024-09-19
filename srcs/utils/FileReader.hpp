/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileReader.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 23:18:32 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/19 00:24:23 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEREADER_HPP
# define FILEREADER_HPP

#include "Webserv.hpp"

class FileReader {
public:
	FileReader(const char *filename);
	~FileReader(void);

	std::string			readFile(const char *filename);
	const std::string	getFullFile(void) const;

	class	FileNotFoundException: public std::exception{
			virtual const char	*what() const throw();
	};

private:
	std::string	_fullFile;
};

#endif //FILEREADER_HPP