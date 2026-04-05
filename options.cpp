#include "options.h"
#include<iostream>

bool Options::has_input_file()
{
	return input_file.size()!=0;
}

bool Options::has_output_file()
{
	return output_file.size()!=0;
}

std::string Options::get_input_file()
{
	return input_file;
}

std::string Options::get_output_file()
{
	return output_file;
}

int Options::get_base()
{
	return digits.size();
}

std::string Options::get_digits()
{
	return digits;
}

int Options::get_precision()
{
	return precision;
}

Options::Options(std::string input_file,std::string output_file,std::string digits,int precision)
	:input_file(input_file),output_file(output_file),digits(digits),precision(precision){}

std::string get_digs(int base,bool capital)
{
	std::string digits="";
	for(int i=0;i<base&&i<10;i++)
		digits.push_back(i+'0');
	for(int i=0;i<base-10;i++)
		digits.push_back(i+(capital?'A':'a'));
	return digits;
}

void Options::print_success_message()
{
	std::cout<<"Text ";
	if(has_input_file())
		std::cout<<"in file \""<<input_file<<"\" ";
	else std::cout<<"on the console ";
	std::cout<<"successfully converted to base "<<get_base()<<" with digit set \""<<get_digits()<<"\".\n";
	std::cout<<"The result was written ";
	if(has_output_file())
		std::cout<<"in file \""<<output_file<<"\".";
	else std::cout<<"on the console.";
}

Options Options::get_options(std::vector<std::string> program_options,MessageHandler &handler)
{
	std::string input_file="",output_file="",digits="";
	int precision=-1;
	for(auto it=program_options.begin();it!=program_options.end();it++)
	{
		if(*it=="-i")
		{
			it++;
			if(it==program_options.end())
				handler.param_error("Expeced file name after parameter -i");
			if(input_file.size()>0)
				handler.warning("Input file name reset from \""+input_file+"\" to \""+(*it)+"\" (duplicated -i option)");
			input_file=*it;
		}
		else if(*it=="-o")
		{
			it++;
			if(it==program_options.end())
				handler.param_error("Expeced file name after parameter -o");
			if(output_file.size()>0)
				handler.warning("Output file name reset from \""+output_file+"\" to \""+(*it)+"\" (duplicated -o option)");
			output_file=*it;
		}
		else if(*it=="-p")
		{
			it++;
			if(it==program_options.end()||it->find_first_not_of("0123456789")!=std::string::npos)
				handler.param_error("Expeced number after parameter -p");
			if(precision>-1)
				handler.warning("Precision reset from "+std::to_string(precision)+" to "+(*it)+" (duplicated -p option)");
			precision=atoi(it->c_str());
			if(precision<0)
				handler.param_error("Precision must be non-negative integer");
		}
		else if(*it=="-b"||*it=="-B")
		{
			std::string opt=*it;
			it++;
			if(it==program_options.end()||it->find_first_not_of("0123456789")!=std::string::npos)
				handler.param_error("Expeced number after parameter "+opt);
			int base=atoi(it->c_str());
			if(base<2||base>36)
				handler.param_error("Numeral system base must be between 2 and 36");
			std::string digs=get_digs(base,opt=="-B");
			if(digits.size()>0)
				handler.warning("Reset numeral system base from base "+std::to_string(digits.size())+" with digits \""+digits
								+"\" to base "+std::to_string(base)+" with digits \""+digs+"\" (specified both -b, -B or -d options)");
			digits=digs;
		}
		else if(*it=="-d")
		{
			it++;
			if(it==program_options.end())
				handler.param_error("Expeced string after parameter -d");
			if(it->size()<2)
				handler.param_error("The base of the numeral system must be bigger than 1");
			if(digits.size()>0)
				handler.warning("Reset numeral system base from base "+std::to_string(digits.size())+" with digits \""+digits
								+"\" to base "+std::to_string(it->size())+" with digits \""+(*it)+"\" (specified both -b, -B or -d options)");
			digits=*it;
		}
		else handler.error("Unknown parameter \""+(*it)+"\"");
	}
	if(digits.size()==0)
		digits=get_digs(16,true);
	if(precision==-1)
		precision=10;
	return Options(input_file,output_file,digits,precision);
}