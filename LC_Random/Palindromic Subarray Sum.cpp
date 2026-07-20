/*
===============================================================================
                    3985. Palindromic Subarray Sum
===============================================================================

Difficulty: Hard
Link: https://leetcode.com/problems/palindromic-subarray-sum/

-------------------------------------------------------------------------------
Problem
-------------------------------------------------------------------------------

You are given an integer array nums.

Return the maximum possible sum of any contiguous subarray that forms a
palindrome.

A palindrome is an array that reads the same forwards and backwards.

Examples:

Input:
nums = [1,2,3,2,1,5,6]

Output:
9

Explanation:

The palindrome is

    [1,2,3,2,1]

whose sum is

1 + 2 + 3 + 2 + 1 = 9.

-------------------------------------------------------------------------------
Observation
-------------------------------------------------------------------------------

Brute force is impossible.

Checking every subarray requires

    O(n²)

subarrays.

Checking whether each is a palindrome takes

    O(n)

making the total complexity

    O(n³)

which is far too slow for

n = 100000.

We need an O(n) solution.

-------------------------------------------------------------------------------
Key Idea
-------------------------------------------------------------------------------

This problem has two independent parts:

1. Find every palindrome efficiently.
2. Compute its sum efficiently.

For (1), Manacher's Algorithm finds the longest palindrome centered at every
position in linear time.

For (2), Prefix Sum allows obtaining the sum of any subarray in O(1).

Combining both gives an overall O(n) solution.

-------------------------------------------------------------------------------
Step 1 : Prefix Sum
-------------------------------------------------------------------------------

Let

prefix[i]

denote the sum of the first i elements.

Then

sum(l...r)

can be obtained as

prefix[r + 1] - prefix[l]

in constant time.

-------------------------------------------------------------------------------
Step 2 : Transform the Array
-------------------------------------------------------------------------------

Manacher's algorithm works best when odd and even length palindromes are treated
uniformly.

We insert separators between every element.

Example

Original

    1 2 3 2 1

Transformed

    # 1 # 2 # 3 # 2 # 1 #

Instead of '#', this implementation uses LLONG_MIN because every array element
is positive.

Now every palindrome has a unique center.

-------------------------------------------------------------------------------
Step 3 : Manacher's Algorithm
-------------------------------------------------------------------------------

Maintain:

center
    Current palindrome center.

right
    Rightmost boundary reached so far.

radius[i]
    Radius of the palindrome centered at i.

If

i < right

its mirror position already provides useful information.

Otherwise expand normally.

Every character is expanded at most once, giving O(n) complexity.

-------------------------------------------------------------------------------
Step 4 : Convert Back to Original Array
-------------------------------------------------------------------------------

Suppose a palindrome in the transformed array has

center = i
radius = radius[i]

Its corresponding indices in the original array are

start = (i - radius[i]) / 2

endExclusive = (i + radius[i]) / 2

Its sum becomes

prefix[endExclusive] - prefix[start]

Update the maximum answer.

-------------------------------------------------------------------------------
Algorithm
-------------------------------------------------------------------------------

1. Compute prefix sums.

2. Transform the array by inserting separators.

3. Run Manacher's Algorithm.

4. For every palindrome:
      • Convert transformed indices back.
      • Compute its sum using prefix sums.
      • Update the maximum.

5. Return the maximum palindrome sum.

-------------------------------------------------------------------------------
Why This Works
-------------------------------------------------------------------------------

Manacher guarantees that every maximal palindrome is discovered exactly once.

For each palindrome, prefix sums compute its subarray sum in O(1).

Therefore every valid palindromic subarray is considered, and the maximum sum
is returned.

-------------------------------------------------------------------------------
Time Complexity
-------------------------------------------------------------------------------

Building prefix sums:
O(n)

Building transformed array:
O(n)

Manacher's Algorithm:
O(n)

Overall:

O(n)

-------------------------------------------------------------------------------
Space Complexity
-------------------------------------------------------------------------------

Prefix Sum:
O(n)

Transformed Array:
O(n)

Radius Array:
O(n)

Overall:

O(n)

===============================================================================
*/

class Solution
{
public:
    long long longestPalindromeSum(const vector<int> &nums,
                                   const vector<long long> &prefix)
    {

        const int n = nums.size();
        const long long SEP = LLONG_MIN;

        // Transform the array:
        // # a # b # c # ...
        vector<long long> transformed(2 * n + 1, SEP);

        for (int i = 0; i < n; i++)
            transformed[2 * i + 1] = nums[i];

        int m = transformed.size();

        vector<int> radius(m, 0);

        int center = 0;
        int right = 0;

        long long best = 0;

        for (int i = 0; i < m; i++)
        {

            // Use mirror information if inside current palindrome.
            if (i < right)
            {
                int mirror = 2 * center - i;
                radius[i] = min(radius[mirror], right - i);
            }

            // Expand around current center.
            while (i - radius[i] - 1 >= 0 &&
                   i + radius[i] + 1 < m &&
                   transformed[i - radius[i] - 1] ==
                       transformed[i + radius[i] + 1])
            {
                radius[i]++;
            }

            // Update the current rightmost palindrome.
            if (i + radius[i] > right)
            {
                center = i;
                right = i + radius[i];
            }

            // Convert transformed indices back to original array.
            int start = (i - radius[i]) / 2;
            int endExclusive = (i + radius[i]) / 2;

            // Compute palindrome sum in O(1).
            best = max(best, prefix[endExclusive] - prefix[start]);
        }

        return best;
    }

    long long getSum(vector<int> &nums)
    {

        int n = nums.size();

        vector<long long> prefix(n + 1, 0);

        for (int i = 0; i < n; i++)
            prefix[i + 1] = prefix[i] + nums[i];

        return longestPalindromeSum(nums, prefix);
    }
};