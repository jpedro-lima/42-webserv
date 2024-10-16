/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:15:47 by joapedr2          #+#    #+#             */
/*   Updated: 2024/10/16 16:49:13 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CgiHandler.hpp"

CgiHandler::~CgiHandler(void) {}

CgiHandler::CgiHandler(Request &request, RequestConfig &config): _body(request.getBody()) {
	this->_initEnv(request, config);
}

void	CgiHandler::_initEnv(Request &request, RequestConfig &config) {
	std::map<std::string, std::string>	headers = request.getHeaders();
	if (headers.find("Auth-Scheme") != headers.end() && headers["Auth-Scheme"] != "")
		this->_env["AUTH_TYPE"] = headers["Authorization"];
	this->_env["REDIRECT_STATUS"] = "200";
	this->_env["GATEWAY_INTERFACE"] = "CGI/1.1";
	this->_env["SCRIPT_NAME"] = config.getPath();
	this->_env["SCRIPT_FILENAME"] = config.getPath();
	this->_env["REQUEST_METHOD"] = request.getMethod();
	this->_env["CONTENT_LENGTH"] = Utils::toString(this->_body.length());
	this->_env["CONTENT_TYPE"] = headers["Content-Type"];
	this->_env["PATH_INFO"] = request.getPath();
	this->_env["PATH_TRANSLATED"] = request.getPath();
	this->_env["QUERY_STRING"] = request.getQuery();
	this->_env["REMOTEaddr"] = config.getHostPort().host;
	this->_env["REMOTE_IDENT"] = headers["Authorization"];
	this->_env["REMOTE_USER"] = headers["Authorization"];
	this->_env["REQUEST_URI"] = request.getPath() + request.getQuery();
	this->_env["SERVER_NAME"] = this->_env["REMOTEaddr"];
	if (headers.find("Hostname") != headers.end())
		this->_env["SERVER_NAME"] = headers["Hostname"];
	this->_env["SERVER_PORT"] = Utils::toString(config.getHostPort().port);
	this->_env["SERVER_PROTOCOL"] = "HTTP/1.1";
	this->_env["SERVER_SOFTWARE"] = "Weebserv/1.0";

	this->_env.insert(config.getCgiParam().begin(), config.getCgiParam().end());
}

char	**CgiHandler::_getEnvAsCstrArray() const {
	char	**env = new char*[this->_env.size() + 1];
	int	j = 0;
	for (std::map<std::string, std::string>::const_iterator i = this->_env.begin(); i != this->_env.end(); i++) {
		std::string	element = i->first + "=" + i->second;
		env[j] = new char[element.size() + 1];
		env[j] = strcpy(env[j], (const char*)element.c_str());
		j++;
	}
	env[j] = NULL;
	return (env);
}

char	**CgiHandler::_getArgs(const std::string& scriptName) {
	char	**args = new char *[3];
	char 	server_root[PATH_MAX];

	if (!getcwd(server_root, (size_t)PATH_MAX))
		throw (std::string("getcwd() failed"));
	if (scriptName.find(".php") != std::string::npos)
		args[0] = strdup("/usr/bin/php");
	else if (scriptName.find(".py") != std::string::npos)
		args[0] = strdup("/usr/bin/python3");

	std::string temp = std::string(server_root) + scriptName;
	args[1] = strdup(temp.c_str());
	args[2] = NULL;
	return (args);
}

std::string		CgiHandler::executeCgi(const std::string& scriptName) {
	pid_t		pid;
	int			saveStdin;
	int			saveStdout;
	char		**env;
	char		**args;
	std::string	newBody;

	try {
		env = this->_getEnvAsCstrArray();
		args = this->_getArgs(scriptName);
	}
	catch (std::exception&) {
		throw ;
	}
	saveStdin = dup(STDIN_FILENO);
	saveStdout = dup(STDOUT_FILENO);

	FILE	*fIn = tmpfile();
	FILE	*fOut = tmpfile();
	long	fdIn = fileno(fIn);
	long	fdOut = fileno(fOut);
	int		ret = 1;

	write(fdIn, this->_body.c_str(), this->_body.size());
	lseek(fdIn, 0, SEEK_SET);

	pid = fork();
	if (pid == -1) {
		std::cerr << RED << "Fork crashed." << RESET << std::endl;
		return ("Status: 500\r\n\r\n");
	} else if (pid == 0)
	{
		
		dup2(fdIn, STDIN_FILENO);
		dup2(fdOut, STDOUT_FILENO);
		execve(args[0], args, env);
		std::cerr << RED << "Execve crashed." << RESET << std::endl;
		write(STDOUT_FILENO, "Status: 500\r\n\r\n", 15);
	} else {
		char	buffer[CGI_BUFSIZE] = {0};

		waitpid(-1, NULL, 0);
		lseek(fdOut, 0, SEEK_SET);
		ret = 1;
		while (ret > 0) {
			memset(buffer, 0, CGI_BUFSIZE);
			ret = read(fdOut, buffer, CGI_BUFSIZE - 1);
			newBody += buffer;
		}
	}

	dup2(saveStdin, STDIN_FILENO);
	dup2(saveStdout, STDOUT_FILENO);
	fclose(fIn);
	fclose(fOut);
	close(fdIn);
	close(fdOut);
	close(saveStdin);
	close(saveStdout);

	for (size_t i = 0; env[i]; i++)
		delete[] env[i];
	delete[] env;
	delete[] args[0];
	delete[] args[1];
	delete[] args;
	
	if (!pid)
		exit(0);
	return (newBody);
}
