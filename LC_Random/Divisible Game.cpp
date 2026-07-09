/*
                                            3984. Divisible Game

You are given an integer array nums of length n.

Alice and Bob are playing a game. Alice chooses:

An integer k such that k > 1.
Two integers l and r such that 0 <= l <= r < n.
Initially, both Alice's and Bob's scores are 0.

For each index i in the range [l, r] (inclusive):

If nums[i] is divisible by k, Alice's score increases by nums[i].
Otherwise, Bob's score increases by nums[i].
The score difference is Alice's score minus Bob's score.

Alice wants to maximize the score difference. If there are multiple values of k that achieve the maximum score difference, she chooses the smallest such k.

Return the product of the maximum score difference and the chosen value of k. Since the result can be large, return it modulo 109 + 7.

Example 1:

Input: nums = [1,4,6,8]

Output: 36

Explanation:

Alice can choose k = 2, l = 1, and r = 3.
All values in nums[1..3] are divisible by 2, so Alice's score is 4 + 6 + 8 = 18, while Bob's score is 0.
The score difference is 18, which is the maximum possible. Among all values of k that achieve this score difference, the smallest is 2.
Therefore, the answer is 18 * 2 = 36.
Example 2:

Input: nums = [2,1,2]

Output: 6

Explanation:

Alice can choose k = 2, l = 0, and r = 2.
The values nums[0] and nums[2] are divisible by 2, so Alice's score is 2 + 2 = 4. The value nums[1] is not divisible by 2, so Bob's score is 1.
The score difference is 4 - 1 = 3, which is the maximum possible. Among all values of k that achieve this score difference, the smallest is 2.
Therefore, the answer is 3 * 2 = 6.
Example 3:

Input: nums = [1]

Output: 1000000005

Explanation:

Alice must choose some k > 1. The smallest possible choice is k = 2.
Since nums[0] is not divisible by 2, Alice's score is 0, while Bob's score is 1.
The score difference is -1, which is the maximum possible.
Therefore, the answer is -1 * 2 = -2. Modulo 109 + 7, this equals 1000000005.


Constraints:

1 <= nums.length <= 1000
1 <= nums[i] <= 106

*/

/********************* CODE ***************************/
/*
- MAke a list of valid divisors :
    Case 1 : A number have factor a then store (A/a and a)
    Case 2 : If number is prime store it
    Case 3 : Don't store 1 (since samllest k can be 2 but 1 is not divisible by 2)

- Run a loop on Factors (k)
- Run a loop on nums
- Apply Kadane's Algo to find max subarray sum
- After finding the max sum keep storing best k (if tempSum > bestSum replace bestK with current k)

- At the end multiple max sum to k and mod

*/
class Solution
{
public:
    int divisibleGame(vector<int> &nums)
    {

        int n = nums.size(), mod = 1e9 + 7;
        long long mx = 0;
        set<int> st;

        for (auto &it : nums)
        {
            if (it > 1)
                st.insert(it);

            for (int i = 2; i * i <= it; i++)
            {
                if (it % i == 0)
                {
                    st.insert(i);
                    st.insert(it / i);
                }
            }
        }

        if (st.size() == 0)
            return (-2 + mod) % mod;
        int bestK = 1;

        for (auto &k : st)
        {
            long long sum = 0, tmx = 0;

            for (auto &it : nums)
            {
                long long val = it % k ? -1ll * it : it;
                sum = max(0ll, (sum + val));
                tmx = max(tmx, sum);
            }

            if (tmx > mx)
            {
                mx = tmx;
                bestK = k;
            }
        }

        return (mx % mod) * bestK % mod;
    }
};