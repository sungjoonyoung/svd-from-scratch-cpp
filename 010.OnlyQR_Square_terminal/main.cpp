#include<iostream>
#include<fstream>
#include<sungso376_STR.hpp>
#include<sungso376_LA.hpp>
#include<sungso376_debbuging.hpp>
using namespace std;
typedef struct{
   vector<vector<double>> A;
   QR QR;
}element;
typedef struct {
   double value;
   vector<double>vector;
}eigen;
vector<element>v;
vector<eigen> eigen_v;

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
   
   
}
/*
1 2 3
5 4 1
5 3 1
*/