#include "decimal.h"

Decimal::Decimal()
	:integer(0),decimal(0),precision(16){}
	
Decimal::Decimal(std::string integer,std::string decimal)
	:integer(integer),decimal(decimal),precision(16){}
	
std::string Decimal::change_base(std::string digs)
{
	std::string s_int="",s_dec="";
	BigInt c_int=integer,c_dec=decimal;
	int base=digs.size();
	while(c_int!=0)
	{
		s_int=digs[c_int%base]+s_int;
		c_int/=base;
	}
	int n,prec=precision,dig;
	while(c_dec!=0&&prec--)
	{
		n=c_dec.digits();
		c_dec*=base;
		if(c_dec.digits()==n)
			dig=0;
		else
		{
			dig=atoi(((std::string)c_dec).substr(0,c_dec.digits()-n).c_str());
			c_dec=BigInt(((std::string)c_dec).substr(c_dec.digits()-n));
		}
		s_dec.push_back(digs[dig]);
		c_dec.trail_clear();
	}
	if(s_int.size()==0)
		s_int="0";
	if(s_dec.size()==0||s_dec=="0")
		return s_int;
	return s_int+'.'+s_dec;
}
	
void Decimal::set_precision(int precision)
{
	this->precision=precision;
}

Decimal::operator std::string()
{
	if(decimal.digits()==0||decimal==0)
		return integer;
	return (std::string)integer+'.'+(std::string)decimal;
}