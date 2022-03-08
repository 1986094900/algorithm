// Dijkstra.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <memory>
#include <climits>
#include <ctime>
#include <assert.h>

using namespace std;

int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

int GRID_X = 10000;
int GRID_Y = 10000;

int START_X = 0, END_X = 100;
int START_Y = 0, END_Y = 100;

class Timer {
public:
    clock_t startTime, endTime;
    Timer() : startTime(0), endTime(0) {}
    void start() { startTime = clock(); }
    void stop() { endTime = clock(); }
    double getElapseTime() {
        return (double(endTime) - double(startTime)) / 1000.0;
    }
};

class Vertex {
public:
    int vertex;
    int realCost;
    int totalCost;
    Vertex* parent;

    Vertex(int ver, int real, int total, Vertex* pa) : vertex(ver), realCost(real), totalCost(total), parent(pa) {}

    ~Vertex() {}
};

class Point {
public:
    int x;
    int y;

    Point(int xx, int yy) : x(xx), y(yy) {}
};

int getVertexByPoint(const Point& pos) {
    return pos.y * GRID_X + pos.x;
}

Point getPointByVertex(int vertex) {
    return Point(vertex % GRID_X, vertex / GRID_X);
}

int main()
{
    std::cout << "start\n";
    //for (int k = 1; k <= 20; ++k) {

        /*END_X = 100 * 1;
        END_Y = 100 * 1;*/

    int a[4] = { 55, 100, 65, 120 };
    int b[4] = { 120, 80, 130, 95 };

    int bbox[4] = { 40, 40, END_X, END_Y };

        GRID_X = std::max(END_X + 1, 3000);
        GRID_Y = std::max(END_Y + 1, 3000);

        Point startPoint(START_X, START_Y);
        Point endPoint(END_X, END_Y);

        int nodeNum = GRID_X * GRID_Y;

        vector<int> vertexCost(nodeNum, INT_MAX);

        auto cmp = [&](const Vertex* lhs, const Vertex* rhs) {
            return lhs->totalCost > rhs->totalCost;
        };
        priority_queue<Vertex*, vector<Vertex*>, decltype(cmp)> pq(cmp);

        int startVertex = getVertexByPoint(startPoint);
        vertexCost[startVertex] = 0;
        pq.push(new Vertex(startVertex, 0, 0, nullptr));

        Vertex* targetPointer = nullptr;

        FILE* popFile = fopen("C:/Users/Administrator/PycharmProjects/pythonLearning/pin/pin_N3.txt", "w");

        int popNum = 0;

        Timer time;
        time.start();
        while (!pq.empty()) {
            Vertex* curPointer = pq.top();
            pq.pop();
            int curVertex = curPointer->vertex;
            int realCost = curPointer->realCost;

            Point curPoint = getPointByVertex(curVertex);
            fprintf(popFile, "%d %d 0\n", curPoint.x, curPoint.y);

            // std::cout << popNum << " : "<< curPoint.x << " " << curPoint.y << "\n";
            ++popNum;

            if (curPoint.x == endPoint.x && curPoint.y == endPoint.y) {
                targetPointer = curPointer;
                break;
            }

            if (realCost > vertexCost[curVertex]) continue;


            for (int d = 0; d < 4; ++d) {
                int newX = curPoint.x + dir[d][0];
                int newY = curPoint.y + dir[d][1];

                if (newX < 0 || newY < 0 || newX >= GRID_X || newY >= GRID_Y) continue;

                Point newPoint(newX, newY);

                /*f (newPoint.x < bbox[0] || newPoint.y < bbox[1] || newPoint.x > bbox[2] || newPoint.y > bbox[3]) {
                    continue;
                }*/

                int newVertex = getVertexByPoint(newPoint);
                if (curPointer->parent && curPointer->parent->vertex == newVertex) continue;

                // A star cost
                int newRealCost = realCost + 1;
                int predictCost = std::abs(newX - endPoint.x) + std::abs(newY - endPoint.y);
                //int predictCost = sqrt((newX - endPoint.x) * (newX - endPoint.x) + (newY - endPoint.y) * (newY - endPoint.y));

                /*int totalCost = 0.0;
                if ((newPoint.x >= a[0] && newPoint.y >= a[1] && newPoint.x <= a[2] && newPoint.y <= a[3]) ||
                    (newPoint.x >= b[0] && newPoint.y >= b[1] && newPoint.x <= b[2] && newPoint.y <= b[3])) {
                    std::cout << newPoint.x<<" "<< newPoint.y<<"\n";
                    newRealCost = 10000;
                    totalCost = 10000;
                }
                else {
                    newRealCost = realCost + 1;
                    totalCost = 0.5 * predictCost + 0.5 * newRealCost;
                }*/

                int totalCost = 0.5 * predictCost + 0.5 * newRealCost;
                
                //int totalCost = 0.6 * predictCost + 0.4 * newRealCost;

                if (newRealCost < vertexCost[newVertex]) {
                    vertexCost[newVertex] = newRealCost;
                    Vertex* newPointer = new Vertex(newVertex, newRealCost, totalCost, curPointer);
                    pq.push(newPointer);
                }
            }
        }
        
        time.stop();

        if (popFile) fclose(popFile);

        if (targetPointer == nullptr) {
            std::cout << "can not find target point\n";
        }

        // FILE* path = fopen("C:/Users/Administrator/PycharmProjects/pythonLearning/net/path.txt", "w");
        Vertex* cur = targetPointer;
        int length = 0;
        while (cur != nullptr) {
            Point curPos = getPointByVertex(cur->vertex);
            // std::cout << curPos.x << " " << curPos.y << "\n";
            cur = cur->parent;

            /*if (cur) {
                Point prePos = getPointByVertex(cur->vertex);
                fprintf(path, "%d %d 0\n", curPos.x, curPos.y);
                fprintf(path, "%d %d 0\n", prePos.x, prePos.y);
            }*/

            ++length;
        }
        // if (path) fclose(path);
        std::cout << "pop    : " << popNum << "\n";
        std::cout << "length : " << length << "\n";

        std::cout << END_X << " * " << END_Y << "\n";
        std::cout << "time   : "<< time.getElapseTime() << ", "<<"\n\n";

    //}

    return 0;
}


