#include "random.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <stdlib.h>

#define SIZE 1e+5

using namespace std;
int main()
{
	srand(time(NULL));
	vector<long long int> v(100), w(100);
	for(long long int i = 0; i < SIZE; i++)
	{
		v[WELLRNG512() % 100]++;
		w[rand()%100] ++;
	}	

	long long int mmin = SIZE, mmax = 0, smin = SIZE, smax = 0;
	long long int sum = 0, ssum = 0;
	for(long long int i = 0; i < 100; i++)
	{
		cout << i << ": " << v[i] << "\t" << w[i] << endl;
		if(mmin > v[i])
			mmin = v[i];
		if(mmax < v[i])
			mmax = v[i];
		if(smin > w[i])
			smin = w[i];
		if(smax < w[i])
			smax = w[i];
		ssum += w[i];
		sum += v[i];
	}

	cout << "WELLRNG\nmin: " << mmin <<endl<< "max: "<<mmax<<endl<<"avr: "<<(double)(sum/100.)<<endl << "err: " << ((double)(mmax-mmin) / 100)<<endl;
	cout << "RAND()\nmin: " << smin <<endl<< "max: "<<smax<<endl<<"avr: "<<(double)(ssum/100.)<<endl << "err: " << ((double)(smax-smin) / 100)<<endl;

}