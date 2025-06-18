#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <queue>

using namespace std;

//type
typedef pair<int, int> Point;
typedef pair<Point, Point> Segment;
typedef vector<deque<size_t>> Graph;

constexpr Point INVALID_POINT = { -1, -1 };
constexpr size_t INVALID_INDEX = -1;


//const
constexpr int N = 10;
constexpr int SqN = N * N;
constexpr int innerN = 2 * N + 1;
constexpr int innerSqN = innerN * innerN;

//utils
inline Point GetPoint(size_t index)
{
    int x = index / innerN;
    int y = index - x * innerN;

    return { x, y };
}

inline Point GetOriginalPoint(size_t originalIndex)
{
    int x = originalIndex / N;
    int y = originalIndex - x * N;

    return { x, y };
}

inline size_t GetPointIndex(const Point& point)
{
    return point.first * innerN + point.second;
}


inline Point ToInnerPoint(const Point& point)
{
    return { 2 * point.first + 1, 2 * point.second + 1 };
}

inline Point ToOriginalPoint(const Point& point)
{
    return { (point.first - 1) / 2, (point.second - 1) / 2 };
}

int CCW(const pair<int, int>& p0, const pair<int, int>& p1, const pair<int, int>& p2);
bool isIntersect(const Point& p0, const Point& p1, const Point& q0, const Point& q1);
bool isIntersect(const Graph& wallGraph, const Point& p0, const Point& p1);


void Algorithm(const std::vector<pair<Point, Point>>& wallSet, __out std::vector<Point>& answer);

