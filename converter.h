#ifndef CONVERTER_H
#define CONVERTER_H

#include<regex>
#include<stack>
#include<iostream>
#include "decimal.h"
#include "options.h"

class Converter
{
public:
	Converter(Options &options,MessageHandler &handler);
	
	void read();
	void convert();
	
	std::string text;
	
private:
	std::string input,output,digits;
	int precision;
	
	MessageHandler handler;
	
	struct Match
	{
		int pos,size;
		std::string integer,decimal,exponent;
	};
	
	Decimal match(const Match &m);
	
	std::stack<Match> get_matches(std::string text);
	
	const std::regex expr=std::regex("(0|(?:[1-9]\\d*))(?:\\.(\\d+))?(?:[eE]([\\+\\-]?[1-9]\\d*))?");
};

#endif