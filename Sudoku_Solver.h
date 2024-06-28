#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>

using namespace std;

class Solution
{
private:
    bool check_box(vector<char> &box, char ch);
    bool check_row(vector<char> &row, char ch);
    bool check_column(vector<vector<char>> &board, int col, char ch);
    void fill(vector<vector<vector<char>>> &freq, vector<vector<char>> &box, vector<vector<char>> &board);
    void remove(vector<char> &freq, char ch);
    void refill(vector<vector<vector<char>>> &freq, int r, int c, char ch);
    bool write(vector<vector<char>> &board, vector<vector<vector<char>>> &freq);
    bool solve(vector<vector<char>> &board, vector<vector<char>> &box, vector<vector<vector<char>>> &freq);

public:
    void solveSudoku(vector<vector<char>> &board);
};

#endif // SOLUTION_H
