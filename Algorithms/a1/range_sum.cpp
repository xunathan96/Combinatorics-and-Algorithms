#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print_vector(vector<long long> v, int n){
    for(int i=0; i<n; i++){
        cout << v[i] << " ";
    }
    cout << endl;
}

vector<long long> get_prefix_sums(vector<long long> nums, int n){
    vector<long long> prefix(n+1);
    prefix[0] = 0;
    for(int i=1; i<=n; i++){
        prefix[i] = prefix[i-1] + nums[i-1];
    }
    return prefix;
}

int S(vector<long long> prefix, int i, int j){
    return prefix[j] - prefix[i-1];
}

// Count while Merge Sorting
int num_cross_range_sums(vector<long long>& prefix, int start, int end, int mid, long lower, long upper){

    int cross_count = 0;
    int lowerbound = mid;
    int upperbound = mid;
    int j=mid, cache_index=0;
    vector<long long> cache(end-start+1);

    for(int i=start; i<mid; i++){
        // COUNT STEP -- left and right subarrays are sorted due to merge sort
        while(lowerbound<=end && prefix[lowerbound]-prefix[i]<lower){
            lowerbound++;
        }
        while(upperbound<=end && prefix[upperbound]-prefix[i]<=upper){
            upperbound++;
        }
        cross_count += upperbound - lowerbound;

        // MERGE STEP -- store sorted array in cache (j is index of right half)
        while(j<=end && prefix[j]<prefix[i]){
            cache[cache_index++] = prefix[j++];
        }
        cache[cache_index++] = prefix[i];
    }

    // MERGE STEP -- update prefix with sorted cache
    for(int i=0; i<cache_index; i++){
        prefix[start+i] = cache[i];
    }

    return cross_count;
}

// should initialize to start=1 and end=n
int num_range_sums(vector<long long>& prefix, int start, int end, long lower, long upper){

    long long range_sum = 0;
    int count = 0;
    int mid = (start+end+1)/2;

    // BASE CASE -- only one element between start and end
    if(start==end){
        range_sum = prefix[start];
        if(range_sum >= lower && range_sum <= upper){
            return 1;
        }
    }
    // RECURSIVE CASE -- add # ranges in left and right halves and # ranges across middle
    else{
        count += num_range_sums(prefix, start, mid-1, lower, upper);
        count += num_range_sums(prefix, mid, end, lower, upper);
        count += num_cross_range_sums(prefix, start, end, mid, lower, upper);
        return count;
    }
    return 0;
}


int main(){
    int n;
    long lower, upper;
    cin >> n >> lower >> upper;

    vector<long long> nums(n);
    for(int i=0; i<n; i++){
        cin >> nums[i];
    }

    vector<long long> prefix = get_prefix_sums(nums, n);
    cout << num_range_sums(prefix, 1, n, lower, upper) << endl;

    return 0;
}
