
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Solution
{
public:
    bool isValidSudoku(vector<vector<char>> &board)
    {
        size_t nrow = board.size();
        size_t ncol = board[0].size();

        vector<unordered_map<char, size_t>> record_col(nrow);
        vector<vector<unordered_map<char, size_t>>> record_sq(3, vector<unordered_map<char, size_t>>(3));

        for (size_t r = 0; r < nrow; r++)
        {
            unordered_map<char, size_t> record_row;
            size_t ridx_sq = r / 3;
            for (size_t c = 0; c < ncol; c++)
            {
                char entry = board[r][c];
                if (entry == '.')
                {
                    continue;
                }

                // check row
                if (record_row[entry] == 1)
                {
                    return false;
                }
                ++record_row[entry];

                // check col
                if (record_col[c][entry] == 1)
                {
                    return false;
                }
                ++record_col[c][entry];

                // check square
                size_t cidx_sq = c / 3;
                if (record_sq[ridx_sq][cidx_sq][entry] == 1)
                {
                    return false;
                }
                ++record_sq[ridx_sq][cidx_sq][entry];
            }
        }
        return true;
    }
};