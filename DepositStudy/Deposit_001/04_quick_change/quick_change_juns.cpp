#include<iostream>

using namespace std;

int main(){
	double change;
	int quartes = 25;
	int dimes = 10;
	int nickels = 5;
	int pennies = 1;

	int Q=0,D=0,n=0,P=0;
	cin >> change ;

	int ch = change;// * 100;

	while (ch != 0){
		if(ch>=quartes){
			Q = ch / quartes;
			ch %= quartes;
		}
		else if(ch<quartes&&ch>=dimes){
			D = ch / dimes;
			ch %= dimes;
		}
		else if(ch<dimes&&ch>=nickels){
			n = ch / nickels;
			ch %= nickels;
		}
		else{
			P = ch /pennies;
			ch %= pennies;
		}
	}
	cout<<Q <<" QUARTER(S), "<<D <<" DIME(S), "<<n <<" NICKEL(S), "<<P <<" PENNY(S)"<<endl;
}