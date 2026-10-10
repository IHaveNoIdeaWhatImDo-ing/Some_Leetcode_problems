#include <queue>
#include <vector>
#include <iostream>

using namespace std;

/*
    You are given an n x n integer matrix board where the cells are labeled from 1 to n2 in a
Boustrophedon style starting from the bottom left of the board (i.e. board[n - 1][0]) and
alternating direction each row.

You start on square 1 of the board. In each move, starting from square curr, do the following:

    - Choose a destination square next with a label in the range [curr + 1, min(curr + 6, n2)].
        - This choice simulates the result of a standard 6-sided die roll: i.e., there are always
          at most 6 destinations, regardless of the size of the board.
    - If next has a snake or ladder, you must move to the destination of that snake or ladder.
    - Otherwise, you move to next.
    - The game ends when you reach the square n2.

    A board square on row r and column c has a snake or ladder if board[r][c] != -1. The destination
of that snake or ladder is board[r][c]. Squares 1 and n2 are not the starting points of any snake or ladder.

    Note that you only take a snake or ladder at most once per dice roll. If the destination to
a snake or ladder is the start of another snake or ladder, you do not follow the subsequent snake or ladder.

    - For example, suppose the board is [[-1,4],[-1,3]], and on the first move, your destination square is 2.
      You follow the ladder to square 3, but do not follow the subsequent ladder to 4.

    Return the least number of dice rolls required to reach the square n2. If it is not possible to
reach the square, return -1.
*/

inline int atIndex(short n, vector<vector<int>>& grid)
{
    unsigned char dim {static_cast<unsigned char>(grid.size())};

    unsigned char row {static_cast<unsigned char>((n - 1) / dim)};
    unsigned char col {static_cast<unsigned char>((n - 1) % dim)};

    row = dim - row - 1;
    if (static_cast<bool>(dim % 2) == static_cast<bool>(row % 2))
    {
        col = dim - col - 1;
    }

    return grid[row][col];
}

struct CellDepth
{
    short num;
    short depth;

    CellDepth(short num = 0, short depth = 0) :
        num(num), depth(depth)
    {}
};

int snakesAndLadders(vector<vector<int>>& board)
{
    int n2 {static_cast<int>(board.size() * board.size())};

    queue<CellDepth> bfs {};
    bfs.emplace(1, 0);

    bool visited[401] {false};
    visited[0] = true;

    CellDepth current;
    int temp;

    int fringe {1};
    int rolls {};

    short i;
    short dice;

    while (!bfs.empty())
    {
        current = bfs.front();
        bfs.pop();
        --fringe;
        
        temp = atIndex(current.num, board);

        if (temp ^ -1)
        {
            current.num = temp;
        }

        if (current.num == n2)
        {
            return current.depth;
        }

        dice = min(current.num + 6, n2);

        for (i = current.num + 1; i <= dice; ++i)
        {
            if (!visited[i - 1])
            {
                bfs.emplace(
                    i,
                    current.depth + 1
                );
                visited[i - 1] = true;
            }
        }
    }

    return -1;
}

int main()
{
    vector<vector<int>> board1 = {{-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1},{-1,35,-1,-1,13,-1},{-1,-1,-1,-1,-1,-1},{-1,15,-1,-1,-1,-1}};
    vector<vector<int>> board2 = {{-1,-1},{-1,3}};

    cout << snakesAndLadders(board1) << '\n';
    cout << snakesAndLadders(board2) << '\n';

    return 0;
}
