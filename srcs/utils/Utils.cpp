/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:40:52 by joapedr2          #+#    #+#             */
/*   Updated: 2024/09/22 02:19:53 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

namespace Utils {
	bool	isspace(int c) {
		if (c == ' ' || c == '\f' || c == '\n'|| c == '\r'|| c == '\t' || c == '\v' || c == '\0')
			return (true);
		return (false);
	}

	size_t	findMembers(const std::string str, const std::string here) {
		size_t	pos = 0;

		while ((pos = here.find(str, pos)) != std::string::npos) {
			if (Utils::isspace(here[pos + str.length()]) && Utils::isspace(here[pos - 1]))
				return (pos);
			pos++;
		}
		return (0);
	}
}