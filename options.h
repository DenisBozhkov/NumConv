#ifndef OPTIONS_H
#define OPTIONS_H

#include<vector>
#include "message_handler.h"

class Options
{
public:
	bool has_input_file();
	bool has_output_file();
	
	std::string get_input_file();
	std::string get_output_file();
	int get_base();
	std::string get_digits();
	int get_precision();
	
	void print_success_message();
	
	static Options get_options(std::vector<std::string> program_options,MessageHandler &handler);
	
private:
	Options(std::string input_file,std::string output_file,std::string digits,int precision);
	
	std::string input_file;
	std::string output_file;
	std::string digits;
	int precision;
};

#endif