#include <iostream>
#include <vector>
#include <algorithm>
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

int generate_permutations_recursive(vector<int> set, int fixed, int r, vector< vector<int> > &permutations){
    //BASE CASE
    if(fixed==r){
        permutations.push_back(vector<int>(set.begin(), set.begin()+r));
        return 0;
    }
    //RECURSIVE CASE
    for(int i=fixed; i<set.size(); i++){
        swap(set, fixed, i);
        generate_permutations_recursive(set, fixed+1, r, permutations);
        swap(set, i, fixed);
    }
    return 0;
}


vector< vector<int> > generate_permutations(vector<int> set, int r){
    vector< vector<int> > permutations;
    generate_permutations_recursive(set, 0, r, permutations);
    return permutations;
}


bool is_permutation_valid(vector<int> v, int a, int b){
    bool pass_2=false, pass_4=false, pass_5=false, pass_6=false, pass_8=false;
    v.insert(v.begin(), a);
    v.push_back(b);

    for(vector<int>::iterator iter=v.begin(); iter!=v.end()-1; iter++){
        switch(*iter) {
            case 2:
                pass_2 = true;
                break;
            case 4:
                pass_4 = true;
                break;
            case 5:
                pass_5 = true;
                break;
            case 6:
                pass_6 = true;
                break;
            case 8:
                pass_8 = true;
                break;
        }

        if( (*iter==1 && *(iter+1)==3) || (*iter==3 && *(iter+1)==1) ){
            if(!pass_2){return false;}
        }
        if( (*iter==1 && *(iter+1)==9) || (*iter==9 && *(iter+1)==1) ){
            if(!pass_5){return false;}
        }
        if( (*iter==1 && *(iter+1)==7) || (*iter==7 && *(iter+1)==1) ){
            if(!pass_4){return false;}
        }
        if( (*iter==3 && *(iter+1)==7) || (*iter==7 && *(iter+1)==3) ){
            if(!pass_5){return false;}
        }
        if( (*iter==3 && *(iter+1)==9) || (*iter==9 && *(iter+1)==3) ){
            if(!pass_6){return false;}
        }
        if( (*iter==7 && *(iter+1)==9) || (*iter==9 && *(iter+1)==7) ){
            if(!pass_8){return false;}
        }
        if( (*iter==4 && *(iter+1)==6) || (*iter==6 && *(iter+1)==4) ){
            if(!pass_5){return false;}
        }
        if( (*iter==2 && *(iter+1)==8) || (*iter==8 && *(iter+1)==2) ){
            if(!pass_5){return false;}
        }
    }
    return true;
}



int main(){
    int a, b, l;
    cin >> a >> b >> l;
    l = l-2;

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int len = sizeof(arr)/sizeof(arr[0]);
    vector<int> v(arr, arr + len);

    v.erase(remove(v.begin(), v.end(), a), v.end());
    v.erase(remove(v.begin(), v.end(), b), v.end());

    //GENERATE ALL PASSCODE PERMUTATIONS
    vector< vector<int> > permutations;
    permutations = generate_permutations(v, l);

    //COUNT THE NUMBER OF VALID PASSCODES
    bool is_valid;
    int num_passcodes = 0;
    for(int i=0; i<permutations.size(); i++){
        is_valid = is_permutation_valid(permutations[i], a, b);
        if(is_valid){
            num_passcodes++;
        }
    }

    cout << num_passcodes << endl;

    return 0;
}
