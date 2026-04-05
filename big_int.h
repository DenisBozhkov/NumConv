#ifndef BIGINT_H
#define BIGINT_H

#include<string>
#include<iostream>

class BigInt
{
public:
	BigInt();
	BigInt(int number);
	BigInt(std::string str);
	
	int digits();
	
	BigInt operator++();
	BigInt operator--();
	
	void abs();
	bool negative();
	
	BigInt operator+(BigInt number);
	BigInt operator-(BigInt number);
	BigInt operator*(int number);
	BigInt operator/(int number);
	int operator%(int number);
	
	BigInt operator+=(BigInt number);
	BigInt operator-=(BigInt number);
	BigInt operator*=(int number);
	BigInt operator/=(int number);
	int operator%=(int number);
	
	int cmp(BigInt number);
	
	bool operator<(BigInt number);
	bool operator<=(BigInt number);
	bool operator==(BigInt number);
	bool operator>=(BigInt number);
	bool operator>(BigInt number);
	bool operator!=(BigInt number);
	
	void lead_clear();
	void trail_clear();
	
	operator std::string();
	
	friend std::ostream &operator<<(std::ostream &out,BigInt number);
	
private:
	std::string num;
	int equalize(BigInt &number);
};

#endif