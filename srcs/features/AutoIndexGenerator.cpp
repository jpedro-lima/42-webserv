/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AutoIndexGenerator.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 08:38:36 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/13 02:55:14 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AutoIndexGenerator.hpp"

AutoIndexGenerator::~AutoIndexGenerator(void) {}

AutoIndexGenerator::AutoIndexGenerator(void) {}

std::string AutoIndexGenerator::getPage(const char *path, std::string const &host, int port) {
    std::string dirName(path);
    DIR *dir = opendir(path);
    std::string page =\
    "<!DOCTYPE html>\n\
    <html>\n\
    <head>\n\
            <title>" + dirName + "</title>\n\
    </head>\n\
    <body>\n\
    <h1>INDEX of " + dirName + "</h1>\n\
    <ul>\n";
    if (dir == NULL) {
        std::cerr << RED << "Error: could not open [" << path << "]" << RESET << std::endl;
        return "";
    }
    if (dirName[0] != '/')
        dirName = "/" + dirName;
    for (struct dirent *dirEntry = readdir(dir); dirEntry; dirEntry = readdir(dir)) {
        page += AutoIndexGenerator::getLink(std::string(dirEntry->d_name), dirName, host, port);
    }
    page +="\
    </ul>\n\
    </body>\n\
    </html>\n";
    closedir(dir);
    return page;
}

std::string AutoIndexGenerator::getLink(std::string const &dirEntry, std::string const &dirName, std::string const &host, int port) {
    std::stringstream   ss;
    ss << "\t\t<li><a href=\"http://" + host + ":" <<\
        port << dirName + "/" + dirEntry + "\">" + dirEntry + "</a></li>\n";
    return ss.str();
}
