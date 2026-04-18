#include<sungso376_LA.hpp>
#include<sungso376_debbuging.hpp>
#include<vector>
#include<iostream>
using namespace std;
int main(void){
    int N,M;cin>>N;
    vector<double>A,B;A.resize(N);B.resize(N);
    for(int i=0;i<N;i++)cin>>A[i];
    for(int i=0;i<N;i++)cin>>B[i];
    vector<double>tmp=vec_AminusB(A,B);
    print_1D(tmp);
}