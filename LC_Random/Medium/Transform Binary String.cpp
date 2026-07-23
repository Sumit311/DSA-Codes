/*
===============================================================================
        3998. Transform Binary String Using Subsequence Sort
===============================================================================

Difficulty: Medium
Link: https://leetcode.com/problems/transform-binary-string-using-subsequence-sort/

-------------------------------------------------------------------------------
Problem
-------------------------------------------------------------------------------

You are given a binary string s and an array of strings strs.

Each string in strs consists of the characters:

    • '0'
    • '1'
    • '?'

Every '?' can be replaced with either '0' or '1'.

You may repeatedly perform the following operation:

    • Choose any subsequence of s.
    • Sort the chosen subsequence in non-decreasing order.

Determine for every string whether there exists a replacement of '?' such that
it can be obtained from s.

-------------------------------------------------------------------------------
Approach
-------------------------------------------------------------------------------

Observation 1

The number of zeros and ones never changes.

So if a target string requires more zeros or more ones than s,
it is impossible.

------------------------------------------------

Observation 2

To maximize the possibility of satisfying the transformation,
replace '?' greedily.

Suppose the target still needs X zeros.

Replace the first X '?' with '0'
and every remaining '?' with '1'.

This places zeros as early as possible, which is always optimal.

------------------------------------------------

Observation 3

While scanning from left to right maintain

balance =
(number of zeros seen in s)
-
(number of zeros seen in target)

Since subsequence sorting can only move zeros towards the left
(or equivalently move ones towards the right),

balance should never become negative.

If it does, the transformation is impossible.

-------------------------------------------------------------------------------
Algorithm
-------------------------------------------------------------------------------

1. Count zeros and ones in s.

2. For every query:

   • Count fixed zeros and ones.

   • If either exceeds those in s, return false.

   • Replace '?' greedily.

   • Scan from left to right while maintaining balance.

   • If balance becomes negative, return false.

   • Otherwise return true.

-------------------------------------------------------------------------------
Time Complexity
-------------------------------------------------------------------------------

Let

n = length of s
m = number of strings

Each query requires O(n).

Overall:

O(m × n)

-------------------------------------------------------------------------------
Space Complexity
-------------------------------------------------------------------------------

Extra Space:

O(1)

(The strings are modified in-place.)

===============================================================================
*/

class Solution
{
public:
    vector<bool> transformStr(string s, vector<string> &strs)
    {

        int zeroCount = count(s.begin(), s.end(), '0');
        int oneCount = s.size() - zeroCount;

        vector<bool> answer;

        for (auto &target : strs)
        {

            int targetZero = count(target.begin(), target.end(), '0');
            int targetOne = count(target.begin(), target.end(), '1');

            // Target needs more zeros or ones than available.
            if (targetZero > zeroCount || targetOne > oneCount)
            {
                answer.push_back(false);
                continue;
            }

            int needZero = zeroCount - targetZero;

            // Replace '?' greedily.
            for (int i = 0; i < target.size(); i++)
            {

                if (target[i] == '?' && needZero)
                {
                    target[i] = '0';
                    needZero--;
                }
                else if (target[i] == '?')
                {
                    target[i] = '1';
                }
            }

            int balance = 0;

            for (int i = 0; i < target.size(); i++)
            {

                balance += (s[i] - '0') - (target[i] - '0');

                if (balance < 0)
                    break;
            }

            answer.push_back(balance >= 0);
        }

        return answer;
    }
};