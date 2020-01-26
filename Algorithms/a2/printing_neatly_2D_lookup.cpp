#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

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

int neat_partition(int i, int j, vector<vector<int> > &S, /*vector<vector<int> > &P,*/ vector<int> word_len, int n, int M){
    if(S[i][j] >= 0){
        return S[i][j];
    }

    int extra_spaces = V(i, j, M, word_len);

    if(extra_spaces>=0 && j==n-1){
        S[i][j] = 0;
        return 0;
    }
    else if(extra_spaces>=0){
        S[i][j] = extra_spaces;
        return extra_spaces;
    }
    else{
        int res=0;
        vector<int> cache;
        for(int k=i; k<j; k++){
            res = neat_partition(i, k, S, /*P,*/ word_len, n, M) + neat_partition(k+1, j, S, /*P,*/ word_len, n, M);
            cache.push_back(res);
        }
        vector<int>::iterator min_iter = min_element(cache.begin(), cache.end());

        int min_index = min_iter - cache.begin() + i;
        int min_value = *min_iter;

        S[i][j] = min_value;
        return min_value;
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

    vector< vector<int> > S(n, vector<int>(n, -1));
    //vector< vector<int> > P(n, vector<int>(n, -1));

    cout << neat_partition(0, n-1, S, /*P,*/ word_len, n, M);

    return 0;
}
