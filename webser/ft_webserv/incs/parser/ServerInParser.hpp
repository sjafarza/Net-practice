#ifndef SERVERINPARSER_HPP
# define SERVERINPARSER_HPP

# include "../../incs/webserv.hpp"

class Location;

class ServerInParser
{

	public:

		ServerInParser();
		ServerInParser(ServerInParser const & src );
		~ServerInParser();

		ServerInParser &	operator=(ServerInParser const & rhs );

	private:

		std::vector<std::string>	_names;
		std::string					_IP;
		int							_port;
		//std::map<int, std::string>	_errorPages;
		std::size_t					_clientBufferSize;
		//std::vector<Location>		_routes;

	public:

		// Setters
		
		void			addName(std::string name);
		void			setIP(std::string IP); // can be equal to 'localhost'
		void			setPort(std::string port);
		//void			addErrorPage(int error_code, std::string filePath);
		void			setClientBufferSize(std::size_t buffer_max);
		//Location &		addLocation();
		//void			completeErrorPages();

		// Accessors
		
		std::vector<std::string> & 	getNames();
		std::string					getIP() const;
		int							getPort() const;
		//std::string					getErrorPagePath(int error_code) const;
		std::size_t					getClientBufferSize() const;
		//std::vector<Location> 	&	getRoutes();

		
	private:

		// helper functions
		bool _isIPValid(std::string IP) const;
		
};

#endif 