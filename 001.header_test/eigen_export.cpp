#include<iostream>
#include<fstream>
#include<sungso376_STR.hpp>
#include<sungso376_LA.hpp>
#include<sungso376_debbuging.hpp>
#include<sungso376_eigen.hpp>
using namespace std;


int main(void){
   //init
   cout<<"N=";int N;cin>>N;cout<<"\n";
   cout<<"max iter=";int iter;cin>>iter;cout<<"\n";
   vector<vector<double>>A;
   for(int i=0;i<N;i++){
      A.push_back(vector<double>());
      A[i].resize(N);
      for(int j=0;j<N;j++)cin>>A[i][j];
   }
   auto tmp=eigen_export(A,iter,1);
   
   for(int i=0;i<tmp.size();i++)cout<<tmp[i].value<<" ";
   cout<<"\n";
   for(int i=0;i<tmp.size();i++)print_1D(tmp[i].vector);
}
/*
1 2 3
5 4 1
5 3 1
*/