/*
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <memory>
#include <climits>
#include <ctime>
#include <assert.h>

using namespace std;

int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

int GRID_X = 500;
int GRID_Y = 500;

int START_X = 0, END_X = 200;
int START_Y = 0, END_Y = 200;

class Timer {
public:
    clock_t startTime, endTime;
    Timer() : startTime(0), endTime(0) {}
    void start() { startTime = clock(); }
    void stop() { endTime = clock(); }
    double getElapseTime() {
        return (double(endTime) - double(startTime)) / 1000.0;
    }
};

class Vertex {
public:
    int vertex;
    int cost;
    std::shared_ptr<Vertex> parent;

    Vertex(int ver, int dis, shared_ptr<Vertex> pa) : vertex(ver), cost(dis), parent(pa) {}

    ~Vertex() {}
};

class Point {
public:
    int x;
    int y;

    Point(int xx, int yy) : x(xx), y(yy) {}
};

int getVertexByPoint(const Point& pos) {
    return pos.y * GRID_X + pos.x;
}

Point getPointByVertex(int vertex) {
    return Point(vertex % GRID_X, vertex / GRID_X);
}

int main()
{
    std::cout << "start\n";
    for (int k = 1; k <= 20; ++k) {
        END_X = 100 * k;
        END_Y = 100 * k;

        GRID_X = std::max(END_X + 1, 5000);
        GRID_Y = std::max(END_Y + 1, 5000);

        Timer time;
        time.start();
        Point startPoint(START_X, START_Y);
        Point endPoint(END_X, END_Y);

        int nodeNum = GRID_X * GRID_Y;
        vector<int> vertexCost(nodeNum, INT_MAX);

        auto cmp = [&](const shared_ptr<Vertex>& lhs, const shared_ptr<Vertex>& rhs) {
            return lhs->cost > rhs->cost;
        };
        priority_queue<shared_ptr<Vertex>, vector<shared_ptr<Vertex>>, decltype(cmp)> pq(cmp);

        int startVertex = getVertexByPoint(startPoint);
        vertexCost[startVertex] = 0;
        pq.push(std::make_shared<Vertex>(startVertex, 0, nullptr));

        std::shared_ptr<Vertex> targetPointer = nullptr;

        int popNum = 0;
        while (!pq.empty()) {
            shared_ptr<Vertex> curPointer = pq.top();
            pq.pop();
            int curVertex = curPointer->vertex;
            int curCost = curPointer->cost;

            Point curPoint = getPointByVertex(curVertex);
            // std::cout << popNum << " : "<< curPoint.x << " " << curPoint.y << "\n";
            ++popNum;

            if (curPoint.x == endPoint.x && curPoint.y == endPoint.y) {
                targetPointer = curPointer;
                break;
            }

            if (curCost > vertexCost[curVertex]) continue;

            for (int d = 0; d < 4; ++d) {
                int newX = curPoint.x + dir[d][0];
                int newY = curPoint.y + dir[d][1];

                if (newX < 0 || newY < 0 || newX >= GRID_X || newY >= GRID_Y) continue;

                Point newPoint(newX, newY);
                int newVertex = getVertexByPoint(newPoint);
                if (curPointer->parent && curPointer->parent->vertex == newVertex) continue;

                int newCost = curPointer->cost + 1;
                if (newCost < vertexCost[newVertex]) {
                    vertexCost[newVertex] = newCost;
                    shared_ptr<Vertex> newPointer = std::make_shared<Vertex>(newVertex, newCost, curPointer);
                    pq.push(newPointer);
                }
            }
        }

        if (targetPointer == nullptr) {
            std::cout << "can not find target point\n";
        }

        //FILE* path = fopen("C:/Users/Administrator/PycharmProjects/pythonLearning/net/path.txt", "w");
        std::shared_ptr<Vertex> cur = targetPointer;
        int length = 0;
        while (cur.get() != nullptr) {
            Point curPos = getPointByVertex(cur->vertex);
            // std::cout << curPos.x << " " << curPos.y << "\n";
            cur = cur->parent;

            //if (cur) {
            //    Point prePos = getPointByVertex(cur->vertex);
            //    fprintf(path, "%d %d 0\n", curPos.x, curPos.y);
            //    fprintf(path, "%d %d 0\n", prePos.x, prePos.y);
            //}

            ++length;
        }
        //if (path) fclose(path);
        // std::cout << "pop num:" << popNum << "\n";
        // std::cout << "length:" << length << "\n";
        time.stop();
        // std::cout << END_X << " * " << END_Y << " time: " << time.getElapseTime() << "\n";
        std::cout << time.getElapseTime() << ", ";
    }

    return 0;
}
*/