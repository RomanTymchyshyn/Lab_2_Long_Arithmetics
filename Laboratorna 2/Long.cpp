#include "Long.h"
#include "Support.h"

const int MAX_BUF = 700;

const double pi=atan(1.0f)*4;

bool operator>>(istream &i, Long &a)
{
	string s;
	if(!(i>>s))return false;
	a.toLong(s);
	return true;
}

bool operator<<(ostream & o, Long a)
{
	string s;
	s=a.toStr();
	if(!(o<<s))return false;
	return true;
}

Long::Long()
{
	number.clear();
}

Long::Long(string a)
{
	if(a!="")
		toLong(a);
	else 
		number.clear();
}

Long::Long(int a)
{
	if (a!=0)
	{
		while(a>BASE)
		{
			number.push_back(a%BASE);
			a/=BASE;
		}
		number.push_back(a);
	}
	else number.clear();
}

bool Long::operator==(Long a)
{
	del_zeros();
	a.del_zeros();
	if (number.size()!=a.number.size()) return false;
	while(a.number.size() < number.size()) a.number.push_back(0);
	while(a.number.size() > number.size()) number.push_back(0);
	for(int i=0;i<(int)number.size();++i)
		if((number[i])!=(a.number[i])) return false;
	return true;
}

Long Long::operator=(Long a)
{
	if ((*this)==a) return (*this);
	if (a.number.size()>0)
		number=a.number;
	else number.clear();
	return (*this);
}

Long Long::operator=(int a)
{
	Long b(a);
	(*this)=b;
	return *this;
}

Long Long::operator+(Long a)
{
	int carry_over = 0;
	int temp_result;
	Long result;
	while (a.number.size() < number.size()) a.number.push_back(0);
	while (a.number.size() > number.size()) number.push_back(0);
	for(int i=0; i<(int)number.size(); i++)
	{
		temp_result = number[i]+a.number[i]+carry_over;
		result.number.push_back(temp_result%BASE);
		carry_over = temp_result/BASE;
	}
	a.del_zeros();
	if(carry_over!=0) result.number.push_back(carry_over);
	del_zeros();
	return result;
}

Long Long::operator+(int a)
{
	Long temp(a);
	return temp+(*this);
}

Long Long::operator-(Long & a)
{
	a.del_zeros();
	if((*this)<a) return Long();
	int carry_over=0;
	int temp_result;
	Long result;
	while (a.number.size() < number.size()) a.number.push_back(0);
	while (a.number.size() > number.size()) number.push_back(0);

	for(int i=0; i<(int)number.size(); i++)
	{
		temp_result=number[i]-a.number[i]-carry_over;
		if (temp_result<0)
		{
			temp_result+=BASE;
			carry_over=1;
		}
		else carry_over=0;
		result.number.push_back(temp_result);
	}
	a.del_zeros();
	del_zeros();
	return result;
}

Long Long::operator-(int a)
{
	Long temp(a);
	if((*this)<a) return Long ();
	return (*this)-temp;
}

Long Long::operator*(int a)
{
	Long result;
	if (a==0 || (*this)==result) return result;
	int carry_over=0;
	int temp_result;
	for(int i=0; i<(int)number.size(); ++i)
	{
		temp_result=a*number[i]+carry_over;	
		carry_over=temp_result/BASE;
		result.number.push_back(temp_result%BASE);
	}
	if (carry_over!=0)
	{
		while(carry_over>=BASE)
		{
			result.number.push_back(carry_over%BASE);
			carry_over/=BASE;
		}
		result.number.push_back(carry_over);
	}
	return result;
}

void reverse(vector <int> & b)
{
	int temp=0;
	for (unsigned int i=0; i<b.size()/2; ++i)
	{
		temp=b[i];
		b[i]=b[b.size()-1-i];
		b[b.size()-1-i]=temp;
	}
}

Long Long::operator/(int a)
{
	if(a==0) return Long();
	int temp;
	int carry_over=0;
	Long result;
	for(int  i=number.size()-1; i>=0; --i)
	{
		temp=number[i]+carry_over*BASE;
		result.number.push_back(temp/a);
		carry_over=temp%a;
	}
	reverse(result.number);
	return result;
}

