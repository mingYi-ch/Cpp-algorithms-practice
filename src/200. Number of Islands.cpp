#include <vector>
#include <array>
#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;

class Solution
{
public:
    int numIslands(vector<vector<char>> &grid)
    {
        size_t landNum = 0;
        for (size_t ridx = 0; ridx < grid.size(); ridx++)
        {
            for (size_t cidx = 0; cidx < grid[ridx].size(); cidx++)
            {
                char cell = grid[ridx][cidx];
                if (cell == '1')
                {
                    ++landNum;
                    deque<pair<int, int>> neis;
                    pair<int, int> neiCoord(ridx, cidx);
                    neis.push_back(neiCoord);

                    // find all connected cells
                    while (!neis.empty())
                    {
                        auto nei = neis.front();
                        neis.pop_front();
                        int ridx_nei = nei.first;
                        int cidx_nei = nei.second;

                        grid[ridx_nei][cidx_nei] = '-';
                        // right
                        if (ridx_nei + 1 < grid.size() && grid[ridx_nei + 1][cidx_nei] == '1')
                        {
                            neis.emplace_back(ridx_nei + 1, cidx_nei);
                        }
                        // down
                        if (cidx_nei + 1 < grid[ridx_nei].size() && grid[ridx_nei][cidx_nei + 1] == '1')
                        {
                            pair<int, int> neiCoord(ridx_nei, cidx_nei + 1);
                            neis.push_back(neiCoord);
                        }

                        // up
                        if (ridx_nei - 1 < grid.size() && grid[ridx_nei - 1][cidx_nei] == '1')
                        {
                            pair<int, int> neiCoord(ridx_nei - 1, cidx_nei);
                            neis.push_back(neiCoord);
                        }

                        // down
                        if (cidx_nei - 1 < grid[ridx_nei].size() && grid[ridx_nei][cidx_nei - 1] == '1')
                        {
                            pair<int, int> neiCoord(ridx_nei, cidx_nei - 1);
                            neis.push_back(neiCoord);
                        }
                    }
                }
                else
                {
                    // assigned or water cell
                    continue;
                }
            }
        }
        return landNum;
    }
};