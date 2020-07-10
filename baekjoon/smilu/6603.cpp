#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;


int k=6;
void perm(int n,vector<int> lotto){
   vector<int> ind;
   for(int i=0; i<k; i++){
      ind.push_back(0);
   }
   for(int i=0; i<lotto.size()-k; i++){
      ind.push_back(1);
   }

   do{
      for(int i=0; i<ind.size(); i++){
         if(ind[i]==0) cout<<lotto[i]<<" ";
      }
      cout<<"\n";
   }while(next_permutation(ind.begin(),ind.end()));
   cout<<"\n";
   return;
}
int main() {
   int a;
   while(1){
      int n;
      cin>>n;
      vector<int> lotto;
      if(n==0) break;
      for(int i=0; i<n; i++){
         int a;
         cin>>a;
         lotto.push_back(a);
      }
      perm(n,lotto);
   }
   
   return 0;
}
