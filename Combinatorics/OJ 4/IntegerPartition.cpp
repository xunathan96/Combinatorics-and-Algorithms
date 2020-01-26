#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define M 1000000007

vector< vector<int> > partition_table(2001, vector<int>(2001, -1));

int integer_partition(int n, int k){
    //EDGE CASES
    if(n<=0 || k<=0){
        return 0;
    }
    else if(k==1 || n==k){
        return 1;
    }
    else if(n<k){
        return 0;
    }

    //BASE CASE
    if(partition_table[n][k]!=-1){
        return partition_table[n][k];
    }
    //RECURSIVE CASE
    else{
        partition_table[n][k] = (integer_partition(n-1, k-1) + integer_partition(n-k, k)) % M;
        return partition_table[n][k];
    }
}


int no_more_than_k_partitions(int n, int k){
    int num_partitions=0;
    for(int i=1; i<=k; i++){
        num_partitions = (num_partitions + integer_partition(n, i)) % M;
    }
    return num_partitions;
}


int main(){

    int n, k;
    cin >> n >> k;
    cout << no_more_than_k_partitions(n, k) << endl;

    return 0;
}