bool Long::operator!=(Long a)
{
	del_zeros();
	a.del_zeros();
	if (number.size()!=a.number.size()) return true;
	while (a.number.size() < number.size()) a.number.push_back(0);
	while (a.number.size() > number.size()) number.push_back(0);
	if (number.size()==0) return false;
	for (int i=0;i<(int)number.size();++i)
		if ((number[i])!=(a.number[i])) return true;
	return false;
}

bool Long::operator<(Long a)
{
	del_zeros();
	a.del_zeros();
	if (number.size() < a.number.size()) return true;
	else if (number.size() > a.number.size())return false;
	int i = number.size() - 1;
	while (i>=0 && number[i] == a.number[i])--i;
	if (i==-1)return false;
	return number[i] < a.number[i];
}

bool Long::operator>(Long a)
{
	del_zeros();
	a.del_zeros();
	if (number.size() > a.number.size()) return true;
	else if (number.size() < a.number.size()) return false;
	int i = number.size() - 1;
	while (i>=0 && number[i] == a.number[i])--i;
	if (i==-1)return false;
	return number[i] > a.number[i];
}

bool Long::operator<=(Long a)
{
	del_zeros();
	a.del_zeros();
	if (number.size() < a.number.size()) return true;
	else if (number.size() > a.number.size())return false;
	int i = number.size() - 1;
	while (i>=0 && number[i] == a.number[i])--i;
	if (i==-1) return true;
	return number[i] < a.number[i];
}

bool Long::operator>=(Long a)
{
	del_zeros();
	a.del_zeros();
	if (number.size() > a.number.size()) return true;
	else if (number.size() < a.number.size())return false;
	int i = number.size() - 1;
	while (i>=0 && number[i] == a.number[i])--i;
	if (i==-1)return false;
	return number[i] < a.number[i];
}

void Long::toLong(string a)
{
	string X=a;
	string rest;
	X=str_divide(a,BASE,rest);
	while(atoi(X.c_str())!=0)
	{
		number.push_back(atoi(rest.c_str()));	
		X=str_divide(X,BASE,rest);
	}
	number.push_back(atoi(rest.c_str()));
}

string operator+(string b,string a)
{
	string res;
	char buf[MAX_BUF];
	vector<int> dec;
	int temp=0;
	int k=(int)a.size()-(int)b.size();
	if(k>0)//a>b
		for(int i=0;i<k;++i)
			b.insert(0,"0");
	else
	{
		k=-k;
		for(int i=0;i<k;++i)
			a.insert(0,"0");
	}
	for(int i=a.size()-1,j=b.size()-1; i>=0 && j>=0; --i,--j)
	{
		temp+=(int)a[i]-48+(int)b[j]-48;
		if(temp<10) {dec.push_back(temp);temp=0;}
		else {temp=temp-10;dec.push_back(temp);temp=1;}
	}
	if(temp!=0)dec.push_back(temp);
	for(int i=(int)dec.size()-1;i>=0;--i){
		_itoa_s(dec[i],buf,10);
		res.append(buf);
	}
	return res;
}

string operator*(string a, string b)//множення у стовпчик
{
	string result="0";
	string temp="";
	char buf[MAX_BUF];
	if(a.size()<b.size()) a.swap(b);
	//a>b
	int t;
	int carry_over=0;
	bool c=true;
	for(int i=(int)b.size()-1; i>=0; --i)
	{
		carry_over=0;
		for(int j=(int)a.size()-1; j>=0; --j)
		{
			t=b[i]-48;
			t=t*(a[j]-48) + carry_over;
			carry_over=t/10;
			_itoa_s(t%10,buf,10);
			temp.insert(0,buf);
		}
		_itoa_s(carry_over,buf,10);
		temp.insert(0,buf);
		for(int t=i+1; t<(int)b.size(); ++t)
			temp.append("0");//реалізується здвиг
		result=result+temp;
		temp="";
	}
	str_del_zeros(result);
	return result;
}

