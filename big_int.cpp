#include "big_int.h"

BigInt::BigInt()
	:num("0"){}
	
BigInt::BigInt(int number)
	:num(std::to_string(number)){}
	
BigInt::BigInt(std::string str)
	:num(str){}
	
int BigInt::digits()
{
	return num.size();
}

void BigInt::abs()
{
	if(num.size()>0&&(num[0]=='+'||num[0]=='-'))
		num=num.substr(1);
}

bool BigInt::negative()
{
	return num.size()>0&&num[0]=='-';
}

BigInt BigInt::operator++()
{
	int i;
	for(i=num.size()-1;i>=0;i--)
	{
		if(num[i]=='9')
			num[i]='0';
		else
		{
			num[i]++;
			break;
		}
	}
	if(i==-1)
		num='1'+num;
	return *this;
}

BigInt BigInt::operator--()
{
	int i;
	for(i=num.size()-1;i>=0;i--)
	{
		if(num[i]=='0')
			num[i]='9';
		else
		{
			num[i]--;
			break;
		}
	}
	if(num!="0"&&num[0]=='0')
		num.erase(0,1);
	return *this;
}

BigInt BigInt::operator+(BigInt number)
{
	BigInt copy=*this;
	int n=copy.equalize(number);
	int c,rem=0;
	for(int i=n-1;i>=0;i--)
	{
		c=number.num[i]+copy.num[i]+rem-96;
		rem=c/10;
		c%=10;
		copy.num[i]=c+'0';
	}
	if(rem>0)
		copy.num="1"+copy.num;
	return copy;
}

BigInt BigInt::operator-(BigInt number)
{
	BigInt copy=*this;
	int n=copy.equalize(number);
	int c,rem=0;
	bool neg=false;
	if(copy<number.num)
	{
		neg=true;
		std::swap(copy,number);
	}
	for(int i=n-1;i>=0;i--)
	{
		c=copy.num[i]-number.num[i]-rem;
		if(c<0)
		{
			rem=1;
			c+=10;
		}
		else rem=0;
		copy.num[i]=c+'0';
	}
	copy.lead_clear();
	if(neg)
		copy.num="-"+copy.num;
	return copy;
}

BigInt BigInt::operator*(int number)
{
	BigInt copy=*this;
	int c,rem=0;
	for(int i=num.size()-1;i>=0;i--)
	{
		c=(num[i]-'0')*number+rem;
		rem=c/10;
		c%=10;
		copy.num[i]=c+'0';
	}
	if(rem>0)
		copy.num=std::to_string(rem)+copy.num;
	return copy;
}

BigInt BigInt::operator/(int number)
{
	long long rem=0;
	std::string res="";
	for(int i=0;i<num.size();i++)
	{
		rem=rem*10+num[i]-'0';
		res+=(char)(rem/number+'0');
		rem%=number;
	}
	BigInt r(res);
	r.lead_clear();
	return r;
}

int BigInt::operator%(int number)
{
	long long rem=0;
	std::string res="";
	for(int i=0;i<num.size();i++)
	{
		rem=rem*10+num[i]-'0';
		res+=(char)(rem/number+'0');
		rem%=number;
	}
	return rem;
}
	
BigInt BigInt::operator+=(BigInt number)
{
	return *this=*this+number;
}

BigInt BigInt::operator-=(BigInt number)
{
	return *this=*this-number;
}

BigInt BigInt::operator*=(int number)
{
	return *this=*this*number;
}

BigInt BigInt::operator/=(int number)
{
	return *this=*this/number;
}

int BigInt::operator%=(int number)
{
	int rem=*this%number;
	*this=rem;
	return rem;
}
	
int BigInt::cmp(BigInt number)
{
	if(num.size()<number.num.size())
		return -1;
	if(num.size()>number.num.size())
		return 1;
	return num.compare(number.num);
}

bool BigInt::operator<(BigInt number)
{
	return cmp(number)<0;
}

bool BigInt::operator<=(BigInt number)
{
	return cmp(number)<=0;
}

bool BigInt::operator==(BigInt number)
{
	return cmp(number)==0;
}

bool BigInt::operator>=(BigInt number)
{
	return cmp(number)>=0;
}

bool BigInt::operator>(BigInt number)
{
	return cmp(number)>0;
}

bool BigInt::operator!=(BigInt number)
{
	return cmp(number)!=0;
}

BigInt::operator std::string()
{
	if(num.size()==0)
		return "0";
	return num;
}

int BigInt::equalize(BigInt &number)
{
	int n=std::max(num.size(),number.num.size());
	while(num.size()<n)
		num='0'+num;
	while(number.num.size()<n)
		number.num='0'+number.num;
	return n;
}

void BigInt::lead_clear()
{
	int i=0;
	while(num[i]=='0'&&i<num.size())i++;
	if(i==num.size())
		num="0";
	else num=num.substr(i);
}

void BigInt::trail_clear()
{
	int i=num.size()-1;
	while(num[i]=='0'&&i>=0)i--;
	if(i==-1)
		num="0";
	else num=num.substr(0,i+1);
}

std::ostream &operator<<(std::ostream &out,BigInt number)
{
	return out<<number.num;
}