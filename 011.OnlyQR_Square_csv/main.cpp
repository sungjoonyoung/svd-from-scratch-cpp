#include<iostream>
#include<fstream>
#include<sungso376_LA.hpp>
#include<sungso376_debbuging.hpp>
#include<sungso376_eigen.hpp>
using namespace std;
vector<double> big_S;
vector<vector<double>> big_U,big_V;

int main(void){
   //init
   cout<<"N=";int N;cin>>N;cout<<"\n";N=22;
   cout<<"max iter=";int iter;cin>>iter;cout<<"\n";
   
   vector<vector<double>>A;
   ifstream fin;fin.open("main.csv");
   A=read_node(fin,N,2);
   for(int i=0;i<N;i++)for(int j=0;j<N;j++){
      if(A[i][j]==0)A[i][j]+=1e-5;
   }

   //
   auto ATA=mat_mul(mat_transpose(A),A);
   auto eigen_ATA=eigen_export(ATA,iter,1);
   for(int i=0;i<eigen_ATA.size();i++)big_S.push_back(eigen_ATA[i].value);
   for(int i=0;i<eigen_ATA.size();i++)big_V.push_back(eigen_ATA[i].vector);
   big_U=mat_transpose(mat_mul(A,mat_transpose(big_V)));
   // for(int i=0;i<A.size();i++){ // 지금 bigU는 row로 누어 있는 상태
   //    for(int j=0;j<A.size();j++){
   //       big_U[i][j]/=big_U[i];
   //    }
   // }

   //
   auto re=mat_zero(A.size());
   for(int i=0;i<A.size();i++){
      re=mat_plus(re,vecvec_to_mat(big_U[i],big_V[i]));
   }
   cout<<"big UT==";
   print_2D(big_U);
   cout<<"big S==";
   print_1D(big_S);
   cout<<"big VT==";
   print_2D(big_V);
   cout<<"USV==";
   print_2D(re);
}
/*
1 2 3
5 4 1
5 3 1
*/

/*
1 5 2 6
7 4 2 1
5 8 5 3
6 2 1 8
*/