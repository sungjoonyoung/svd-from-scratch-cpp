#include<iostream>
#include<vector>
#include<sungso376_LA.hpp>
using namespace std;
int main(void){
    vector<double>v;
    v.resize(3);
    v[0]=0.741028;
    v[1]=1.14033;
    v[2]=1;
    for(int i=0;i<3;i++){
        cout<<v[i]/(sqrt(inner_product(v,v)))<<" ";
    }
}