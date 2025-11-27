#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // Check if placing queen is safe
    bool isSafe(vector<string> &board, int row, int col, int n)
    {
        // Column check
        for (int i = 0; i < row; i++)
            if (board[i][col] == 'Q')
                return false;

        // Left diagonal
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
            if (board[i][j] == 'Q')
                return false;

        // Right diagonal
        for (int i = row, j = col; i >= 0 && j < n; i--, j++)
            if (board[i][j] == 'Q')
                return false;

        return true;
    }

    bool nQueens(vector<string> &board, int row, int n, vector<string> &result)
    {
        if (row == n)
        { // solution complete
            result = board;
            return true;
        }

        for (int j = 0; j < n; j++)
        {
            if (isSafe(board, row, j, n))
            {
                board[row][j] = 'Q';
                if (nQueens(board, row + 1, n, result))
                    return true;     // stop immediately
                board[row][j] = '.'; // backtrack
            }
        }
        return false;
    }

    // Returns only ONE solution
    vector<string> solveOneSolution(int n)
    {
        vector<string> board(n, string(n, '.'));
        vector<string> result;
        nQueens(board, 0, n, result);
        return result;
    }
};

int main()
{
    int n;
    cout << "Enter N: ";
    cin >> n;

    Solution solver;
    vector<string> ans = solver.solveOneSolution(n);

    if (ans.empty())
    {
        cout << "No solution exists for N=" << n << endl;
    }
    else
    {
        cout << "\nOne valid solution:\n\n";
        for (string row : ans)
            cout << row << endl;
    }

    return 0;
}
