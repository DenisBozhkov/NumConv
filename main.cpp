#include<iostream>
#include<regex>
#include<string>
#include<fstream>
#include<stack>
#include "decimal.h"
using namespace std;
string read_all(char* file)
{
	string res="",line;
	ifstream fin(file);
	while(getline(fin,line))
	{
		res.append(line);
		res.push_back('\n');
	}
	res.pop_back();
	return res;
}
struct Match
{
	int pos,size;
	string integer,decimal,exponent;
};

Decimal match(const Match &m)
{
	string integer=m.integer,decimal=m.decimal,exponent=m.exponent;
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

stack<Match> get_matches(string text,regex &r)
{
	stack<Match> matches;
	std::sregex_iterator it(text.begin(), text.end(), r), it_end;
	smatch m;
	while(it!=it_end)
	{
		m=*it;
		matches.push({(int)m.position(),(int)m.str().size(),m.str(1),m.str(2),m.str(3)});
        it++;
	}
    return matches;
}

int main(int argc, char** argv) 
{
	try
	{
		const char exp[]="(0|(?:[1-9]\\d*))(?:\\.(\\d+))?(?:[eE]([\\+\\-]?[1-9]\\d*))?";
		char test[]="test.txt";
		regex r(exp);
		string text=read_all(test);
		cout<<text<<endl<<endl;
		stack<Match> m=get_matches(text,r);
		Decimal dec;
		while(!m.empty())
		{
			dec=match(m.top());
			dec.set_precision(30);
	        text.replace(m.top().pos,m.top().size,dec.change_base(16,true));
	        m.pop();
	    }
	    cout<<text<<endl;
	}
	catch(regex_error e)
	{
		cout<<e.what()<<endl;
	}
	return 0;
}