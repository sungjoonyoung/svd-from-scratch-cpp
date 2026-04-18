#include<sungso376_LA.hpp>
#include<sungso376_debbuging.hpp>
#include<vector>
#include<iostream>
using namespace std;
// typedef struct{
//     vector<vector<double>>Q;
//     vector<vector<double>>R;
// } QR;
int main(void){
    int N,M;cin>>N>>M;
    vector<vector<double>>v;v.resize(N);
    for(int i=0;i<N;i++)for(int j=0;j<M;j++){
        double in;cin>>in;
        v[i].push_back(in);
    }
    cout<<"A==\n";
    print_2D(v);
    auto tmp=QRD_GS(v);
    cout<<"Q==\n";
    print_2D(tmp.Q);
    cout<<"R==\n";
    print_2D(tmp.R);
    cout<<"QR==\n";
    auto QmR=mat_mul(tmp.Q,tmp.R);
    print_2D(QmR);
}

/*
3 3
1 2 3
6 5 1
4 6 2


3 3
1 0 0
1 1 0
1 1 1
*/