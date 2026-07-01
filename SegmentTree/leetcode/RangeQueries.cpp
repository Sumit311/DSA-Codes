/*

2080. Range Frequency Queries

Design a data structure to find the frequency of a given value in a given subarray.

The frequency of a value in a subarray is the number of occurrences of that value in the subarray.

Implement the RangeFreqQuery class:

RangeFreqQuery(int[] arr) Constructs an instance of the class with the given 0-indexed integer array arr.
int query(int left, int right, int value) Returns the frequency of value in the subarray arr[left...right].
A subarray is a contiguous sequence of elements within an array. arr[left...right] denotes the subarray that contains the elements of nums between indices left and right (inclusive).



Example 1:

Input
["RangeFreqQuery", "query", "query"]
[[[12, 33, 4, 56, 22, 2, 34, 33, 22, 12, 34, 56]], [1, 2, 4], [0, 11, 33]]
Output
[null, 1, 2]

Explanation
RangeFreqQuery rangeFreqQuery = new RangeFreqQuery([12, 33, 4, 56, 22, 2, 34, 33, 22, 12, 34, 56]);
rangeFreqQuery.query(1, 2, 4); // return 1. The value 4 occurs 1 time in the subarray [33, 4]
rangeFreqQuery.query(0, 11, 33); // return 2. The value 33 occurs 2 times in the whole array.


Constraints:

1 <= arr.length <= 105
1 <= arr[i], value <= 104
0 <= left <= right < arr.length
At most 105 calls will be made to query

*/

// My CODE:
// FIrst I used vector of vector but it will give MLE error as worst C is 4 x 10^5 x 10^4 x 4 bytes = 16 GB.
// TO optimise the

class SGTree
{
public:
    vector<unordered_map<int, int>> seg;

public:
    SGTree(int n)
    {
        seg.resize(4 * n + 1);
    }
    SGTree() {}

    void build(int ind, int low, int high, vector<int> &arr)
    {
        if (low == high)
        {
            seg[ind][arr[low]]++;
            return;
        }

        int mid = (low + high) / 2;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);

        // for(auto& it : seg)
        for (auto &it : seg[2 * ind + 1])
            seg[ind][it.first] += it.second;
        for (auto &it : seg[2 * ind + 2])
            seg[ind][it.first] += it.second;
    }

    // query function
    int query(int ind, int low, int high, int l, int r, int val)
    {
        // no overlap
        // l r low high or low high l r
        if (r < low || high < l)
            return 0;

        // complete overlap
        // [l low high r]
        if (low >= l && high <= r)
            return seg[ind][val];

        int mid = (low + high) >> 1;
        int left = query(2 * ind + 1, low, mid, l, r, val);
        int right = query(2 * ind + 2, mid + 1, high, l, r, val);
        return left + right;
    }
};

class RangeFreqQuery
{
public:
    SGTree sg;
    int n;
    RangeFreqQuery(vector<int> &arr)
    {
        n = arr.size();
        sg = SGTree(n);
        sg.build(0, 0, n - 1, arr);
    }

    int query(int left, int right, int value)
    {
        return sg.query(0, 0, n - 1, left, right, value);
    }
};

/************************* BEST SOLUTION ****************************/

class RangeFreqQuery
{
    unordered_map<int, vector<int>> mp;

public:
    RangeFreqQuery(vector<int> &arr)
    {
        for (int i = 0; i < size(arr); i++)
            mp[arr[i]].push_back(i);
    }

    int query(int L, int R, int V)
    {
        return upper_bound(begin(mp[V]), end(mp[V]), R) - lower_bound(begin(mp[V]), end(mp[V]), L);
    }
};