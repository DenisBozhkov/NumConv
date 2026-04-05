#include "converter.h"
#include<fstream>

Converter::Converter(Options &options,MessageHandler &handler)
	:handler(handler)
{
	input=options.get_input_file();
	output=options.get_output_file();
	digits=options.get_digits();
	precision=options.get_precision();
}

void Converter::read()
{
	std::string res="",line;
	auto buf=std::cin.rdbuf();
	std::ifstream fin;
	if(input.size()!=0)
	{
		fin.open(input);
		if(!fin.is_open())
			handler.error("Failed reading file \""+input+"\"");
		std::cin.rdbuf(fin.rdbuf());
	}
	
	while(getline(std::cin,line))
	{
		res.append(line);
		res.push_back('\n');
	}
	
	if(input.size()!=0)
	{
		std::cin.rdbuf(buf);
		fin.close();
	}
	if(res.size()>0)
		res.pop_back();
	text=res;
}

void Converter::convert()
{
	std::stack<Match> m=get_matches(text);
	Decimal dec;
	while(!m.empty())
	{
		dec=match(m.top());
		dec.set_precision(precision);
        text.replace(m.top().pos,m.top().size,dec.change_base(digits));
        m.pop();
    }
    if(output.size()==0)
    	std::cout<<text;
    else
    {
    	std::ofstream fout(output);
		if(!fout.is_open())
			handler.error("Failed writing to file \""+output+"\"");
    	fout<<text;
    	fout.close();
	}
}

Decimal Converter::match(const Match &m)
{
	std::string integer=m.integer,decimal=m.decimal,exponent=m.exponent;
	BigInt exp(exponent);
	if(exp.digits()==0)
		return {integer,decimal};
	if(exp.negative())
	{
		exp.abs();
		while(exp!=0)
		{
			if(integer=="0")
				decimal='0'+decimal;
			else
			{
				decimal=integer.back()+decimal;
				integer.pop_back();
				if(integer.size()==0)
					integer="0";
			}
			--exp;
		}
	}
	else
	{
		exp.abs();
		exp.lead_clear();
		while(exp!=0)
		{
			if(decimal.size()==0)
				integer.push_back('0');
			else
			{
				integer.push_back(decimal[0]);
				decimal.erase(0,1);
			}
			--exp;
		}
	}
	return Decimal(integer,decimal);
}

std::stack<Converter::Match> Converter::get_matches(std::string text)
{
	std::stack<Match> matches;
	std::sregex_iterator it(text.begin(), text.end(), expr), it_end;
	std::smatch m;
	while(it!=it_end)
	{
		m=*it;
		matches.push({(int)m.position(),(int)m.str().size(),m.str(1),m.str(2),m.str(3)});
        it++;
	}
    return matches;
}