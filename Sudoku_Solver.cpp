#include "Sudoku_Solver.h"
#include <algorithm>

// Function to check if a character is already in the given box
bool Solution::check_box(vector<char> &box, char ch)
{
    for (auto &val : box)
    {
        if (val == ch)
            return true;
    }
    return false;
}

// Function to check if a character is already in the given row
bool Solution::check_row(vector<char> &row, char ch)
{
    for (auto &val : row)
    {
        if (val == ch)
            return true;
    }
    return false;
}

// Function to check if a character is already in the given column
bool Solution::check_column(vector<vector<char>> &board, int col, char ch)
{
    for (int i = 0; i < 9; i++)
    {
        if (board[i][col] == ch)
            return true;
    }
    return false;
}

// Function to fill the frequency matrix for possible values in each cell
void Solution::fill(vector<vector<vector<char>>> &freq, vector<vector<char>> &box, vector<vector<char>> &board)
{
    for (char num = '1'; num <= '9'; ++num)
    {
        for (int i = 0; i < 9; ++i)
        {
            int r = (i / 3) * 3;
            for (int j = 0; j < 9; ++j)
            {
                int c = (j / 3);
                if (check_box(box[r + c], num))
                    continue;
                if (check_row(board[i], num))
                    continue;
                if (check_column(board, j, num))
                    continue;
                freq[i][j].push_back(num);
            }
        }
    }
}

// Function to remove a character from the frequency list
void Solution::remove(vector<char> &freq, char ch)
{
    auto it = find(freq.begin(), freq.end(), ch);
    if (it != freq.end())
    {
        freq.erase(it);
    }
}

// Function to update the frequency matrix after placing a number
void Solution::refill(vector<vector<vector<char>>> &freq, int r, int c, char ch)
{
    for (int i = 0; i < 9; i++)
    {
        remove(freq[i][c], ch);
        remove(freq[r][i], ch);
    }
    r = (r / 3) * 3;
    c = (c / 3) * 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            remove(freq[r + i][c + j], ch);
        }
    }
}

// Function to place numbers in the board based on frequency matrix
bool Solution::write(vector<vector<char>> &board, vector<vector<vector<char>>> &freq)
{
    bool written = false;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] == '.' && freq[i][j].size() == 1)
            {
                board[i][j] = freq[i][j].back();
                freq[i][j].clear();
                written = true;
                refill(freq, i, j, board[i][j]);
            }
        }
    }
    return written;
}

// Recursive function to solve the Sudoku puzzle
bool Solution::solve(vector<vector<char>> &board, vector<vector<char>> &box, vector<vector<vector<char>>> &freq)
{
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            if (board[i][j] == '.')
            {
                for (char &num : freq[i][j])
                {
                    int r = (i / 3) * 3 + (j / 3);
                    if (!check_row(board[i], num) && !check_column(board, j, num) && !check_box(box[r], num))
                    {
                        board[i][j] = num;
                        box[r].push_back(num);
                        if (solve(board, box, freq))
                            return true;
                        board[i][j] = '.';
                        box[r].pop_back();
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// Main function to solve the Sudoku puzzle
void Solution::solveSudoku(vector<vector<char>> &board)
{
    vector<vector<char>> box(9);
    vector<vector<vector<char>>> freq(9, vector<vector<char>>(9));

    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            if (board[i][j] != '.')
            {
                int r = (i / 3) * 3 + (j / 3);
                box[r].push_back(board[i][j]);
            }
        }
    }

    fill(freq, box, board);

    while (write(board, freq))
    {
    }

    solve(board, box, freq);
}
