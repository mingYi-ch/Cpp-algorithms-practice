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
        // four corners
        static const array<pair<int, int>, 4> corners{{{-1, 0},
                                                       {1, 0},
                                                       {0, 1},
                                                       {0, -1}

        }}; // 3 brackets for  initializing

        for (size_t ridx = 0; ridx < grid.size(); ridx++)
        {
            for (size_t cidx = 0; cidx < grid[ridx].size(); cidx++)
            {
                char cell = grid[ridx][cidx];
                if (cell == '1') // check for new Island
                {
                    ++landNum;
                    deque<pair<int, int>> neis;
                    neis.emplace_back(ridx, cidx);
                    grid[ridx][cidx] = '-';

                    // find all connected cells
                    while (!neis.empty())
                    {
                        auto nei = neis.front();
                        neis.pop_front();

                        int ridx_nei = nei.first;
                        int cidx_nei = nei.second;

                        for (auto corner : corners)
                        {
                            int coordRow = ridx_nei + corner.first;
                            int coordCol = cidx_nei + corner.second;
                            bool isConnected = coordRow >= 0 && coordRow < grid.size() && coordCol >= 0 && coordCol < grid[coordRow].size() && grid[coordRow][coordCol] == '1'; // expend current island
                            if (isConnected)
                            {
                                neis.emplace_back(coordRow, coordCol);
                                grid[coordRow][coordCol] = '-'; // avoid revisiting
                            }
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