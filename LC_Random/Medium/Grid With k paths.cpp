/*
===============================================================================
                        3988. Create Grid With Exactly K Paths I
Difficulty: Medium
Link: https://leetcode.com/problems/create-grid-with-exactly-k-paths-i/

Author: <Your Name>
Language: C++

-------------------------------------------------------------------------------
Problem
-------------------------------------------------------------------------------

You are given three integers m, n, and k.

Construct an m × n grid consisting of:

    '.' -> Free cell
    '#' -> Obstacle

such that there are exactly k valid paths from the top-left cell
(0,0) to the bottom-right cell (m-1,n-1).

A valid path:
    • Starts at (0,0)
    • Ends at (m-1,n-1)
    • Can only move Right or Down.

Return any valid grid.
If impossible, return an empty array.

Constraints:
    1 <= m, n <= 10
    1 <= k <= 4

-------------------------------------------------------------------------------
Approach
-------------------------------------------------------------------------------

Observation:

Since k <= 4, we do not need to construct arbitrary numbers of paths.
We only need to create at most four paths.

Step 1:
Create a grid having exactly ONE path.

We make

    First row     -> all '.'
    Last column   -> all '.'

Everything else remains '#'.

Example:

. . . .
# # # .
# # # .
# # # .

There is only one possible path:

Right -> Right -> Right -> Down -> Down -> Down

------------------------------------------------

Step 2:
Every additional opened cell creates exactly one extra route.

If m < n:

Open cells in the second row from right to left.

Example:

. . . .
# # . .
# # # .

Each newly opened cell introduces exactly one new way of reaching
the last column.

------------------------------------------------

If m >= n:

Open cells in the second-last column from top to bottom.

Example:

. . # .
# . # .
# . # .
# . . .

Again, every opened cell contributes exactly one extra path.

------------------------------------------------

Special Cases

1. Single row / single column

Only one path can ever exist.

Therefore:

if k > 1
    return {}

2. 3 × 3 with k = 4

The above construction cannot generate 4 paths.

A special hardcoded grid is used:

..#
...
#..

which contains exactly four paths.

-------------------------------------------------------------------------------
Correctness
-------------------------------------------------------------------------------

• Initial construction guarantees exactly one path.

• Every additional opened cell creates one independent alternative
  without affecting previously created paths.

• Since k ≤ 4, opening at most three additional cells is sufficient.

-------------------------------------------------------------------------------
Time Complexity
-------------------------------------------------------------------------------

Building the grid:
    O(m × n)

Opening extra cells:
    O(max(m, n))

Overall:
    O(m × n)

-------------------------------------------------------------------------------
Space Complexity
-------------------------------------------------------------------------------

Grid storage:
    O(m × n)

===============================================================================
*/

class Solution
{
public:
    vector<string> createGrid(int m, int n, int k)
    {

        // A single row or column can only have one path.
        if ((m == 1 || n == 1) && k > 1)
            return {};

        // Special case needed for generating exactly 4 paths.
        if (m == 3 && n == 3 && k == 4)
            return {"..#", "...", "#.."};

        // Initially fill everything with obstacles.
        vector<string> grid(m, string(n, '#'));

        // Open the last column.
        for (int i = 0; i < m; i++)
            grid[i][n - 1] = '.';

        // Open the first row.
        for (int j = 0; j < n; j++)
            grid[0][j] = '.';

        // Exactly one path already exists.
        if (k == 1)
            return grid;

        k--;

        // Add extra paths.
        if (m < n)
        {

            int col = n - 2;

            while (col >= 0 && k)
            {
                grid[1][col] = '.';
                col--;
                k--;
            }
        }
        else
        {

            int row = 1;

            while (row < m && k)
            {
                grid[row][n - 2] = '.';
                row++;
                k--;
            }
        }

        // Unable to create required number of paths.
        if (k)
            return {};

        return grid;
    }
};