string str_divide(string a, int b, string & rest)//a/b
{
	int base_iter=1;
	for(int x=b;x/10!=0;x=x/10)
		base_iter++;
	string result;
	char buf[MAX_BUF];
	memset(buf,Long::BASE,0);
	int iter=base_iter;
	int size=(int)a.size();
	int i=0;
	while(1)
	{
		iter=base_iter;
		int X=atoi(a.substr(i,iter).c_str());//переводимо підрядок у char*
		if((int)a.size() >= i+iter)
			{if(X<b) X=atoi(a.substr(i,(++iter)).c_str());}
		else 
			{
				rest=a;
				break;
			}
		if(X<b && (int)a.size() > i+iter)
		{
			result.append("0");
			X=atoi(a.substr(i,(++iter)).c_str());
		}
		_itoa_s(X/b,buf,10);
		if(strcmp(buf,"")==0) strcpy_s(buf, "0");
		result.append(buf);
		_itoa_s(X%b,buf,10);
		rest=buf;
		if(i+iter >= (int)a.size()) break;
		if(rest=="")rest="0";
		while((int)rest.size() < base_iter)
			rest=rest.insert(0,"0");
		a.insert(iter+i,rest);//вставляэмо решту після символів, які ми вже використовували
		i+=iter;
	}
	return result;
}

string Long::toStr()const
{
	if(number.size()==0) return "";
	string result;
	char buf[MAX_BUF];
	_itoa_s(number[0],buf,10);
	result.append(buf);
	string temp;
	string base;	
	_itoa_s(BASE,buf,10);
	base=buf;
	string temp_base=base;
	for(int i=1; i<(int)number.size(); ++i)
	{
		_itoa_s(number[i],buf,10);
		temp=string(buf)*temp_base;
		result=result+temp;
		temp_base=temp_base*base;
	}
	str_del_zeros(result);
	return result;
}

void Long::del_zeros()
{
	while (number.size() != 0 && number[number.size()-1]==0) number.pop_back();
}

void str_del_zeros(string &a)
{
	int i;
	for(i=0; i<(int)a.length() && a[i]=='0'; ++i);
	a.erase(0,i);
}

int Long::operator%(int a)
{
	if (a==0) return -1;
	int temp;
	int carry_over=0;
	for(int  i=number.size()-1; i>=0; --i)
	{
		temp=number[i]+carry_over*BASE;
		carry_over=temp%a;
	}
	return carry_over;
}

vector<int> operator+(vector<int> a,vector<int> b)
{
	int carry_over=0;
	int temp_res;
	vector<int> res;
	while(a.size()<b.size())a.push_back(0);
	while(a.size()>b.size())b.push_back(0);
	for(int i=0;i<(int)a.size();i++)
	{
		temp_res=a[i]+b[i]+carry_over;
		res.push_back(temp_res%10);
		carry_over=temp_res/10;
	}
	if(carry_over!=0)res.push_back(carry_over);
	return res;
}

vector<int> operator*(vector<int> a,int b)
{
	vector<int> res;
	if(b==0||a==res)return res;
	int carry_over=0;
	int temp_res;
	for(int i=0; i<(int)a.size(); ++i)
	{
		temp_res=b*a[i]+carry_over;	
		carry_over=temp_res/10;
		res.push_back(temp_res%10);
	}
	if(carry_over!=0)res.push_back(carry_over);
	return res;
}

vector<int> operator*(vector<int> a,vector<int> b)
{
	int carry_over=0;
	vector<int> res;
	//==0
	if(a==res||b==res)return res;
	vector<int> temp;
	if(a.size()>b.size())a.swap(b);
	for(int i=0;i<(int)a.size();++i)
	{
		temp=b*a[i];
		for(int j=0;j<i;++j)
			temp.insert(temp.begin(),0);
		res=res+temp;
	}
	return res;
}

vector<int> Long::to_Binary()const
{
	Long X=(*this);
	vector<int> result;
	for(int i=0,k=0; i<X.number.size(); ++i)
	{
		k=1;
		while(X.number[i]/2!=0)
		{
			result.push_back(X.number[i]%2);
			X.number[i]=X.number[i]/2;
			++k;
		}
		result.push_back(X.number[i]%2);
		while(k<15){result.push_back(0);++k;}
	}
	while(result[result.size()-1]==0) result.pop_back();
	return result;

}

void Long::fromBin(vector<int> b)
{
	number.clear();
	int i=0;
	int temp=0;
	int base=1;
	for(i=0; i<b.size(); i+=15)
	{
		base=1;
		temp=0;
		for(int j=0; j<15 && i+j<b.size(); ++j)
		{
			temp=temp+base*b[i+j];
			base*=2;
		}
		number.push_back(temp);
	}
}

Long Long::operator^(const Long &n)
{
	vector<int> m;
	m=n.to_Binary();
	Long s=(*this);
	for(int i=(int)m.size()-2; i>=0; --i)
		if(m[i]==0)s=s*s;
		else s=s*s*(*this);
	return s;
}

