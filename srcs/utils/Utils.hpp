/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:33:44 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/29 10:40:52 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Webserv.hpp"

namespace Utils {
	bool	isspace(int c);
	size_t	findMembers(const std::string str, const std::string here);
	bool	isdigit(std::string str);
}
