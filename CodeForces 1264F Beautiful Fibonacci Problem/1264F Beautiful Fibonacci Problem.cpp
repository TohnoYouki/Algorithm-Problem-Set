#include<iostream>
using namespace std;
int main()
{	
	long long n, a, d;
	cin >> n >> a >> d;
	long long b = ((a * 574725245) % 1000000000) * 1500000000;
	long long e = ((d * 574725245) % 1000000000) * 1500000000;
	cout << b << " " << e;
	return 0;
}