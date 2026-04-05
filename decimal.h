#ifndef DECIMAL_H
#define DECIMAL_H

#include "big_int.h"

class Decimal
{
public:
	Decimal();
	Decimal(std::string integer,std::string decimal);
	
	std::string change_base(std::string digs);
	std::string change_base(int base,bool cap=false);
	
	void set_precision(int precision);
	
	operator std::string();
	
private:
	BigInt integer,decimal;
	int precision;
	std::string change_base(int base,std::string digs);
};

#endif