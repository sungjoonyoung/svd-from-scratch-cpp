#include<sungso376_LA.hpp>
#include<sungso376_debbuging.hpp>
#include<vector>
#include<iostream>
using namespace std;
int main(void){
    int N;cin>>N;
    vector<vector<double>> tmp=mat_identity(N);
    print_2D(tmp);
}