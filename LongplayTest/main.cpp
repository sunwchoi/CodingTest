#include <iostream>
#include <vector>
#include <chrono>

#include "Algorithm.h"

extern deque<std::vector<pair<Point, Point>>> WallSets;

void Visualizer(const vector<pair<Point, Point>>& wallSet, const vector<Point>& answer, const chrono::milliseconds& time)
{
    std::cout << "\033[2J\033[H";

    vector<string> map(innerN, string(innerN, '*'));

    for (size_t i = 0; i < answer.size(); i++)
    {
        Point p = ToInnerPoint(answer[i]);
        map[p.second][p.first] = i + '0';
    }

    for (size_t i = 0; i < wallSet.size(); i++)
    {
        const auto& wall = wallSet[i];

        const Point& p0 = ToInnerPoint(wall.first);
        const Point& p1 = ToInnerPoint(wall.second);

        int x0 = p0.first, x1 = p1.first;
        int y0 = p0.second, y1 = p1.second;

        if (x0 == x1)
        {
            int y = (y0 + y1) / 2;
            
            map[y][x0] = 'w';
            map[y][x0 - 1] = 'w';
            map[y][x0 + 1] = 'w';
        }
        else
        {
            int x = (x0 + x1) / 2;

            map[y0][x] = 'w';
            map[y0 - 1][x] = 'w';
            map[y0 + 1][x] = 'w';
        }

    }

    for (size_t i = 0; i < map.size(); i++)
    {
        for (size_t j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] == 'w')
                cout << "\033[34m" << map[i][j] << "\033[0m" << " ";
            else if (map[i][j] == '*')
                cout << map[i][j] << " ";
            else
                cout << "\033[31m" << map[i][j] << "\033[0m" << " ";



        }
        cout << "\n";
    }

    cout << "\n[";
    for (size_t i = 0; i < answer.size(); i++)
    {
        cout << "(" << answer[i].first << ", " << answer[i].second << ")";
        if (i != answer.size() - 1)
            cout << ", ";
    }
    cout << "]\n";

    cout << "Time: " << time.count() << "ms" << "\n";
}

void GenerateRandomWallSet(__out vector<pair<Point, Point>>& wallSet)
{
    int dir[2][2] = { {0, 1}, {1, 0} };
    vector<vector<bool>> visit(SqN, vector<bool>(2));

    for (int i = 0; i < N; i++)
    {
        visit[(N - 1) * N + i][1] = true;
        visit[(i + 1) * N - 1][0] = true;
    }

    int randSize = rand() % SqN;
    for (int i = 0; i < randSize; i++)
    {
        int randIdx = rand() % SqN;
        int randDir = rand() % 2;

        if (visit[randIdx][randDir])
            continue;
        visit[randIdx][randDir] = true;

        Point p0 = GetOriginalPoint(randIdx);
        wallSet.push_back({ p0, {p0.first + dir[randDir][0], p0.second + dir[randDir][1]}});
    }
}

int main()
{
    cout << "Preset TEST(1), Random TEST(2), Performance TEST(3)" << "\n";
    cout << "Press Test Number: ";
    string test;
    cin >> test;

    while (1)
    {
        std::cout << "\033[2J\033[H";

        vector<pair<Point, Point>> wallSet;
        static int testCase = 0;
        if (test == "1")
        {
            if (WallSets.empty())
            {
                cout << "(No More Preset DATA... End TEST)\n";
                return 0; 
            }
            wallSet = WallSets.front();
            WallSets.pop_front();
        }
        else if (test == "2")
        {
            GenerateRandomWallSet(wallSet);
        }
        else if (test == "3")
        {
            GenerateRandomWallSet(wallSet);
            if (testCase == 0)
                testCase = 100;
        }

        auto start = std::chrono::high_resolution_clock::now();

        std::vector<Point> answer;
        Algorithm(wallSet, answer);

        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        static long long durationAverage = 0;
        durationAverage += duration.count();

        Visualizer(wallSet, answer, duration);

        if (test != "3" || (test == "3" && testCase == 1))
        {
            if (test == "3")
            {
                testCase = 0;
                cout << "\033[2J\033[H";
                cout << "TEST 100 AVERAGE: " << durationAverage / 100 << "MS" << "\n";
                durationAverage = 0;
            }
            cout << "(Press Anykey To Continue...)\n";
            string input;
            cin >> input;
        }
        else
        {
            testCase--;
        }
    }
}
