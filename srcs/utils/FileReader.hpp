/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileReader.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 23:18:32 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/25 17:11:52 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEREADER_HPP
# define FILEREADER_HPP

# include "Webserv.hpp"
typedef	std::vector<std::string>	fileVector;

namespace FileReader {

	std::string	readFile(const char *filename);
	fileVector	split(std::string fileText, const std::string charset);

	void		checkerConfigFile(const std::string fileText) ;
};


#endif //FILEREADER_HPP