#include <iostream>
#include <vector>

using namespace std;

/*
int countMergeSort(vector<long long>& prefix, int start, int end, int lower, int upper)
{
    if(start >= end) return 0;
    int mid = (start + end) >> 1;
    int count = countMergeSort(prefix, start, mid, lower, upper) + countMergeSort(prefix, mid+1, end, lower, upper);
    vector<long long> tmp(end-start+1);
    int lowerBound = mid+1, upperBound = mid+1, right = mid+1, tmpindex = 0;
    for(int left = start; left<=mid; left++)
    {
        while(lowerBound<=end && prefix[lowerBound] - prefix[left] < lower)
            lowerBound++;
        while(upperBound<=end && prefix[upperBound] - prefix[left] <= upper)
            upperBound++;
        count += upperBound - lowerBound;
        while(right<=end && prefix[right] < prefix[left])
            tmp[tmpindex++] = prefix[right++];
        tmp[tmpindex++] = prefix[left];
    }
    for(int i = 0; i<tmpindex; i++)
        prefix[start+i] = tmp[i];
    return count;
}

int countRangeSum(vector<int>& nums, int lower, int upper)
{
    //get the prefix sum
    vector<long long> prefix(nums.size() + 1, 0);
    for(int i = 1; i<=nums.size(); i++)
        prefix[i] = prefix[i-1] + nums[i-1];
    return countMergeSort(prefix, 0, nums.size(), lower, upper);
}
*/

/*
int countAndMergeSort(vector<long long> *sums, int start, int end, int lower, int upper) {

    if (end - start <= 1) {  // The number of range [start, end) of which size is less than 2 is always 0.
        return 0;
    }
    int mid = start + (end - start) / 2;
    int count = countAndMergeSort(sums, start, mid, lower, upper) + countAndMergeSort(sums, mid, end, lower, upper);
    int j = mid, k = mid, r = mid;
    vector<long long> tmp;
    for (int i = start; i < mid; ++i) {
        // Count the number of range sums that lie in [lower, upper].
        while (k < end && (*sums)[k] - (*sums)[i] < lower) {
            ++k;
        }
        while (j < end && (*sums)[j] - (*sums)[i] <= upper) {
            ++j;
        }
        count += j - k;

        // Merge the two sorted arrays into tmp.
        while (r < end && (*sums)[r] < (*sums)[i]) {
            tmp.push_back((*sums)[r++]);
        }
        tmp.push_back((*sums)[i]);
    }
    // Copy tmp back to sums.
    copy(tmp.begin(), tmp.end(), sums->begin() + start);
    return count;
}

int countRangeSum(vector<int>& nums, int lower, int upper) {
    vector<long long> sums(nums.size() + 1);
    for (int i = 0; i < nums.size(); ++i) {
        sums[i + 1] = sums[i] + nums[i];
    }
    return countAndMergeSort(&sums, 0, sums.size(), lower, upper);
}
*/



/*
int countMergeSort(vector<long long>& prefix, int start, int end, int lower, int upper)
{
    if(start >= end) return 0;
    int mid = (start + end) >> 1;
    int count = countMergeSort(prefix, start, mid, lower, upper) + countMergeSort(prefix, mid+1, end, lower, upper);
    vector<long long> tmp(end-start+1);
    int lowerBound = mid+1, upperBound = mid+1, right = mid+1, tmpindex = 0;
    for(int left = start; left<=mid; left++)
    {
        while(lowerBound<=end && prefix[lowerBound] - prefix[left] < lower)
            lowerBound++;
        while(upperBound<=end && prefix[upperBound] - prefix[left] <= upper)
            upperBound++;
        count += upperBound - lowerBound;
        while(right<=end && prefix[right] < prefix[left])
            tmp[tmpindex++] = prefix[right++];
        tmp[tmpindex++] = prefix[left];
    }
    for(int i = 0; i<tmpindex; i++)
        prefix[start+i] = tmp[i];
    return count;
}

int countRangeSum(vector<int>& nums, int lower, int upper)
{
    //get the prefix sum
    vector<long long> prefix(nums.size() + 1, 0);
    for(int i = 1; i<=nums.size(); i++)
        prefix[i] = prefix[i-1] + nums[i-1];
    return countMergeSort(prefix, 0, nums.size(), lower, upper);
}
*/

int mergeSort(vector<int64_t>& sum, int i, int j, int u, int l) {
    if(i == j) return l <= sum[i] && sum[i] <= u;
    int mid = i + (j-i)/2, count = mergeSort(sum, i, mid, u, l) + mergeSort(sum, mid+1, j, u, l);

    for(int l_ = i, r_ = i, k = mid+1; k <= j; ++k) { // Find all i, j pairs
        while(r_ <= mid && sum[r_] + l <= sum[k]) ++r_;
        while(l_ <= mid && sum[k] > sum[l_] + u) ++l_;
        count += r_ - l_;
    }

    vector<int64_t> tmp(j-i+1, 0);
    for(int k = i, l = mid+1, m = 0; m <= j-i; ++m) { // merge
        if(k > mid) tmp[m] = sum[l++];
        else if(l > j) tmp[m] = sum[k++];
        else tmp[m] = sum[l] < sum[k] ? sum[l++] : sum[k++];
    }
    copy(tmp.begin(), tmp.end(), sum.begin()+i);
    return count;
}

int countRangeSum(vector<int>& nums, int lower, int upper) {
    const int size = nums.size();
    if(!size) return 0;
    vector<int64_t> sum(size, nums[0]);
    for(int i = 1; i < size; ++i) sum[i] = sum[i-1] + nums[i];
    return mergeSort(sum, 0, size-1, upper, lower);
}

int main(){
    int n, lower, upper;
    cin >> n >> lower >> upper;

    vector<int> nums(n);
    for(int i=0; i<n; i++){
        cin >> nums[i];
    }

    //vector<int> prefix = get_prefix_sums(nums, n);

    //print_vector(prefix, n+1);

    cout << countRangeSum(nums, lower, upper) << endl;



    return 0;
}
