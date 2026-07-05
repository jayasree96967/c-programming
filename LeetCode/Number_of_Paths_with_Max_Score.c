 ## ## Number of Paths with Maximum Score

**Platform:** LeetCode

**Problem:** Find the maximum score that can be collected while moving from the bottom-right cell (`S`) to the top-left cell (`E`) on a square board. Return both the maximum score and the number of paths that achieve this score. If no valid path exists, return `[0, 0]`.

### Approach
- Dynamic Programming (DP)
- Compute the maximum score for each cell.
- Track the number of paths that achieve the maximum score.
- Handle obstacles and apply modulo `10^9 + 7` for path counting.

### Concepts Used
- Dynamic Programming
- 2D Arrays
- Matrix Traversal
- Path Counting
- Optimization

**Time Complexity:** `O(n²)`

**Space Complexity:** `O(n²)`

**Language:** C ##

#define MOD 1000000007

int* pathsWithMaxScore(char** board, int boardSize, int* returnSize) {
    int n = boardSize;

    int dpScore[101][101];
    int dpWays[101][101];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dpScore[i][j] = -1;
            dpWays[i][j] = 0;
        }
    }

    dpScore[n - 1][n - 1] = 0;
    dpWays[n - 1][n - 1] = 1;

    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {

            if (board[i][j] == 'X' || (i == n - 1 && j == n - 1))
                continue;

            int maxScore = -1;
            long long ways = 0;

            // From below
            if (i + 1 < n && dpScore[i + 1][j] != -1) {
                if (dpScore[i + 1][j] > maxScore) {
                    maxScore = dpScore[i + 1][j];
                    ways = dpWays[i + 1][j];
                } else if (dpScore[i + 1][j] == maxScore) {
                    ways = (ways + dpWays[i + 1][j]) % MOD;
                }
            }

            // From right
            if (j + 1 < n && dpScore[i][j + 1] != -1) {
                if (dpScore[i][j + 1] > maxScore) {
                    maxScore = dpScore[i][j + 1];
                    ways = dpWays[i][j + 1];
                } else if (dpScore[i][j + 1] == maxScore) {
                    ways = (ways + dpWays[i][j + 1]) % MOD;
                }
            }

            // From diagonal
            if (i + 1 < n && j + 1 < n && dpScore[i + 1][j + 1] != -1) {
                if (dpScore[i + 1][j + 1] > maxScore) {
                    maxScore = dpScore[i + 1][j + 1];
                    ways = dpWays[i + 1][j + 1];
                } else if (dpScore[i + 1][j + 1] == maxScore) {
                    ways = (ways + dpWays[i + 1][j + 1]) % MOD;
                }
            }

            if (maxScore == -1)
                continue;

            dpWays[i][j] = ways % MOD;

            if (board[i][j] == 'E')
                dpScore[i][j] = maxScore;
            else
                dpScore[i][j] = maxScore + (board[i][j] - '0');
        }
    }

    int *ans = (int *)malloc(2 * sizeof(int));
    *returnSize = 2;

    if (dpWays[0][0] == 0) {
        ans[0] = 0;
        ans[1] = 0;
    } else {
        ans[0] = dpScore[0][0];
        ans[1] = dpWays[0][0];
    }

    return ans;
}
