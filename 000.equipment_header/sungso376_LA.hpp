#pragma once
#include<vector>
#include<iostream>
#include<sungso376_debbuging.hpp>
using namespace std;

// 1D vector의 내적
auto inner_product(const vector<double>&a,const vector<double>&b){
    if(a.size()!=b.size()){
        cout<<"inner product의 사이즈가 다름\n\n";
        return 0.0;
    }
    double answer=0;
    for(int i=0;i<a.size();i++)answer+=a[i]*b[i];
    return answer;
}

// 2D mat의 곱
auto mat_mul(const vector<vector<double>>&a,const vector<vector<double>>&b){
    if(a[0].size()!=b.size()){
        cout<<"mat mul의 사이즈가 다름\n\n";
        return vector<vector<double>>();
    }
    vector<vector<double>> answer;
    answer.resize(a.size());
    for(int i=0;i<answer.size();i++){
        answer[i].resize(b[0].size());
        for(int j=0;j<answer[i].size();j++){
            answer[i][j]=0;
            for(int k=0;k<a[0].size();k++){
                answer[i][j]+=a[i][k]*b[k][j];
            }
        }
    }
    return answer;
}

// 2D mat의 합
auto mat_plus(const vector<vector<double>>&a,const vector<vector<double>>&b){
    if(a.size()!=b.size() or a[0].size()!=b[0].size() ){
        cout<<"mat_plus의 사이즈가 다름\n\n";
        return vector<vector<double>>();
    }
    vector<vector<double>> answer;
    answer.resize(a.size());
    for(int i=0;i<answer.size();i++){
        answer[i].resize(b[0].size());
        for(int j=0;j<answer[i].size();j++){
            answer[i][j]=a[i][j]+b[i][j];
        }
    }
    return answer;
}

// 아이덴디티 메트릭스를 후딱 만듦
auto mat_identity(int N){
    vector<vector<double>> answer;
    answer.resize(N);
    for(int i=0;i<N;i++){
        answer[i].resize(N);
        answer[i][i]=1;
    }
    return answer;
}

// 영 메트릭스를 후딱 만듦
auto mat_zero(int N){
    vector<vector<double>> answer;
    answer.resize(N);
    for(int i=0;i<N;i++)answer[i].resize(N);
    return answer;
}

// 1D column vector를 v^t*v 를 통해 2D mat 만듦
auto vec_to_mat(const vector<double> &v){
    vector<vector<double>> answer;
    answer.resize(v.size());
    for(int i=0;i<v.size();i++){
        answer[i].resize(v.size());
        for(int j=0;j<v.size();j++){
            answer[i][j]=v[i]*v[j];
        }
    }
    return answer;
}

// 루트함수 by 뉴턴메서드
auto sqrt(double x, double error=1e-16, int max_iter=100000){
    if(x<0){
        cout<<"sqrt에 음수 들어옴\n\n";
        return 0.0;
    }
    if(x==0){
        return 0.0;
    }
    double answer=x;
    double before=0;
    while(abs(before-answer)>error and max_iter--){
        if(answer==0)answer+=error;
        before=answer;
        answer=answer-(answer*answer-x)/(2*answer);
    }
    return answer;
}

// 2d matrix T
auto mat_transpose(const vector<vector<double>> &A){
    vector<vector<double>>answer;
    answer.resize(A[0].size());
    for(int i=0;i<A[0].size();i++){
        answer[i].resize(A.size());
        for(int j=0;j<A.size();j++){
            answer[i][j]=A[j][i];
        }
    }
    return answer;
}

// 1D vector A-B
auto vec_AminusB(const vector<double>&A,const vector<double>&B){
    if(A.size()!=B.size()){
        cout<<"vec_AminusB에서 사이즈 안 맞음\n\n";
        return vector<double>();
    }
    vector<double> answer;answer.resize(A.size());
    for(int i=0;i<answer.size();i++)answer[i]=A[i]-B[i];
    return answer;
}

typedef struct QR{
    vector<vector<double>>Q;
    vector<vector<double>>R;
} QR;
// qr분해, 그람슈미쯔
auto QRD_GS(const vector<vector<double>> &A){
    if(A.size()!=A[0].size()){
        cout<<"QRD_GS에서 A가 정방행렬이 아님\n";
        return QR();
    }
    QR answer;
    auto AT=mat_transpose(A);
    vector<vector<double>> QT,R;
    // 그람슈미쯔
    for(int i=0;i<AT.size();i++){
        QT.push_back(AT[i]);
        for(int j=0;j<i;j++){
            vector<double>pol=QT[j]; // vj
            double son=inner_product(QT[i],pol); // <ui,vj>
            double mom=inner_product(pol,pol);   // <vj,bj>
            for(int k=0;k<pol.size();k++){
                pol[k]*=son;
                pol[k]/=mom;
            }
            QT[i]=vec_AminusB(QT[i],pol);
        }
        // q 칼럼 유닛화
        double norm=sqrt(inner_product(QT[i],QT[i]));
        for(int j=0;j<QT[i].size();j++)QT[i][j]/=norm;
    }
    answer.Q=mat_transpose(QT);
    // R 구하기
    for(int i=0;i<A.size();i++){
        R.push_back(vector<double>());R[i].resize(A.size());
        for(int j=i;j<A.size();j++){
            R[i][j]=inner_product(AT[j],QT[i]);
        }
    }
    answer.R=R;
    return answer;
}