/*
                        Subsequence After One Replacement

You are given two strings s and t consisting of lowercase English letters.

You may choose at most one index in s and replace the character at that index with any lowercase English letter.

Return true if it is possible to make s a subsequence of t; otherwise, return false.


Example 1:

Input: s = "cat", t = "chat"

Output: true

Explanation:

Replace s[1] from 'a' to 'h'. The resulting string is "cht".
"cht" is a subsequence of "chat" because we can match 'c', 'h', and 't' in order.
Example 2:

Input: s = "plane", t = "apple"

Output: false

Explanation:

The characters 'p', 'l', and 'e' can be matched in t, but the remaining characters cannot be matched while preserving the required order.
Even after replacing any one character in s, it is impossible to make s a subsequence of t.


Constraints:

1 <= s.length, t.length <= 105
s and t consist only of lowercase English letters.


*/

/**************** CODE ******************/
/*
 pre matach till (i- 1) - ith index to replace - suff match from (i + 1) till n
    suff[i + 1] - pre[ i - 1] > 1 (at least one index in between to replace)
 edge cases:
    i == 0
    pre[i - 1] = -1
    i == n - 2
*/
class Solution
{
public:
    bool canMakeSubsequence(string s, string t)
    {
        int n = s.size(), m = t.size();

        if (n > m)
            return false;

        vector<int> pre(n, -1), suff(n, -1);

        int j = 0;

        for (int i = 0; i < n; i++)
        {

            while (j < m && s[i] != t[j])
                ++j;
            if (j == m)
                break;
            pre[i] = j++;
        }

        if (pre[n - 1] != -1)
            return true;
        j = m - 1;

        for (int i = n - 1; i >= 0; i--)
        {

            while (j >= 0 && s[i] != t[j])
                --j;

            if (j < 0)
                break;
            suff[i] = j--;
        }

        for (int i = 0; i < n; i++)
        {
            if (i != 0 && pre[i - 1] == -1 || i != n - 1 && suff[i + 1] == -1)
                continue;

            int l = i == 0 ? -1 : pre[i - 1] == -1 ? m
                                                   : pre[i - 1];
            int r = (i == n - 1) ? m : suff[i + 1];

            if (r - l > 1)
                return true;
        }

        return false;
    }
};

/******************** BEST SOLUTION ***********************/
class Solution
{
public:
    bool canMakeSubsequence(string s, string t)
    {

        int n = s.size();

        // Longest prefix matched without replacement.
        int normalMatch = 0;

        // Longest prefix matched using at most one replacement.
        int oneReplacementMatch = 0;

        for (char currentChar : t)
        {

            // Option 1:
            // Continue a path where replacement
            // was already used.
            if (oneReplacementMatch < n &&
                currentChar == s[oneReplacementMatch])
            {

                oneReplacementMatch++;
            }

            // Option 2:
            // Start using the replacement
            // at the current position.
            oneReplacementMatch =
                max(oneReplacementMatch,
                    min(normalMatch + 1, n));

            // Normal subsequence matching.
            if (normalMatch < n &&
                currentChar == s[normalMatch])
            {

                normalMatch++;
            }
        }

        return oneReplacementMatch == n;
    }
};