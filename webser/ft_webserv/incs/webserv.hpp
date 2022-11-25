#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h> // For sockaddr_in
# include <arpa/inet.h>	// For inet_addr
# include <sys/stat.h> // For directory testing
# include <unistd.h>
# include <stdio.h>
# include <poll.h> // for poll
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h> // For directory listing

# include <cstdlib>
# include <vector>
# include <map>
# include <set>
# include <fstream>
# include <string>
# include <iostream>
# include <sstream>

//class ServerEngine;
struct Connection;
//typedef	std::map<struct pollfd, ServerEngine *> 	t_fds_map;

// parser************************************************
# include "./parser/GlobalConfiguration.hpp"
//# include "./parser/Location.hpp"
# include "./parser/ServerInParser.hpp"
# include "./parser/Parsing.hpp"

std::vector<std::string>	split(const std::string &str, char delim);
std::vector<std::string>	split(const std::string &str, const char *set_delim);



# define RED_TXT "\e[31m"
# define GREEN_TXT "\e[32m"
# define YELLOW_TXT "\e[33m"
# define BLUE_TXT "\e[34m"
# define MAG_TXT "\e[35m"

# define BOLD_TXT "\e[1m"
# define ITALIC_TXT "\e[2m"
# define UL_TXT "\e[4m"

# define RESET_TXT "\e[0m"

# define FATAL_ERR(x)	std::cerr << RED_TXT << x << RESET_TXT;

#endif