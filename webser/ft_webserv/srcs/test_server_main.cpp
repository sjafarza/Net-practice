

#include <stdio.h>
#include "../incs/TestServer.hpp"
#include "../incs/webserv.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << av[0] << RED_TXT" Error: Webserver needs a configuration file ." << std::endl;
		return (EXIT_FAILURE);
	}

	//parsing

	/*std::string inputPath(av[1]);
	GlobalConfiguration globalConf;
	Parsing parser(inputPath, globalConf);*/

	std::cout << "IN TEST SERVER CPP"<<std::endl;
	SAMATHE::ServConf	sc;
	SAMATHE::TestServer t(sc);
}
