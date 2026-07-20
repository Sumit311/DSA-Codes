/*
===============================================================================
                         MANACHER'S ALGORITHM
                Longest Palindromic Substring in O(n)
===============================================================================

PROBLEM
-------
Given a string, find its longest palindromic substring.

Example:
    Input : "babad"
    Output: "bab" or "aba"

Brute Force:
    Check every substring and verify whether it is a palindrome.

    Time Complexity : O(n^3)

Expand Around Center:
    Expand around every possible center.

    Time Complexity : O(n^2)

Manacher's Algorithm:
    Reuses information from previously computed palindromes to avoid
    unnecessary comparisons.

    Time Complexity : O(n)

===============================================================================
INTUITION
-------------------------------------------------------------------------------

The biggest observation is that palindromes are symmetric.

Suppose we already know this palindrome:

                center
                  |
        # a # b # c # b # a #
                  <---------->
                      right

Everything inside this palindrome has already been verified.

Now imagine we are processing another index that lies inside this palindrome.

Because of symmetry, much of its palindrome is already known.
Instead of expanding from scratch, we reuse previously computed information.

This is exactly what makes Manacher's Algorithm linear.

Instead of repeatedly checking the same characters, we remember the
rightmost palindrome discovered so far and reuse it.

===============================================================================
WHY DO WE TRANSFORM THE STRING?
-------------------------------------------------------------------------------

Original string

    abba

contains

Odd palindrome

    racecar

and

Even palindrome

    abba

Handling these separately complicates the algorithm.

Instead we transform the string.

Original

    abba

Transformed

    #a#b#b#a#

Now every palindrome has odd length.

Every palindrome has exactly ONE center.

So we only need one algorithm.

===============================================================================
RADIUS ARRAY
-------------------------------------------------------------------------------

We maintain an array

    p[i]

where

    p[i] = radius of the palindrome centered at index i
           in the transformed string.

Example

        # a # b # b # a #
              ^
              i

Suppose

    p[i] = 4

Then the palindrome spans

    [i-4 , i+4]

Notice:

p[i] is NOT the palindrome length.

In the transformed string

    palindrome length = 2*p[i] + 1

===============================================================================
MAIN IDEA
-------------------------------------------------------------------------------

Maintain two variables:

    center
        Center of the current rightmost palindrome.

    right
        Right boundary of that palindrome.

Initially

    center = 0
    right  = 0

These two variables allow us to reuse previously computed answers.

===============================================================================
ALGORITHM
-------------------------------------------------------------------------------

For every index i in the transformed string:

1. Check whether i lies inside the current palindrome.

    If

        i < right

    then we already know part of the answer.

2. Find the mirror position.

        mirror = 2 * center - i

3. Copy the already known radius.

        p[i] = min(right - i, p[mirror])

4. Expand further while characters match.

5. If the palindrome extends farther than the current right boundary,

        update center
        update right

6. Track the maximum radius while processing.

7. Convert the answer back to the original string.

===============================================================================
EXAMPLE
-------------------------------------------------------------------------------

Input

    "abba"

Transformed

    # a # b # b # a #

Index

    0 1 2 3 4 5 6 7 8

Suppose after running the algorithm

    p =

    0 1 0 1 4 1 0 1 0

Maximum radius

    center = 4
    radius = 4

Convert back

    start = (4 - 4) / 2
          = 0

Longest palindrome length

    radius = 4

Answer

    "abba"

===============================================================================
COMMON MISTAKES
-------------------------------------------------------------------------------

1. Forgetting to transform the string.

2. Forgetting that p[i] stores radius, NOT length.

3. Forgetting the mirror optimization.

4. Copying

       p[mirror]

   directly.

   Correct

       p[i] = min(right - i, p[mirror])

5. Forgetting to update

       center
       right

6. Converting indices incorrectly.

===============================================================================
TIME COMPLEXITY
-------------------------------------------------------------------------------

Transformation

    O(n)

Manacher

    O(n)

Overall

    O(n)

Space Complexity

    O(n)

===============================================================================
INTERVIEW TIPS
-------------------------------------------------------------------------------

When should you use Manacher?

✓ Longest Palindromic Substring
✓ Longest Palindromic Subarray
✓ Problems requiring palindrome preprocessing

Advantages

✓ Linear time
✓ Elegant use of symmetry
✓ Much faster than Expand Around Center for large inputs

Remember the flow:

    Transform
        ↓
    For every center
        ↓
    Copy mirror radius if possible
        ↓
    Expand
        ↓
    Update center & right
        ↓
    Track maximum radius
        ↓
    Convert answer

===============================================================================
*/

#include <bits/stdc++.h>
using namespace std;

string longestPalindrome(const string &s)
{
    // Transform: "abba" -> "#a#b#b#a#"
    string t;
    t.reserve(2 * s.size() + 1);

    t.push_back('#');
    for (char c : s)
    {
        t.push_back(c);
        t.push_back('#');
    }

    int n = t.size();
    vector<int> p(n, 0);

    int center = 0;
    int right = 0;

    int bestCenter = 0;
    int bestRadius = 0;

    for (int i = 0; i < n; i++)
    {
        if (i < right)
        {
            int mirror = 2 * center - i;
            p[i] = min(right - i, p[mirror]);
        }

        while (i - p[i] - 1 >= 0 &&
               i + p[i] + 1 < n &&
               t[i - p[i] - 1] == t[i + p[i] + 1])
        {
            p[i]++;
        }

        if (i + p[i] > right)
        {
            center = i;
            right = i + p[i];
        }

        if (p[i] > bestRadius)
        {
            bestRadius = p[i];
            bestCenter = i;
        }
    }

    int start = (bestCenter - bestRadius) / 2;
    return s.substr(start, bestRadius);
}

int main()
{
    string s = "babad";

    cout << longestPalindrome(s);

    return 0;
}