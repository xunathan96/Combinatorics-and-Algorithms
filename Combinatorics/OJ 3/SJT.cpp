#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print_step(vector< vector<int> > v){
    for(int i=0; i<v.size(); i++){
        cout << v[i][0] << " | " << v[i][1] << endl;
    }
    cout << endl;
}

void init_sjt(vector< vector<int> > &v){
    for(int i=0; i<v.size(); i++){
        v[i][0] = i+1;
    }
}

void swap(vector< vector<int> > &v, int i, int j){
    int temp_value=0, temp_arrow=0;
    temp_value = v[i][0];
    temp_arrow = v[i][1];
    v[i][0] = v[j][0];
    v[i][1] = v[j][1];
    v[j][0] = temp_value;
    v[j][1] = temp_arrow;
}

void flip_directions(vector< vector<int> > &v, int m){
    for(int i=0; i<v.size(); i++){
        //FLIP DIRECTION
        if(v[i][0] > m){
            v[i][1] = !v[i][1];
        }
    }
}

int find_largest_mobile_int(vector< vector<int> > v){
    int max = 0;
    int max_i = 0;
    int temp = 0;
    int n = v.size();
    for(int i=0; i<n; i++){
        bool skip = false;

        //POINTS LEFT
        if(v[i][1] == 0 && i!=0){
            temp = v[i-1][0];
        }
        //POINTS RIGHT
        else if(v[i][1] == 1 && i!=n-1){
            temp = v[i+1][0];
        }
        //INTEGER IS AT ENDPOINT
        else{
            skip = true;
        }

        //MOBILE INTEGER
        if(!skip && temp < v[i][0]){
            //LARGEST MOBILE INT
            if(v[i][0] > max){
                max = v[i][0];
                max_i = i;
            }
        }
    }

    //cout << "largest mobile int: " << max << endl;
    //cout << "Index: " << max_i << endl;

    return max_i;
}

int main(){
    int n, k;
    cin >> n >> k;
    vector< vector<int> > p(n, vector<int>(2, 0));
    init_sjt(p);

    int max_mobile_index = 0;
    int max_mobile_value = 0;
    for(int i=2; i<=k; i++){

        //print_step(p);

        //FIND LARGEST MOBILE INTEGER
        max_mobile_index = find_largest_mobile_int(p);
        max_mobile_value = p[max_mobile_index][0];

        //SWAP ADJACENT INTEGER
        if(p[max_mobile_index][1] == 0){
            swap(p, max_mobile_index, max_mobile_index-1);
        }
        else{
            swap(p, max_mobile_index, max_mobile_index+1);
        }

        if(max_mobile_value!=n){
            flip_directions(p, max_mobile_value);
        }
    }

    //print_step(p);
    for(int i=0; i<p.size(); i++){
        cout << p[i][0] << " ";
    }

    return 0;
}
