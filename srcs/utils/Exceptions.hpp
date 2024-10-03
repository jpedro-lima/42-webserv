/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:37:39 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/03 17:25:01 by joapedr2         ###   ########.fr       */
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
	
	class	ExpectedCurlyBracketsAfter: public std::exception{
	public:
		virtual const char	*what() const throw();
	};
	
	class	ExpectedCurlyBracketsBefore: public std::exception{
	public:
		virtual const char	*what() const throw();
	};
	
	class	ExceptionInvalidArguments: public std::exception{
	public:
		virtual const char	*what() const throw();
	};

	class	ExceptionInvalidAllowMethod: public std::exception{
	public:
		virtual const char	*what() const throw();
	};

	class	ExceptionInvalidServerName: public std::exception{
	public:
		virtual const char	*what() const throw();
	};
	
	class	ExceptionInvalidAutoIndex: public std::exception{
	public:
		virtual const char	*what() const throw();
	};

	class	ExceptionInvalidListenArgs: public std::exception{
	public:
		virtual const char	*what() const throw();
	};
	
	class	ExceptionInvalidListenServers: public std::exception{
	public:
		virtual const char	*what() const throw();
	};

	class	ExceptionInvalidRootArgs: public std::exception{
	public:
		virtual const char	*what() const throw();
	};

	class	ExceptionInvalidErrorPageArgs: public std::exception{
	public:
		virtual const char	*what() const throw();
	};

	class		ExceptionInvalidClientBodyBufferSize: public std::exception{
	public:
		virtual const char	*what() const throw();
	};

	class	ExceptionInvalidIndexArgs: public std::exception{
	public:
		virtual const char	*what() const throw();
	};

	class	ExceptionInvalidLocationMethod: public std::exception{
	public:
		virtual const char	*what() const throw();
	};

	class	ExceptionInvalidServerMethod: public std::exception{
	public:
		virtual const char	*what() const throw();
	};

	class	ExceptionServerSocket: public std::exception{
	public:
		virtual const char	*what() const throw();
	};
	
	class	ExceptionServerBind: public std::exception{
	public:
		virtual const char	*what() const throw();
	};

	class	ExceptionServerListen: public std::exception{
	public:
		virtual const char	*what() const throw();
	};

	class	ExceptionServiceServer: public std::exception{
	public:
		virtual const char	*what() const throw();
	};
	
};

#endif //EXCEPTIONS_HPP