#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include<iostream>
#include<cstdio>

class MessageHandler
{
public:
	MessageHandler();
	
	void error(std::string message);
	void warning(std::string message);
	void param_error(std::string message);
	
	bool is_handled();
private:
	bool handled;
};

#endif