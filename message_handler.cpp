#include "message_handler.h"

MessageHandler::MessageHandler()
	:handled(false){}

void MessageHandler::error(std::string message)
{
	std::cout<<"Error: "<<message<<std::endl;
	exit(0);
}

void MessageHandler::warning(std::string message)
{
	std::cout<<"Warning: "<<message<<std::endl;
	handled=true;
}

void MessageHandler::param_error(std::string message)
{
	std::cout<<"Parameter error: "<<message<<std::endl;
	exit(0);
}

bool MessageHandler::is_handled()
{
	return handled;
}
