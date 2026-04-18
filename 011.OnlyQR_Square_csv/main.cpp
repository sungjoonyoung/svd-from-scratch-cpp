 #include<iostream>
 #include<fstream>
 #include<sungso376_STR.hpp>
 #include<sungso376_LA.hpp>
 #include<sungso376_debbuging.hpp>
 using namespace std;
 typedef struct{
    vector<vector<double>> A;
    QR;
 }element;
 vector<element>v;
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
    v.push_back(element());
    //
    
 }