Long Long::operator/(Long a)
{
	Long result;
	vector<int> c,d;
	del_zeros();
	a.del_zeros();
	for(int i=number.size()-1; i>=0; --i)
		c.push_back(number[i]);
	for(int i=a.number.size()-1; i>=0; --i)
		d.push_back(a.number[i]);
	vector<int> res=divideVectorByVector(c,d,BASE);
	for(int i=res.size()-1; i>=0; --i)
		result.number.push_back(res[i]);
	return result;
}

Long Long::operator%(Long a)
{
	Long result;
	vector<int> c,d;
	del_zeros();
	a.del_zeros();
	for(int i=number.size()-1; i>=0; --i)
		c.push_back(number[i]);
	for(int i=a.number.size()-1; i>=0; --i)
		d.push_back(a.number[i]);
	vector<int> res=moduloVector(c,d,BASE);
	for(int i=res.size()-1;i>=0;--i)
		result.number.push_back(res[i]);
	return result;
}

Long Long::Primitive(Long a)
{
	int carry_over=0;
	Long result;
	if(a==result||(*this)==result) return result;
	Long temp;
	if(number.size() > a.number.size()) number.swap(a.number);
	for(int i=0;i<(int)number.size();++i)
	{
		temp=a*number[i];
		for(int j=0;j<i;++j)
			temp.number.insert(temp.number.begin(),0);
		result=result+temp;
	}
	return result;
}

Long Long::Karatsuba(Long a)
{
	while(number.size()<a.number.size())	
		number.push_back(0);
	while(number.size()>a.number.size())
		a.number.push_back(0);

	if(number.size()%2!=0)
	{
		a.number.push_back(0);
		number.push_back(0);
	}

	int n=number.size();
	int m=n/2;

	Long A1,A0,B0,B1;
	Long result;
	
	int i=0;
	for(i=0;i<m;++i)
		A0.number.push_back(number[i]);
	for(;i<n;++i)
		A1.number.push_back(number[i]);
	for(i=0;i<m;++i)
		B0.number.push_back(a.number[i]);
	for(;i<n;++i)
		B1.number.push_back(a.number[i]);
	
	result = A0.Primitive(B0);
	Long res1 = A1.Primitive(B1);
	Long res2 = ((A0+A1).Primitive((B0+B1)) - result - res1);
	for (int i=0; i<m; ++i)
		res2.number.insert(res2.number.begin(),0);
	for (int i=0; i<n; ++i)
		res1.number.insert(res1.number.begin(),0);
	result=result+res1+res2;
	return result;
}

