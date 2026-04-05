#ifndef DECIMAL_H
#define DECIMAL_H

#include "big_int.h"

class Decimal
{
public:
	Decimal();
	Decimal(std::string integer,std::string decimal);
	
	std::string change_base(std::string digs);
	
	void set_precision(int precision);
	
	operator std::string();
	
private:
	BigInt integer,decimal;
	int precision;
};

#endif