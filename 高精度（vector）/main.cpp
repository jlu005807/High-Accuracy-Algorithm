#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdio>
#include<math.h>
#include <cstring>
using namespace std;


vector<int> sub(vector<int>, vector<int>);

ostream& operator<<(ostream& out, const vector<int> a)
{
	if (a.size() == 2 && a[1] == 0)return out << 0;
	if (a[a.size() - 1] == 0)out << "-";

	for (int i = a.size() - 2; i >= 0; i--)out << a[i];
	return out;

}

bool cmp(vector<int> a, vector<int> b)
{
	if (a.size() != b.size())return a.size() > b.size();
	for (int i = a.size() - 2; i >= 0; i--) {
		if (a[i] != b[i])return a[i] > b[i];
	}
	return true;
}


vector<int> add(vector<int> a, vector<int> b)
{
	if (a[a.size() - 1] ^ b[b.size() - 1]) {
		if (a[a.size() - 1] == 1)
		{
			b[b.size() - 1] = 1;
			return sub(a, b);
		}
		else
		{
			a[a.size() - 1] = 1;
			return sub(b, a);
		}
	}
	if (a.size() < b.size())return add(b, a);
	vector<int> c;

	int t = 0, n;
	for (int i = 0; i < b.size()-1; i++)
	{
		n = t / 10;
		t = a[i] + b[i] + n;
		c.push_back(t % 10);
	}
	for (int i = b.size()-1; i < a.size()-1; i++) {
		n = t / 10;
		t = a[i] + n;
		c.push_back(t % 10);
	}
	if (t >= 10)c.push_back(t / 10);
	c.push_back(a[a.size() - 1] * b[b.size() - 1]);
	return c;
}


vector<int> sub(vector<int> a, vector<int> b)
{
	if (a[a.size() - 1] ^ b[b.size() - 1]) {
		if (a[a.size() - 1] == 1)
		{
			b[b.size() - 1] = 1;
			
			return add(a, b);
		}
		else
		{
			b[b.size() - 1] = 0;
			return add(b, a);
		}
	}
	int flag = 0;
	if (cmp(b, a))
	{
		flag = 1;
		vector<int>v;
		v = a;
		a = b;
		b = v;
	}
	int t = 0;
	vector<int> c;
	for (int i = 0; i < a.size()-1; i++)
	{
		t = a[i] - t;
		if (i < b.size()-1)t -= b[i];
		c.push_back((t + 10) % 10);
		if (t < 0)t = 1;
		else t = 0;
	}
	while (c.size() > 1 && c.back() == 0)c.pop_back();
	if (flag)c.push_back(0);
	else c.push_back(1);

	return c;

}

vector<int> mul(vector<int> a, vector<int> b)
{
	if (a.size() < b.size())return mul(b, a);
	vector<int>c, v;
	int t = 0;
	for (int i = 0; i < b.size()-1; i++)
	{
		v.clear();
		for (int j = 0; j < i; j++)v.push_back(0);
		t = 0;
		for (int j = 0; j < a.size()-1; j++)
		{
			if (b[i] == 0) {
				v.push_back(b[i]);
				break;
			}
			t = a[j] * b[i] + t / 10;

			v.push_back(t % 10);
		}
		if (t >= 10) {
			v.push_back(t / 10);
		}
		v.push_back(1);
		if (i == 0)c = v;
		else c = add(v, c);
	}
	
	if (a[a.size() - 1] ^ b[b.size() - 1])c[c.size() - 1] = 0; 
	return c;
}

vector<int> vert(string str)
{
	vector<int> num;
	for (int i = str.size() - 1; i > 0; i--)
	{
		num.push_back(str[i] - '0');
	}
	if (str[0] == '-')num.push_back(0);
	else {
		num.push_back(str[0] - '0');
		num.push_back(1);
	}
	return num;
}

vector<int> div(vector<int>a, int b)
{
	vector<int>c;
	int r = 0;
	for (int i = a.size() - 2; i >= 0; i--)
	{
		r = r * 10 + a[i];
		c.push_back(r / b);
		r %= b;
	}
	reverse(c.begin(), c.end());
	while (c.size() > 1 && c.back() == 0)c.pop_back();
	if (a[a.size() - 1] * b > 0) {
		if (b < 0)c.push_back(0);
		else c.push_back(1);
	}
	else
	{
		if (b > 0)c.push_back(0);
		else c.push_back(1);
	}
	return c;
}

vector<int> div(vector<int> a, vector<int> b)
{
	vector<int>m, n,r,one,c;
	one.push_back(1);
	one.push_back(1);
	c.push_back(0);
	c.push_back(1);
	m = a, n = b;
	m[m.size() - 1] = 1;
	n[n.size() - 1] = 1;
	r = sub(m, n);
	if (r[r.size() - 1] != 0)c = add(c,one);
	while (cmp(r, n) && r[r.size() - 1] != 0) {
		/*if(c[0]==0&&c.size()==2)c = add(c, one);*/
		c = add(c, one);
		r = sub(r, n);

	}
	if (a[a.size() - 1] ^ b[b.size() - 1])c[c.size() - 1] = 0;
	return c;
}

int main()
{
	string m, n;
	vector<int>a, b;
	vector<int> c;
	cin >> m >> n;
	a = vert(m);
	b = vert(n);
	c = add(a, b);
	cout << c;

	
}