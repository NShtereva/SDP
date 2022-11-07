#include <iostream>
#include <utility>
#include <vector>
#include <stack>
#include <queue>

const size_t NUMBER_OF_ROWS = 8;
const size_t NUMBER_OF_COLS = 10;

struct Position
{
    int first, second;

    bool operator == (const Position& other)
    {
        return this->first == other.first && this->second == other.second;
    }

    friend std::ostream& operator << (std::ostream& out, const Position& pos)
    {
        out << "(" << pos.first << ", " << pos.second << ")";
        return out;
    }
};

bool isInside(const Position& pos)
{
    return (pos.first  >= 0 && pos.first  < NUMBER_OF_ROWS) && 
           (pos.second >= 0 && pos.second < NUMBER_OF_COLS);
}

bool isValidMove(const Position& pos, const bool board[][NUMBER_OF_COLS])
{
    return isInside(pos) && !board[pos.first][pos.second];
}

bool findPath(bool board[][NUMBER_OF_COLS], const Position& start, const Position& end, std::vector<Position>& path)
{
    if(!isInside(start) || !isInside(end) || board[start.first][start.second])
    {
        return false;
    }

    std::stack<std::pair<Position, Position>> steps;

    std::queue<Position> wave;
    wave.push(start);

    while(!wave.empty())
    {
        Position current = wave.front();
        wave.pop();

        if(current == end)
        {
            std::stack<Position> reversePath;

            while(!steps.empty())
            {
                std::pair<Position, Position> step = steps.top();
                steps.pop();

                if(step.second == current)
                {
                    reversePath.push(current);
                    current = step.first;
                }
            }

            reversePath.push(start);

            while(!reversePath.empty())
            {
                path.push_back(reversePath.top());
                reversePath.pop();
            }

            return true;
        }

        board[current.first][current.second] = 1;

        for(int i = -1; i <= 1; i++)
        {
            for(int j = -1; j <= 1; j++)
            {
                if((std::abs(i - j) == 1) && isValidMove({current.first + i, current.second + j}, board))
                {
                    Position newPosition = {current.first + i, current.second + j};
                    wave.push(newPosition);
                    steps.push({current, newPosition});
                }
            }
        }
    }

    return false;
}

void printPath(bool board[][NUMBER_OF_COLS], const Position& start, const Position& end)
{
    std::vector<Position> path;

    bool hasPath = findPath(board, start, end, path);

    if(!hasPath)
    {
        std::cout << "No path found from " << start << " to " << end << "!" << std::endl;
        return;
    }

    size_t size = path.size();

    std::cout << "Path: ";
    
    for(size_t i = 0; i < size; i++)
    {
        std::cout << path[i];

        if(i != size - 1)
        {
            std::cout << " -> ";
        }
    }

    std::cout << std::endl;
}

int main()
{
    bool board[NUMBER_OF_ROWS][NUMBER_OF_COLS] = {
                                                    { 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 },
                                                    { 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 },
                                                    { 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 0 },
                                                    { 0 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 0 , 0 },
                                                    { 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 },
                                                    { 0 , 0 , 0 , 1 , 0 , 1 , 0 , 0 , 0 , 0 },
                                                    { 0 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 0 , 0 },
                                                    { 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 }
                                                 };

    printPath(board, {0, 0}, {7, 9});
    return 0;
}
