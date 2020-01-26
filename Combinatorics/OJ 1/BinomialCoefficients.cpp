#include <iostream>
#include <vector>
using namespace std;

#define M 1000000007

vector< vector<int> > pascal_triangle(2001, vector<int>(2001, -1));

int calculate_binomial_coefficient(int n, int r){
    //EDGE CASES
    if(n==r || r==0){
        pascal_triangle[n][r] = 1;
        return 1;
    }
    if(n<r){
        return 0;
    }

    //BASE CASE
    if(pascal_triangle[n][r] != -1){
        return pascal_triangle[n][r];
    }
    //RECURSIVE CASE
    else{
        pascal_triangle[n][r] = (calculate_binomial_coefficient(n-1, r) + calculate_binomial_coefficient(n-1, r-1)) % M;
        return pascal_triangle[n][r];
    }
}


int main(){
    int n, r;
    cin >> n >> r;
    cout << calculate_binomial_coefficient(n, r) << endl;
    return 0;
}