Long Long::Cook (Long a)
{
	while(number.size()<a.number.size())	
		number.push_back(0);
	while(number.size()>a.number.size())
		a.number.push_back(0);

	Long result;
	int n=number.size();
	const Long cod1("-1"),cod2("-2"),cod3("-3"),cod4("-4");
	stack<int> A;
	stack<Long> U,V,C,W;
	int k,Q,R;
	list<int> q,r;
	k=1; Q=4; R=2;
	q.push_back(16); q.push_back(16);
	r.push_back(4); r.push_back(4);
	list<int>::iterator i=q.begin();
	while((*i)+*(++i)<n)
	{
		++k; 
		Q+=R;
		if((R+1)*(R+1)<=Q)++R;
		q.push_back((int)pow(2.,Q));
		r.push_back((int)pow(2.,R));
	}
	int p=(*i)+*(--i);
	while((int)number.size()<p)
	{
		a.number.push_back(0);
		number.push_back(0);
	}
	C.push(cod1);
	C.push(a);
	C.push(*this);
	
	while(true)
	{
		while(k>1)
		{
			--k;
			i=q.end(); --i;
			int s=*i;
			p=(*i)+*(--i);
			i=r.end();--i;
			int t=*i;
			Long top=C.top();
			vector<Long> u;
			for(int i=0, k=0; i<=t; ++i)
			{
				u.push_back(Long());
				for(int j=0; j<s && k<(int)top.number.size(); ++j)
				{
					u[i].number.push_back(top.number[k++]);
				}
				while(int(u[i].number.size())<s) 
					u[i].number.insert(u[i].number.begin(),0);
			}
	
			Long K;
			Long i0;
			for(int j=0; j<=t+t; ++j)
			{
				int l=1;
				K.number.clear();
				for(int i=u.size()-1; i>=0; --i)
				{
					K=u[i]*l+K;
					l*=j;
				}
				U.push(K);
			}
			C.pop();
			top=C.top();
			u.clear();
			for(int i=0,k=0; i<=t; ++i)
			{
				u.push_back(Long());
				for(int j=0; j<s && k<(int)top.number.size(); ++j)
				{
					u[i].number.push_back(top.number[k++]);
				}
				while(int(u[i].number.size())<s) 
					u[i].number.insert(u[i].number.begin(),0);
			}
			K.number.clear();
			for(int j=0; j<=t+t; ++j)
			{
				int l=1;
				K.number.clear();
				for(int i=u.size()-1; i>=0; --i)
				{
					K=u[i]*l+K;
					l*=j;
				}
				V.push(K);
			}
			C.pop();
			C.push(cod2);
			C.push(U.top());
			C.push(V.top());
			U.pop();V.pop();
			for(int i=0;i<t+t;++i)
			{
				C.push(cod3);
				C.push(U.top());
				C.push(V.top());
				U.pop();
				V.pop();
			}
		}

	Long w,u,v;
	u=C.top(); C.pop();
	v=C.top(); C.pop();
	w=u.Primitive(v);
		while(k<=1)
		{
			while(C.top()==cod3)
			{
				C.pop();
				W.push(w);
				u=C.top();C.pop();
				v=C.top();C.pop();
				w=u.Primitive(v);
			}
			if(C.top()==cod2)
			{
				k++;
				W.push(w);
				C.pop();
				i=q.end();--i;
				int s=*i;
				p=(*i)+*(--i);
				i=r.end();--i;
				int t=*i;
				vector<Long> l;
				while(!W.empty())
				{
					l.push_back(W.top());
					W.pop();
				}
				Long temp;
				for(int i=0; i<(int)l.size()/2; ++i)
				{
					temp=l[i];
					l[i]=l[l.size()-1-i];
					l[l.size()-1-i]=temp;
				}
				for(int j=1; j<=t+t; ++j)
					for(int k=t+t; k>=j; --k)
						l[k]=(l[k]-l[k-1])/j;
				for(int j=t+t-1; j>0; --j)
					for(int k=j; k<t+t; ++k)
						l[k]=l[k]-l[k+1]*j;
				int k=1;
				w.number.clear();
				for(int i=l.size()-1; i>=0; --i)
				{
					w=l[i]*k+w;
					k*=s;
				}
			}
			if(C.top()==cod1)
				return w;
			if(C.top()==cod3||C.top()==cod2) k=1;
		}
	}  
}

Long Long::Shenchaga(Long a)
{
	while(number.size()<a.number.size())	
		number.push_back(0);
	while(number.size()>a.number.size())
		a.number.push_back(0);

	int q=1,p=26;
	if((int)number.size()<=p) return Primitive(a);
	while((int)number.size()>p)
	{
		q=q+q+q-1;
		p=18*q+8;
	}
	int m[6];
	m[0]=1;
	for(int i=0;i<6*q;++i)
		m[0]=m[0]*2;
	m[0]=m[0]/2-1; m[1]=m[0]*2-1;	m[2]=m[0]*4-1;	
	m[3]=m[0]*8-1; m[4]=m[0]*32-1;  m[5]=m[0]*128-1;

	int u[6],v[6],w[6];
	for(int i=0;i<6;++i)
	{
		u[i]=(*this)%m[i];
		v[i]=a%m[i];
		w[i]=(u[i]*v[i])%m[i];
	}

	int c[6][6];
	for(int i=0; i<6; ++i)
		for(int j=0; j<6; ++j)
		{
			int t=0;
			if(i!=j) for(;(t*m[i])%m[j]!=1;t++);
			c[i][j]=t;
		}	
	int W[6];
	W[0]=w[0];
	for(int i=1; i<6; ++i)
	{
		W[i]=((w[i]-W[0])*c[1][i]%m[i]+m[i])%m[i];
		for(int j=1;j<i;++j)	
			W[i]=((W[i]-W[j])*c[j][i]%m[i]+m[i])%m[i];
	}

	Long result;
 	result.number.push_back(W[5]);

	for(int i=4;i>=0;--i)
		result=result*m[i]+W[i];

	return result;
}

