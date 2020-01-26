#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void init_permutation(int *a, int n){
    for(int i=0; i<n; i++){
        a[i] = i+1;
    }
}


void print_permutation(int a[], int n){
    for(int i=0; i<n; i++){
        cout << a[i] << " ";
    }
    cout << endl;
}


int main(){

    int n, a;
    cin >> n >> a;

    int v[n];
    for(int i=0; i<n; i++){
        cin >> v[i];
    }

    for(int i=0; i<a; i++){
        if(!next_permutation(v, v+n)){
            break;
        }
    }

    print_permutation(v, n);

    return 0;
}
