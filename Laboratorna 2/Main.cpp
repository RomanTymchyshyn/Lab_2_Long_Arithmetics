#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cmath>
#include <time.h>
#include <complex>
#include "Long.h"
#include "Support.h"

using namespace std;

int main()
{
	ifstream fi("in.txt");
	if (!fi) return 0;
	ofstream fo("out.txt");
	Long *a, *b, *c, *d, *e, *f;
	a=new Long_number<Karatsuba>;
	b=new Long_number<Shenchaga>;
	c=new Long_number<Cook>;
	d=new Long_number<ShenchShtrass>;
	e=new Long;
	f=new Long;
	fo.setf(ios::app);
	/*
	fi>>(*a);
	fi>>(*b);
	double dif;
	double time=(float)clock()/CLOCKS_PER_SEC;
	(*f)=(*a)*(*b);
	dif=(float)clock()/CLOCKS_PER_SEC-time;
	time=(float)clock()/CLOCKS_PER_SEC;
	cout<<"Karatsuba\n";
	cout<<dif<<endl;
	fo<<"Karatsuba\n";
	fo<<(*f);
	fo<<endl;
	*/
	/*
	fi>>(*b);
	fi>>(*c);
	double time=(float)clock()/CLOCKS_PER_SEC;
	(*f)=(*b)*(*c);
	double dif=(float)clock()/CLOCKS_PER_SEC-time;
	time=(float)clock()/CLOCKS_PER_SEC;
	cout<<"Toom Cook\n";
	cout<<dif<<endl;
	fo<<"Toom Cook\n";
	fo<<(*f);
	fo<<endl;
	*/
	/*
	fi>>(*d);
	fi>>(*c);
	double time=(float)clock()/CLOCKS_PER_SEC;
	(*f)=(*d)*(*c);
	double dif=(float)clock()/CLOCKS_PER_SEC-time;
	time=(float)clock()/CLOCKS_PER_SEC;
	cout<<"ShenchShtrass\n";
	cout<<dif<<endl;
	fo<<"ShenchShtrass\n";
	fo<<(*f);
	fo<<endl;
	*/
	/*
	fi>>(*a);
	fi>>(*b);
	double time=(float)clock()/CLOCKS_PER_SEC;
	(*f)=(*b)*(*a);
	double dif=(float)clock()/CLOCKS_PER_SEC-time;
	time=(float)clock()/CLOCKS_PER_SEC;
	cout<<"Shenchaga\n";
	cout<<dif<<endl;
	fo<<"Shenchaga\n";
	fo<<(*f);
	fo<<endl;
	*/
	/*
	fi>>(*e);
	fi>>(*d);
	double time=(float)clock()/CLOCKS_PER_SEC;
	(*f)=(*e)*(*d);
	double dif=(float)clock()/CLOCKS_PER_SEC-time;
	time=(float)clock()/CLOCKS_PER_SEC;
	cout<<"Primitive\n";
	cout<<dif<<endl;
	fo<<"Primitive\n";
	fo<<(*f);
	fo<<endl;
	*/
	/*
	fi>>(*a);
	fi>>(*b);
	double time=(float)clock()/CLOCKS_PER_SEC;
	(*f)=(*a).CookDivide(*b);
	double dif=(float)clock()/CLOCKS_PER_SEC-time;
	time=(float)clock()/CLOCKS_PER_SEC;
	cout<<"CookDivide\n";
	cout<<dif<<endl;
	fo<<"CookDivide\n";
	fo<<(*f);
	fo<<endl;
	*/
	/*
	fi>>(*a);
	double time=(float)clock()/CLOCKS_PER_SEC;
	fo<<"Lemer\n";
	if((*a).Lemer()) fo<<"Prime\n"; else fo<<"Not prime\n";
	double dif=(float)clock()/CLOCKS_PER_SEC-time;
	time=(float)clock()/CLOCKS_PER_SEC;
	cout<<"Lemer\n";
	cout<<dif<<endl;
	fo<<endl;
	*/
	/*
	fi>>(*c);
	double time=(float)clock()/CLOCKS_PER_SEC;
	fo<<"Miller-Rabin\n";//дуже довго працює
	if((*c).MillerRabin(4)) fo<<"Prime\n"; else fo<<"Not prime\n";
	double dif=(float)clock()/CLOCKS_PER_SEC-time;
	time=(float)clock()/CLOCKS_PER_SEC;
	cout<<"Miller-Rabin\n";
	cout<<dif<<endl;
	fo<<endl;
	*/
	
	fi>>(*c);
	double time=(float)clock()/CLOCKS_PER_SEC;
	fo<<"Solovej-Shtrassen\n";
	if((*c).SolovejShtrassen(4)) fo<<"Prime\n"; else fo<<"Not prime\n";
	double dif=(float)clock()/CLOCKS_PER_SEC-time;
	time=(float)clock()/CLOCKS_PER_SEC;
	cout<<"Solovej-Shtrassen\n";
	cout<<dif<<endl;
	fo<<endl;
	

	delete a;
	delete b;
	delete c;
	delete d;
	delete e;
	delete f;
	fi.close();
	fo.close();
	system("pause");
	return 0;
}