#pragma once

#include "iostream"
#include "fstream"
#include "cmath"
#include "cstdlib"
#include "vector"
#include "ctime"
#include "string"
#include "Support.h"
#include <time.h>

using namespace std;

void inverseVector(vector<int> &a)
{
	vector<int> supp=a;
	a.clear();
	for(int i=supp.size()-1; i>=0; --i)
	{
		a.push_back(supp[i]);
	}
	return;
}

void makeVectorCanonical(vector<int> &a, int size)
{
	vector<int>::iterator it;
	it=a.begin();
	a.insert(it,size-a.size(),0);
}

bool vectorNotLessThan(const vector<int> &a, const vector<int> &b)
{
	if(a.size()<b.size())
		return false;
	if(a.size()>b.size())
		return true;
	int i=0;
	while(i<a.size() && a[i]==b[i])
		i++;
	if(i>=a.size()) return true;
	if(a[i]>b[i]) return true;
	return false;
}

vector<int> sumVector(vector<int> a, vector<int> b, const int &base)
{
	if(a.size()>b.size())
		makeVectorCanonical(b,a.size());
	else
		makeVectorCanonical(a,b.size());
	vector<int> supp;
	int rest=0, sum=0;
	for(int i=a.size()-1; i>=0; i--)
	{
		sum=a[i]+b[i]+rest;
		rest=sum/base; 
		sum%=base;
		supp.push_back(sum);
	}
	if(rest==1) supp.push_back(1);
	inverseVector(supp);
	return supp;
}

vector<int> mutiplyVectorAndInt(const vector<int> &a, const int &n, const int &base)
{
	vector<int> supp;
	int sum=0, rest=0;
	for(int i=a.size()-1; i>=0; i--)
	{
		sum=a[i]*n+rest;
		rest=sum/base; 
		sum%=base;
		supp.push_back(sum);
	}
	while(rest>0)
	{
		supp.push_back(rest%base);
		rest/=base;
	}
	inverseVector(supp);
	return supp;
}

vector<int> mutiplyVectorAndVector(const vector<int> &a, const vector<int> &b, const int &base)
{
	vector<int> supp,sum;
	vector<int>::iterator it;
	for(int i=b.size()-1; i>=0; i--)
	{
		supp=mutiplyVectorAndInt(a,b[i],base);
		it=supp.end();
		supp.insert(it, b.size()-i-1, 0);
		sum=sumVector(sum,supp,base);
	}
	if(sum[0]==0)
	{
		int u=0;
		while(u<sum.size()-1 && sum[u]==0)
			u++;
		sum.erase(sum.begin(), sum.begin() +u);
	}
	return sum;
}

vector<int> IpowVector(const vector<int> &a, vector<int> n, const vector<int> &roll, const int &base )
{
	vector<int> supp(1,1), _n=n, pows, bin(1,2);
	int maxBinPow=(int)((double)(n.size())/(double)log10((double)2))+1;
	vector<vector<int>> binPow;
	for(int i=0; i<maxBinPow+1; i++)
	{
		binPow.push_back(supp);
		supp=mutiplyVectorAndInt(supp, 2, base);
	}
	vector<int> res(1,1);
	int j=maxBinPow;
	bool check=false;
	while(j>-1)
	{
		if(vectorNotLessThan(_n,binPow[j])) 
		{
			pows.push_back(1);
			_n=subtractVectors(_n, binPow[j], base);
			check=true;
		}
		else
			if(check==true)
				pows.push_back(0);
		j--;
	}
	supp.clear();
	supp=a;
	for(int i=pows.size()-1; i>-1; i--)
	{
		if(pows[i]==1)
			res=moduloVector(mutiplyVectorAndVector(res, supp, base), roll, base);
		supp=moduloVector(mutiplyVectorAndVector(supp,supp,base), roll, base);
	}
	return res;
}

vector<int> subtractVectors(vector<int> a,vector<int> b, const int &base)
{
	makeVectorCanonical(b,a.size());
	vector<int> supp;
	int rest=0, sum=0;
	for(int i=a.size()-1; i>=0; i--)
	{
		if(a[i]-rest-b[i]<0)
		{
			sum=a[i]-rest-b[i]+base;
			rest=1;
		}
		else
		{
			sum=a[i]-rest-b[i];
			rest=0;
		}
		supp.push_back(sum);
	}
	inverseVector(supp);
	int i=2;
	while(i>1 && supp[0]==0)
	{
		supp.erase(supp.begin());
		i=supp.size();
	}
	return supp;
}

vector<int> divideVectorByVector(vector<int> a, vector<int> b, const int &base)
{
	vector<int> res;
	if(!vectorNotLessThan(a,b))
	{
		res.push_back(0);
		return res;
	}
	if (b[0]<base/2)
	{
		int d=base/(b[0]);
		a=mutiplyVectorAndInt(a,d,base);
		b=mutiplyVectorAndInt(b,d,base);
	}
	vector<int> _a=a;
	vector<int> _b;
	int k;
	vector<int> supp=b;
	int shift=a.size()-b.size();
	supp.insert(supp.end(),shift,0);
	if(!vectorNotLessThan(a,supp))
		shift--;	
	while(vectorNotLessThan(_a,b) || shift>-1)
	{
		if(_a.size()==0)
		{
			res.insert(res.end(),shift+1,0);
			return res;
		}
		supp=b;
		supp.insert(supp.end(),shift,0);
		if(_a.size()>supp.size() && _a.size()>1)
			k=(base*_a[0]+_a[1])/supp[0]+1;
		else 
			k=_a[0]/supp[0]+1;
		_b=mutiplyVectorAndInt(supp,k,base);
		while(!vectorNotLessThan(_a,_b))
		{
			_b=subtractVectors(_b,supp,base);
			k--;
		}
		_a=subtractVectors(_a,_b,base);
		res.push_back(k);
		shift--;
	}
	return res;
}

vector<int> convertIntIntoVector(int a, const int &base)
{
	vector<int> res;
	int _a=a;
	int supp=1;
	int i=0;
	while(_a>=base)
	{
		_a=_a/base;
		supp*=base;
		i++;
	}
	int j=0;
	while(j<=i)
	{
		res.push_back((a-a%supp)/supp);
		a=a%supp;
		supp/=base;
		j++;
	}
	return res;
}

vector<int> moduloVector(vector<int> a, vector<int> b, const int &base)
{
	vector<int> temp=divideVectorByVector(a,b,base);
	vector<int> supp=subtractVectors(a,mutiplyVectorAndVector(temp,b,base),base);
	return supp;
}

vector<int> convertFromBase(vector<int> a, const int &base)
{
	vector<int> res;
	vector<int> _base=convertIntIntoVector(base,10);
	vector<int> supp(1,1);
	int i=a.size();
	while(i>0)
	{
		i--;
		res=sumVector(res, mutiplyVectorAndInt(supp, a[i], 10),10);
		supp=mutiplyVectorAndVector(supp,_base,10);
	}
	return res;
}

vector<int> yakobi(vector<int> a, vector< int> P, const int &base)
{
	vector<int> bin(1,2), one(1,1);
	vector<int> res=IpowVector(a,divideVectorByVector(subtractVectors(P,one,base), bin, base), P, base);
	res=moduloVector(res,P,base);
	return res;
}

vector<int> gcd(vector<int> a, vector<int> b, const int &base)
{
	vector<int> nullVec(1,0),temp;
	while(b!=nullVec && b.size()>0)
	{
		a=moduloVector(a,b,base);
		temp=a;
		a=b;
		b=temp;
	}
	return a;
}