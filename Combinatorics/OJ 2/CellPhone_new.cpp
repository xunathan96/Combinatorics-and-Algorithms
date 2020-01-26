#include <iostream>
#include <vector>
using namespace std;

void print_permutations(vector< vector<int> > v) {
    for(int i=0; i<v.size(); i++){
        for(int j=0; j<v[i].size(); j++){
            cout << v[i].at(j) << " ";
        }
        cout << endl;
    }
    cout << "# of Permutations: " << v.size() << endl;
}

int swap(vector<int> &v, int j, int k){
    int temp = v[j];
    v[j] = v[k];
    v[k] = temp;
    return 1;
}

vector< vector<int> > permutations;

int generate_permutations(vector<int> set, int fixed){

    if(fixed==set.size()-1){
        permutations.push_back(set);
        return 0;
    }

    for(int i=fixed; i<set.size(); i++){
        swap(set, fixed, i);
        generate_permutations(set, fixed+1);
        swap(set, i, fixed);
    }

    return 0;
}

int main(){
    int a, b, l;
    //cin >> a >> b >> l;
    //cout << a + b + l << endl;

    vector<int> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    generate_permutations(v, 0);

    print_permutations(permutations);


    return 0;
}
