//Runtime: 968 ms, faster than 52.07% of C++ online submissions for The k Strongest Values in an Array.
//Memory Usage: 80.6 MB, less than 100.00% of C++ online submissions for The k Strongest Values in an Array.
class Solution {
public:
    vector<int> getStrongest(vector<int>& arr, int k) {
        int n = arr.size();
        sort(arr.begin(), arr.end());
        int median = arr[(n-1)/2];
        
        sort(arr.begin(), arr.end(),
            [&median](const int& x, const int& y){
                return (abs(x-median) == abs(y-median)) ? (x > y) : (abs(x-median) > abs(y-median));
            });
        
        return vector<int>(arr.begin(), arr.begin()+k);
    }
};

//two pointer
//https://leetcode.com/problems/the-k-strongest-values-in-an-array/discuss/674384/C%2B%2BJavaPython-Two-Pointers-%2B-3-Bonuses
//Runtime: 708 ms, faster than 74.91% of C++ online submissions for The k Strongest Values in an Array.
//Memory Usage: 80.5 MB, less than 100.00% of C++ online submissions for The k Strongest Values in an Array.
class Solution {
public:
    vector<int> getStrongest(vector<int>& arr, int k) {
        int n = arr.size();
        sort(arr.begin(), arr.end());
        int median = arr[(n-1)/2];
        int i = 0, j = n-1;
        
        //remove k weakest values
        while(k-- > 0){
            if(median - arr[i] > arr[j] - median){
                ++i;
            }else/* if(median - arr[i] <= arr[j] - median)*/{
                /*
                when median - arr[i] == arr[j] - median,
                we choose to move j forward,
                i.e. to maintain the original arr[j],
                because arr[j] is larger than arr[i],
                so arr[j] is also stronger than arr[i]
                */
                --j;
            }
        }
        
        //[i, j] are to be removed
        arr.erase(arr.begin()+i, arr.begin()+j+1);
        return arr;
    }
};
