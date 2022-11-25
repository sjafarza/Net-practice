#include "../../incs/parser/Parsing.hpp"

static std::size_t find_comment(const std::vector<std::string> & line_items);


// --------------------------- CONSTRUCTOR  & DESTRUCTOR --------------------------------
Parsing::Parsing(std::string inputFilePath, GlobalConfiguration & globalConf)
	: _inputFilePath(inputFilePath), _globalConf(globalConf), _context("main")
{
	_parseFile();
}

Parsing::Parsing( const Parsing & src )
	: _inputFilePath(src._inputFilePath), _globalConf(src._globalConf), _context("main") 
{}

Parsing::~Parsing() {}

// --------------------------- OVERLOAD  -----------------------------------------------
Parsing &	Parsing::operator=( Parsing const & rhs )
{
	if ( this != &rhs )
	{
		_inputFilePath = rhs._inputFilePath;
		_globalConf = rhs._globalConf;
	}
	return *this;
}

// --------------------------- METHODS -----------------------------------------------
/* 2 */
void	Parsing::_parseLine(std::vector<std::string> & line_items, std::size_t line_nb)
{
	if (_context == "server")
		_parseServerLine(line_items, line_nb);
	else if (_context == "location")
		_parseLocationLine(line_items, line_nb);
	else // main context
	{
        //Whow find server with "{" in next line
		if (line_items.size() == 2 && line_items[0] == "server" && line_items[1] == "{") // server {
		{
			_context = "server";
			_globalConf.addServer();
			_currentServer = &(_globalConf.getServersList().back());
		}
		else if (line_items.size() == 1 && line_items[0] == "}")
		{
			FATAL_ERR("Syntax error: extra '}' in the configuration file\n");
			throw syntax_error("misplaced symbol");
		}
		else
		{
			FATAL_ERR("Parsing error in line " << line_nb << '\n');
			throw parsing_error("invalid line");
		}
	}
}

/* 1 */
void	Parsing::_parseFile()
{
	std::ifstream	inputStream;
	std::size_t		line_nb = 0;
	std::string 	currentLine;
	
	inputStream.open(_inputFilePath.c_str());

	// checking  opening file
	if (!inputStream)
	{
		throw std::ios_base::failure(RED_TXT"Error: while opening configuration file");
	}

	// start to parsing the file line by line in currentLine
	while (std::getline(inputStream, currentLine, '\n'))
	{
		std::vector<std::string>	line_items;
		
		++line_nb;
		line_items = split(currentLine, " \t");

		// skip empty_line  & comment_lins
		if (line_items.empty())
			continue ;
		else if (line_items[0][0] == '#')
			continue ;
        // parsing the rest    
		else
		{
            // remove tokens that have '#' in them
			std::size_t comment_index = find_comment(line_items);
			while (comment_index != line_items.size())
				line_items.pop_back();
			_parseLine(line_items, line_nb); /* got to 2*/
		}
	}

	if (_context != "main")
	{
		FATAL_ERR("Syntax error: missing '}' in the configuration file\n");
		throw syntax_error("file syntax error");
	}

	if (_globalConf.getServersList().empty())
	{
		FATAL_ERR("No server detected in configuration file" << '\n');
		throw parsing_error("invalid file");
	}

	_checkServerDuplicate();
	inputStream.close();
}

//* ---------------  Private Helpers Fonction ---------------------------------------
static std::size_t find_comment(const std::vector<std::string> & line_items)
{
	std::size_t i;
	
	for (i = 0; i < line_items.size(); ++i)
	{
		if (line_items[i][0] == '#')
			break ;	
	}
	return i;
}

void	Parsing::_checkServerDuplicate()
{
	for (std::size_t i = 0; i < _globalConf.getServersList().size() - 1; ++i)
	{
		for (std::size_t j = i + 1; j < _globalConf.getServersList().size(); ++j)
		{
			if (_globalConf.getServersList()[i].getIP() == _globalConf.getServersList()[j].getIP() &&
				_globalConf.getServersList()[i].getPort() == _globalConf.getServersList()[j].getPort())
				_globalConf.getServersList().erase(_globalConf.getServersList().begin() + j--);
		}
	}
}
