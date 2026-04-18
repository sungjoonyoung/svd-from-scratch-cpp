#include<sungso376_LA.hpp>
#include<sungso376_debbuging.hpp>
#include<vector>
#include<iostream>
using namespace std;
int main(void){
    vector<vector<double>> a,b;
    int X,Y,Z;cin>>X>>Y>>Z;
    for(int i=0;i<X;i++){
        a.push_back(vector<double>());
        for(int j=0;j<Y;j++){
            double in;cin>>in;
            a[i].push_back(in);
        }
    }
    for(int i=0;i<Y;i++){
        b.push_back(vector<double>());
        for(int j=0;j<Z;j++){
            double in;cin>>in;
            b[i].push_back(in);
        }
    }
    print_2D(a);
    print_2D(b);
    vector<vector<double>> tmp=mat_mul(a,b);
    print_2D(tmp);
}