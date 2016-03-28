#ifndef _CLASS_Long_
#define _CLASS_Long_

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <list>
#include <complex>
#include <cmath>
#include <stdlib.h>
#include <time.h>

using namespace std;

enum Types{Karatsuba,Cook,Shenchaga,ShenchShtrass};

class Long
{
		vector<int> number;
	public:
		static const int BASE=10;
		Long ();
		Long(string a);
		Long(int a);
		Long operator=(Long a);
		Long operator=(int a);
		Long operator+(Long a);
		Long operator+(int a);
		Long operator-(Long & a);
		Long operator-(int a);
		virtual Long operator*(Long a){return Primitive(a);}
		Long operator*(int a);
		Long operator/(Long a);
		Long operator/(int a);
		bool operator!=(Long a);
		bool operator==(Long a);
		bool operator>(Long a);
		bool operator<(Long a);
		bool operator>=(Long a);
		bool operator<=(Long a);
		int operator%(int a);
		Long operator%(Long a);
		Long operator^(const Long &n);
		vector<int> to_Binary()const;
		void fromBin(vector<int> b);
		int last()const {return (number.size()>0 ? number[number.size()-1] : -1);}
		void pop_back() {number.pop_back();}
		void toLong(string a);
		string toStr() const;
		void del_zeros();
		Long Primitive (Long a);
		Long Karatsuba (Long a);
		Long Cook (Long a);
		Long Shenchaga(Long a);
		Long CookDivide(Long v);
		Long mod(const int &n);
		bool Lemer();
		bool isMersenne(int &p);
		Long ShenchShtrass(Long a);
		Long IndPowMod(const Long &n, const Long &m);
		bool MillerRabin(const int &r);
		bool SolovejShtrassen(int k);
};


template <Types a>
class Long_number:public Long
{
public:
	virtual Long operator*(Long a);
};

template <Types b>
Long Long_number<b>::operator*(Long a)
{
	switch(b)
	{
	case 0: return Karatsuba(a);
	case 1: return Cook(a);
	case 2: return Shenchaga(a);
	case 3: return ShenchShtrass(a);
	}
}

void str_del_zeros(string &a);

vector<complex<double>> fft(vector<complex<double>>);

vector<complex<double>> fft_rev(vector<complex<double>>);

long long round(double x);

bool operator>>(istream &i, Long & a);

bool operator<<(ostream &o, Long a);

string str_divide(string a,int b, string & rest);

#endif