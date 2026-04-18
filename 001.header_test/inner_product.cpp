#include<sungso376_LA.hpp>
#include<vector>
#include<iostream>
using namespace std;
int main(void){
    vector<double> a,b;
    int N;cin>>N;
    a.resize(N);b.resize(N);
    for(int i=0;i<N;i++)cin>>a[i];
    for(int i=0;i<N;i++)cin>>b[i];
    cout<<inner_product(a,b);
}