vector<int> summ(vector<int> a,vector<int> b,const int& base)
{
	int carry_over=0;
	int temp_result;
	vector<int> result;
	while(a.size()<b.size()) a.push_back(0);
	while(a.size()>b.size()) b.push_back(0);
	for(int i=0; i<(int)a.size(); i++)
	{
		temp_result=a[i]+b[i]+carry_over;
		result.push_back(temp_result%base);
		carry_over=temp_result/base;
	}
	if(carry_over!=0)result.push_back(carry_over);
	return result;
}

Long Long::mod(const int & n)
{
	vector<int> k;
	k=to_Binary();
	vector<int> k1,k2;
	while((int)k.size()>n)
	{
		k1.clear();
		k2.clear();
		for(int i=0; i<n; ++i)
			k1.push_back(k[i]);
		for(int i=n; i<(int)k.size(); ++i)
			k2.push_back(k[i]);
		k.clear();
		k=summ(k1,k2,2);
	}
	Long result;
	result.fromBin(k);
	return result;
}

bool Long::Lemer()
{
	int n=-1;
	if(!isMersenne(n))return false;
	Long s(4);
	for(int i=0; i<n-2; ++i)
		s=(s.Karatsuba(s)-2).mod(n);
	if(s==0) return true;
	Long M(2);
	M=(M^n)-1;
	if(s==M)return true;
	return false;
}

bool Long::isMersenne(int & p)
{
	if(number.size()==0)return false;
	Long x=(*this)+1;
	p=1;
	while(x!=2)
	{
		if(x.number[0]%2==1)return false;
		x=x/2;
		++p;
	}
	return true;
}

bool isPow2(const int &x)
{
	return ((x!=0)&&((x&(~x+1))==x));
}

Long Long::CookDivide(Long v)
{
	int m=number.size();
	int n=v.number.size();
	Long rеsult;
	int k=1,j=0;
	while(k<(BASE*n) || k<(BASE*m-BASE*n)) {k*=BASE;++j;}
	
	k=k/BASE;
	rеsult=(*this)/v;
	if(k!=BASE-1) return rеsult;

	v.number.insert(v.number.begin(),k-n,0);
	
	Long a=BASE;
	Long d;
	Long a1;
	Long temp;

	for(int i=1;i<j;++i)
	{
		temp=v;
		temp.number.erase(temp.number.begin(),temp.number.begin()+k-i-i);
		a.del_zeros();
		a1=a;
		a1.number.insert(a1.number.begin(),3*(int)pow((double)BASE,i),0);//2
		d=a1-a*a*temp;
		a=d;
		a.number.erase(a.number.begin(),a.number.begin()+i-1);
	}

	d.number.erase(d.number.begin(),d.number.end()-k-k);
	a.number.erase(a.number.begin(),a.number.end()-k);
	a1=a;
	a1.number.insert(a1.number.begin(),k+k,0);

	d=a1-a*a*v;
	Long l=1;
	l.number.insert(l.number.begin(),k+k-1,0);
	a=(d+l);
	a.number.erase(a.number.begin(),a.number.begin()+k+k-1);
	Long result;
	l=1;
	l.number.insert(l.number.begin(),k+n-1,0);
	result=a*(*this)+l;
	result=result+l;
	result.number.erase(result.number.begin(),result.number.begin()+k+n-1);
	return rеsult;
}

vector<complex<double>> fft(vector<complex<double>> number)
{
	if(number.size()==1) return vector<complex<double>>(1,number[0]);
	while(!isPow2(number.size()))number.push_back(0);	
	int n=number.size();
	vector<complex<double>> A;
	vector<complex<double>> B;
	for(int i=0;i<n;++i)
	{
		if(i%2==0) A.push_back(number[i]);
		else B.push_back(number[i]);
	}
	vector<complex<double>> w;
	double temp;
	for(int i=0;i<n;++i)
	{
		temp=2*pi*i/n;
		w.push_back(complex<double>(cos(temp),sin(temp)));
	}

	vector<complex<double>> A1=fft(A);
	vector<complex<double>> B1=fft(B);
	vector<complex<double>> result;
	for(int i=0;i<n;++i)
	{
		result.push_back(A1[i%(n/2)]+w[i]*B1[i%(n/2)]);
	}
	return result;
}

vector<complex<double>> fft_rev(vector<complex<double>> result)
{
	vector<complex<double>> number=fft(result);
	int n=number.size();
	for(int i=0; i<(int)number.size(); ++i)
		number[i]/=n;
	complex<double> temp=0;
	for(int i=1; i<n/2; ++i)
	{
		temp=number[i];
		number[i]=number[n-i];
		number[n-i]=temp;
	}
	return number;
}

