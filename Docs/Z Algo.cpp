/*
===============================================================================
                           Z ALGORITHM
                  Prefix Matching in O(n)
===============================================================================

PROBLEM
-------
For every index i in a string s, find the length of the longest substring
starting at i that matches the PREFIX of the string.

Example:
    s = "aaaa"

    z = [0, 3, 2, 1]

Meaning:
    z[1] = 3  -> "aaa" matches prefix "aaa"
    z[2] = 2  -> "aa"  matches prefix "aa"
    z[3] = 1  -> "a"   matches prefix "a"

Applications
------------
1. Pattern Matching
2. Finding repeated prefixes
3. String periodicity
4. Borders of a string

Time Complexity : O(n)

===============================================================================
INTUITION
-------------------------------------------------------------------------------

The naive approach compares the prefix with every suffix separately.

Example:

Prefix
a a b c

Compare with

a a b c
a b c
b c
c

This takes O(n²).

Observation:
If we already know that some substring matches the prefix, we should reuse
that information instead of comparing again.

So we maintain a window:

    [l, r]

such that

    s[l...r] == s[0...r-l]

Everything inside this window is already VERIFIED.

===============================================================================
STEP 1 : Maintain the Z Window
-------------------------------------------------------------------------------

Window:

        l           r
        |-----------|
String: a a b c a a b c

This means:

    s[l..r] == prefix

We will try to reuse information from this window.

===============================================================================
STEP 2 : Traverse Every Index
-------------------------------------------------------------------------------

For every index i from 1 to n-1, there are two cases.

===============================================================================
CASE 1 : i > r
-------------------------------------------------------------------------------

Current index is OUTSIDE the Z window.

We know nothing.

Compute the answer manually.

Algorithm:

    l = r = i

    while(characters match)
        r++

    z[i] = r - l
    r--

Now we have discovered a new Z window.

===============================================================================
CASE 2 : i <= r
-------------------------------------------------------------------------------

Current index is INSIDE the Z window.

We already know some matching information.

Mirror index inside the prefix:

    idx = i - l

This tells us which previously computed Z value corresponds to i.

===============================================================================
CASE 2A : Match Completely Inside Window
-------------------------------------------------------------------------------

Check

    i + z[idx] <= r

Meaning

The copied match DOES NOT cross the current Z window.

Therefore

    z[i] = z[idx]

No comparisons are needed.

===============================================================================
CASE 2B : Match Crosses Boundary
-------------------------------------------------------------------------------

Check

    i + z[idx] > r

Meaning

The copied match MAY continue beyond the current window.

Inside the window we are already sure characters match.

But outside the window we know nothing.

Therefore:

    l = i

Continue matching from r+1.

    while(characters match)
        r++

Update

    z[i] = r - l
    r--

===============================================================================
WHY IS THE ALGORITHM O(n)?
-------------------------------------------------------------------------------

The important observation:

    r NEVER moves backward.

Every expansion only moves r forward.

Each character is compared at most once while expanding.

Therefore

    Time = O(n)

===============================================================================
PATTERN MATCHING
-------------------------------------------------------------------------------

To find pattern P in text T

Create

    P + "$" + T

Example

Pattern = abc
Text    = ababcabc

Combined

    abc$ababcabc

Compute the Z array.

Whenever

    z[i] == length(pattern)

Pattern occurs at that position.

===============================================================================
MEMORY TRICK
-------------------------------------------------------------------------------

Maintain Z Window

        ↓

For every index

        ↓

Outside window?
        YES -> Expand manually

        NO

Mirror index = i-l

        ↓

Fits inside window?
        YES -> Copy

        NO  -> Expand

        ↓

Update window

===============================================================================
COMMON MISTAKES
-------------------------------------------------------------------------------

1. Using

       idx = i-r

   instead of

       idx = i-l

2. Forgetting

       r--

3. Wrong condition

       i + z[idx] <= r

4. Forgetting to update l before expanding.

===============================================================================
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> zFunction(string s)
{
    int n = s.size();
    vector<int> z(n, 0);

    for (int i = 1, l = 0, r = 0; i < n; i++)
    {
        // CASE 1 : Outside current Z window
        if (i > r)
        {
            l = r = i;

            while (r < n && s[r] == s[r - l])
                r++;

            z[i] = r - l;
            r--;
        }
        // CASE 2 : Inside current Z window
        else
        {
            int idx = i - l;

            // CASE 2A : Match remains inside the window
            if (i + z[idx] <= r)
            {
                z[i] = z[idx];
            }
            // CASE 2B : Match may extend beyond the window
            else
            {
                l = i;

                while (r < n && s[r] == s[r - l])
                    r++;

                z[i] = r - l;
                r--;
            }
        }
    }

    return z;
}

int main()
{
    string s = "aaaa";

    vector<int> z = zFunction(s);

    for (int x : z)
        cout << x << " ";

    return 0;
}
