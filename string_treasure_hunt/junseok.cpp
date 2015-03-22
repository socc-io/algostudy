#include<iostream>

using namespace std;

int main(){
	int a,b,cnt;
	cin>>a>>b;
	cin>>cnt;
	char p;int q;
	int j=0,k=0;
	for(int i=0;i<cnt;i++){
		cin>>q>>p;
		if(p=='S'){q*=-1;}
		else if(p=='W'){q*=-1;}
	
		if(p=='W'||p=='E'){
			j+=q;
		}
		else{
			k+=q;
		}
	}
	
	if(a==j&&b==k){
		cout<<"Treasure Found"<<endl;
	}else{cout<<"Bad Map"<<endl;}


}