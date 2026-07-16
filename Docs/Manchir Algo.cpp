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

Naive Solution:
    Expand around every center.
    Time Complexity = O(n^2)

Manacher's Algorithm:
    Reuses information from previously found palindromes.
    Time Complexity = O(n)

===============================================================================
INTUITION
-------------------------------------------------------------------------------
This algorithm is very similar to the Z Algorithm.

Z Algorithm:
    Keep a window [l, r] that matches the prefix.

Manacher:
    Keep the RIGHTMOST palindrome discovered so far.

Instead of storing:
    [l, r]

We store:
    center = center of palindrome
    right  = right boundary of palindrome

Example:

            center
               |
#a#b#b#a#
    <-------> right

Everything inside this palindrome is already verified.
We try to reuse this information instead of recomputing it.

===============================================================================
STEP 1 : Transform the String
-------------------------------------------------------------------------------

Convert

    "abba"

into

    "#a#b#b#a#"

Why?

Normally there are two types of palindromes:

Odd:
    racecar

Even:
    abba

After transformation, EVERY palindrome becomes odd length.
Now every palindrome has exactly one center.

===============================================================================
STEP 2 : Radius Array
-------------------------------------------------------------------------------

p[i] = radius of palindrome centered at index i.

Example

#a#b#b#a#
     ^

If

    p[i] = 4

it means we can move
    4 positions left
and 4 positions right
while characters keep matching.

===============================================================================
STEP 3 : Maintain Current Largest Palindrome
-------------------------------------------------------------------------------

center = center of current rightmost palindrome
right  = right boundary of that palindrome

Initially

    center = 0
    right  = 0

===============================================================================
STEP 4 : Process Every Index
-------------------------------------------------------------------------------

For every index i:

CASE 1 : i >= right
-------------------

Current index is OUTSIDE the known palindrome.

We know nothing.

Expand manually around i.

===============================================================================
CASE 2 : i < right
-------------------------------------------------------------------------------

Current index is INSIDE the known palindrome.

Example

mirror ----- center ----- i

Because palindrome is symmetric,

whatever happens at mirror
also happens at i.

Mirror index is

    mirror = 2 * center - i

We copy the already known radius

    p[i] = min(right - i, p[mirror])

Why min() ?

Because the mirror palindrome may extend outside the current
known palindrome.

We only trust information up to "right".

===============================================================================
STEP 5 : Expand
-------------------------------------------------------------------------------

After copying,
try expanding further.

while(left and right characters match)
{
    p[i]++;
}

If expansion succeeds,
we discovered a larger palindrome.

===============================================================================
STEP 6 : Update
-------------------------------------------------------------------------------

If

    i + p[i] > right

then we found a palindrome extending farther.

Update

    center = i
    right = i + p[i]

This becomes the new palindrome we will reuse.

===============================================================================
STEP 7 : Find the Answer
-------------------------------------------------------------------------------

Find maximum value in p[].

Suppose

    centerIndex = index having maximum radius
    maxRadius   = p[centerIndex]

Convert transformed index back:

    start = (centerIndex - maxRadius) / 2

Answer

    s.substr(start, maxRadius)

===============================================================================
MEMORY TRICK
-------------------------------------------------------------------------------

Transform
    ↓
For every center
    ↓
If inside palindrome → Copy mirror
    ↓
Expand
    ↓
Update center & right
    ↓
Return longest palindrome

===============================================================================
Connection with Z Algorithm
-------------------------------------------------------------------------------

Z Algorithm                    Manacher
---------------------------------------------------------
Window [l,r]              ->   Palindrome (center,right)

idx = i-l                 ->   mirror = 2*center-i

Copy z[idx]               ->   Copy p[mirror]

Expand beyond r           ->   Expand beyond right

Update [l,r]              ->   Update (center,right)

Prefix Matching           ->   Palindrome Matching

If you understand Z Algorithm,
Manacher is simply the same optimization using palindrome symmetry.
===============================================================================
*/

#include <bits/stdc++.h>
using namespace std;

string longestPalindrome(string s)
{
    string t = "#";
    for (char c : s)
    {
        t += c;
        t += '#';
    }

    int n = t.size();
    vector<int> p(n, 0);

    int center = 0;
    int right = 0;

    for (int i = 0; i < n; i++)
    {
        int mirror = 2 * center - i;

        if (i < right)
            p[i] = min(right - i, p[mirror]);

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
    }

    int maxRadius = 0;
    int centerIndex = 0;

    for (int i = 0; i < n; i++)
    {
        if (p[i] > maxRadius)
        {
            maxRadius = p[i];
            centerIndex = i;
        }
    }

    int start = (centerIndex - maxRadius) / 2;
    return s.substr(start, maxRadius);
}

int main()
{
    string s = "babad";
    cout << longestPalindrome(s);
    return 0;
}
