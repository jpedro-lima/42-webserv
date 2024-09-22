/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:37:39 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/22 13:23:42 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

# include "Webserv.hpp"

class Exceptions {
public:
	class	FileNotFoundException: public std::exception{
		public:
		virtual const char	*what() const throw();
	};

	class	ConfigFileErrorException: public std::exception{
		public:
		virtual const char	*what() const throw();
	};
	
	class	ConfigFileEmptyException: public std::exception{
		public:
		virtual const char	*what() const throw();
	};
};

#endif //EXCEPTIONS_HPP