long long round(double x)
{
	long long d=(long long) x;
	double eps=x-d;
	if(eps<0.5) return d;
	return d+1;
}

Long Long::ShenchShtrass(Long a){

	while(number.size()<a.number.size())	
		number.push_back(0);
	while(number.size()>a.number.size())
		a.number.push_back(0);

	vector<complex<double>> u,v;

	for(int i=0;i<(int)number.size();++i)
		u.push_back(complex<double>(number[i],0));
	for(int i=0;i<(int)a.number.size();++i)
		v.push_back(complex<double>(a.number[i],0));
	

	for(int i=0;i<(int)number.size();++i)
		u.push_back(complex<double>(0,0));
	for(int i=0;i<(int)a.number.size();++i)
		v.push_back(complex<double>(0,0));
	
	vector<complex<double>> u1,v1,w;
	u1=fft(u);v1=fft(v);
	for(int i=0;i<v1.size();++i)
	{
		w.push_back(u1[i]*v1[i]);
	}
	u.clear();
	u=fft_rev(w);
	Long result;
	for(int i=0;i<u.size();++i)
		result.number.push_back(round(u[i].real()));
	int carry_over=0;
	for(int i=0;i<result.number.size();++i)
	{
		result.number[i]+=carry_over;
		if(result.number[i]>BASE)
		{
			carry_over=result.number[i]/BASE;
			result.number[i]%=BASE;
		}
		else carry_over=0;
	}
	while(carry_over!=0)
	{
		if(carry_over>BASE)
		{
			result.number.push_back(carry_over%BASE);
			carry_over/=BASE;}
		else 
		{
			result.number.push_back(carry_over);
			carry_over =0;
		}
	}
	return result;
}

Long Long::IndPowMod(const Long &n, const Long &m)
{
	vector<int> k;
	k=n.to_Binary();
	Long s=(*this);
	for(int i=(int)k.size()-2;i>=0;--i)
		if(k[i]==0)s=(s*s)%m;
		else {s=(s*s)%m; s=(s*(*this))%m;}
	return s;
}

bool Long::MillerRabin(const int &r)
{
	if(number.size()==0)return false;
	Long t=(*this)-1;
	if(t.number[0]%2==1)return false;
	int s=1;
	while(t%2==0)
	{
		t=t/2;
		++s;
	}
	srand(unsigned(time(NULL)));
	Long x,a;
	Long m1=(*this);
	m1.number[0]-=1;
	for(int i=0;i<r;++i)
	{
		int size;
		if(number.size()==1)
		{
			size=1;
			a=rand()%(number[0]-2)+2;
		}
		else if(number.size()==2)
		{
			size = rand()%2+1;
			a.number.push_back(rand()%(number[0]-2)+2);
		}
		else
		{
			size=rand()%(number.size()-2)+2;
			for(int i=0;i<size;++i)
				a.number.push_back((rand()%BASE));
		}		
		x=a.IndPowMod(t,(*this));
		if(x==1 || x==m1) continue;
		int j=0;
		for(j=0; j<s-1; ++j)
		{
			x=(x*x)%(*this);
			if(x==1)return false;
			else if(x==m1)break;
		}
		if(j!=s-1)continue;
		return false;
	}
	return true;
}

bool Long::SolovejShtrassen(int k)
{
	int base=BASE;
	vector<int> m=number;
	reverse(m);
	if(base!=10)
	{
		base=10;
		convertFromBase(m, base);
	}
	srand(time(NULL));
	for(int j=0; j<k; j++)
	{
	vector<int> w,temp,one(1,1),bin(1,2);
	int size=rand()%(m.size()-2)+1;
	if (size<m.size()/10)
		size+=2*m.size()/10;
	for(int i=0; i<size; i++)
		w.push_back(rand()%9+1);
	if(gcd(m,w,base)!=one)
		return false;
	temp=divideVectorByVector(subtractVectors(m,one,base),bin,base);
	vector<int> q1=IpowVector(w,temp,m,base);
	vector<int> q2=yakobi(w,m,base);
	if(q2!=one && q2!=subtractVectors(m,one,base))
		return false;
	if(q1!=q2)
		return false;
	}
	return true;
}