#pragma once
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

auto eigen_export(const vector<vector<double>>&A,int max_iter=1000){
   // QR algorithm
   v.push_back(element());
   v[0].A=A;
   v[0].QR=QRD_GS(A);
   for(int i=1;i<max_iter;i++){
      v.push_back(element());
      v[i].A=mat_mul(v[i-1].QR.R,v[i-1].QR.Q);
      v[i].QR=QRD_GS(v[i].A);
   }
   // eigen value
   eigen_v.resize(A.size());
   for(int i=0;i<eigen_v.size();i++) eigen_v[i].value=v.back().A[i][i];
   // eigen vector
   vector<vector<double>> big_V=mat_identity(A.size());
   for(int i=0;i<v.size();i++){
      big_V=mat_mul(big_V,v[i].QR.Q);
   }
   for(int i=0;i<eigen_v.size();i++){
      eigen_v[i].vector.resize(big_V[i].size());
      for(int j=0;j<big_V[i].size();j++){
         eigen_v[i].vector[j]=big_V[j][i];
      }
   }
   // // 중간 체크
   // for(int i=0;i<eigen_v.size();i++){
   //    cout<<eigen_v[i].value<<" ";
   // }
   // for(int i=0;i<eigen_v.size();i++){
   //    print_1D(eigen_v[i].vector);
   // }
   
   return eigen_v;
}
/*
1 2 3
5 4 1
5 3 1
*/