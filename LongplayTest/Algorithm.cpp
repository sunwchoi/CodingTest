#include "Algorithm.h"

//global
const int START = GetPointIndex(ToInnerPoint({ 0, 0 }));
const int GOAL = GetPointIndex(ToInnerPoint({ N - 1, N - 1}));

int CCW(const pair<int, int>& p0, const pair<int, int>& p1, const pair<int, int>& p2)
{
    int x0 = p0.first, x1 = p1.first, x2 = p2.first;
    int y0 = p0.second, y1 = p1.second, y2 = p2.second;

    return x0 * y1 + x1 * y2 + x2 * y0 - x1 * y0 - x2 * y1 - x0 * y2;
}

bool isIntersect(const Point& p0, const Point& p1, const Point& q0, const Point& q1)
{
    if (CCW(p0, p1, q0) * CCW(p0, p1, q1) <= 0 && CCW(q0, q1, p0) * CCW(q0, q1, p1) <= 0)
        return true;

    return false;
}

bool isIntersect(const Graph& wallGraph, const Point& p0, const Point& p1)
{
    for (size_t i = 0; i < wallGraph.size(); i++)
    {
        for (size_t j = 0; j < wallGraph[i].size(); j++)
        {
            if (isIntersect(p0, p1, GetPoint(i), GetPoint(wallGraph[i][j])))
                return true;
        }
    }

    return false;
}

// inner dfs in merge graph
static void DFS(size_t point, size_t start, vector<vector<bool>>& visit, const vector<deque<size_t>>& originalGraph, __out vector<deque<size_t>>& mergedGraph, bool isTwoWay)
{
    bool isLine = false;
    for (size_t next : originalGraph[point])
    {
        if (visit[point][next] || visit[next][point])
            continue;

        visit[point][next] = true;
        visit[next][point] = true;

        if (start != INVALID_INDEX && CCW(GetPoint(start), GetPoint(point), GetPoint(next)) == 0)
        {
            isLine = true;
            DFS(next, start, visit, originalGraph, mergedGraph, isTwoWay);
        }
        else
        {
            DFS(next, point, visit, originalGraph, mergedGraph, isTwoWay);
        }
    }

    if (start != INVALID_INDEX && isLine == false)
    {
        mergedGraph[start].push_back(point);
        if (isTwoWay)
            mergedGraph[point].push_back(start);
    }
}

// merge graph edge if on one line
// ex) originalGraph: a -> b -> c,  mergedGraph: a -> c
static void MergeGraph(const vector<deque<size_t>>& originalGraph, __out vector<deque<size_t>>& mergedGraph, bool isTwoWay)
{
    vector<vector<bool>> visit(innerSqN, vector<bool>(innerSqN));

    for (size_t i = 0; i < innerSqN; i++)
        DFS(i, INVALID_INDEX, visit, originalGraph, mergedGraph, isTwoWay);
}

// make wallset to graph
static void MakeWallGraph(const std::vector<pair<Point, Point>>& wallSet, __out Graph& wallGraph)
{
    size_t wallSetSize = wallSet.size();
    for (size_t i = 0; i < wallSetSize; i++)
    {
        const auto& wall = wallSet[i];

        bool swap = wall.first > wall.second;
        const Point& p0 = ToInnerPoint(swap == false ? wall.first : wall.second);
        const Point& p1 = ToInnerPoint(swap == false ? wall.second : wall.first);

        int x0 = p0.first, x1 = p1.first;
        int y0 = p0.second, y1 = p1.second;

        size_t startIndex, endIndex;

        if (x0 == x1)
        {
            int y = (y0 + y1) / 2;

            startIndex = GetPointIndex({ x0 - 1, y });
            endIndex = GetPointIndex({ x0 + 1, y });
        }
        else
        {
            int x = (x0 + x1) / 2;

            startIndex = GetPointIndex({ x, y0 - 1 });
            endIndex = GetPointIndex({ x, y0 + 1 });
        }

        wallGraph[startIndex].push_back(endIndex);
    }
}

// make all node connected if not intersect
static void MakePathGraph(const Graph& wallGraph, __out Graph& pathGraph)
{
    for (size_t i = 0; i < SqN; i++)
    {
        for (size_t j = i + 1; j < SqN; j++)
        {
            Point nde0 = ToInnerPoint(GetOriginalPoint(i));
            Point nde1 = ToInnerPoint(GetOriginalPoint(j));
            if (isIntersect(wallGraph, nde0, nde1) == false)
            {
                pathGraph[GetPointIndex(nde0)].push_back(GetPointIndex(nde1));
            }
        }
    }
}

// find shortest way with dijkstra algorithm
static void Dijkstra(const Graph& pathGraph, __out vector<size_t>& path)
{
    priority_queue<pair<double, pair<size_t, size_t>>, vector<pair<double, pair<size_t, size_t>>>, greater<>> que;

    que.push({ 0, {START, INVALID_INDEX} });
    while (que.empty() == false)
    {
        double d = que.top().first;
        size_t idx = que.top().second.first;
        size_t prev = que.top().second.second;

        que.pop();

        if (idx != START)
        {
            if (path[idx] != INVALID_INDEX)
                continue;

            path[idx] = prev;
            if (idx == GOAL)
                break;
        }

        const Point& point = ToOriginalPoint(GetPoint(idx));
        for (size_t i = 0; i < pathGraph[idx].size(); i++)
        {
            size_t nextIdx = pathGraph[idx][i];
            const Point& next = ToOriginalPoint(GetPoint(nextIdx));

            int dx = point.first - next.first;
            int dy = point.second - next.second;

            que.push({ d + sqrt(dx * dx + dy * dy), {nextIdx, idx } });
        }
    }
}

// make answer with path array
static void MakeAnswer(size_t idx, const std::vector<size_t>& path, __out std::vector<Point>& answer)
{
    if (path[idx] != INVALID_INDEX)
        MakeAnswer(path[idx], path, answer);

    answer.push_back(ToOriginalPoint(GetPoint(idx)));
}

void Algorithm(const std::vector<pair<Point, Point>>& wallSet, __out std::vector<Point>& answer)
{
    Graph wallGraph(innerSqN);
    MakeWallGraph(wallSet, wallGraph);

    Graph mergedWallGraph(innerSqN);
    MergeGraph(wallGraph, mergedWallGraph, false);

    Graph pathGraph(innerSqN);
    MakePathGraph(mergedWallGraph, pathGraph);

    Graph mergedPathGraph(innerSqN);
    MergeGraph(pathGraph, mergedPathGraph, true);

    vector<size_t> path(innerSqN, INVALID_INDEX);
    Dijkstra(mergedPathGraph, path);

    MakeAnswer(GOAL, path, answer);
}