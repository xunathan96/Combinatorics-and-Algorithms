#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

#define MAX_VALUE numeric_limits<int>::max();

int V(int i, int j, int M, vector<int> word_len){
    int res = 0;
    for(int k=i; k<=j; k++){
        res += word_len[k];
    }
    res += j - i;
    res = M - res;
    res = res * res * res;
    return res;
}

int neat_partition(int i, int n, int M, vector<int> &S, vector<int> word_len){
    if(S[i] >= 0){
        return S[i];
    }

    int extra_spaces = V(i, n, M, word_len);

    if(extra_spaces>=0){
        S[i] = 0;
        return 0;
    }
    else{
        int optimal_subsolution = MAX_VALUE;
        int subsolution = MAX_VALUE;
        int partition_extra_spaces = 0;

        for(int k=i+1; k<=n; k++){
            partition_extra_spaces = V(i, k-1, M, word_len);
            if(partition_extra_spaces < 0) break;

            subsolution = partition_extra_spaces + neat_partition(k, n, M, S, word_len);

            if(subsolution < optimal_subsolution){
                optimal_subsolution = subsolution;
            }
        }

        S[i] = optimal_subsolution;
        return optimal_subsolution;
    }
}


int main(){
    int n, M;
    cin >> n >> M;

    string word;
    vector<int> word_len(n);
    for(int i=0; i<n; i++){
        cin >> word;
        word_len[i] = word.length();
    }

    vector<int> S(n, -1);
    cout << neat_partition(0, n-1, M, S, word_len);

    return 0;
}
