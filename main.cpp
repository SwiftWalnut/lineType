// main.cpp
#include "lineType.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

bool isSquare(const vector<Point>& points);
bool isRectangle(const vector<Point>& points);
bool isRhombus(const vector<Point>& points);
bool isParallelogram(const vector<lineType>& lines);
bool isTrapezoid(const vector<lineType>& lines);
double distance(const Point& p1, const Point& p2);

int main() {
    ifstream inputFile("data.txt");
    if (!inputFile) {
        cout << "Error opening file." << endl;
        return 1;
    }

    vector<lineType> lines(4);
    while (inputFile >> lines[0] >> lines[1] >> lines[2] >> lines[3]) {
        Point p1, p2, p3, p4;
        bool ok1 = lines[0].intersectionPoint(lines[2], p1);
        bool ok2 = lines[2].intersectionPoint(lines[1], p2);
        bool ok3 = lines[1].intersectionPoint(lines[3], p3);
        bool ok4 = lines[3].intersectionPoint(lines[0], p4);

        if (!(ok1 && ok2 && ok3 && ok4)) {
            cout << "Invalid quadrilateral (lines may be parallel)." << endl;
            continue;
        }

        vector<Point> points = { p1, p2, p3, p4 };

        if (isSquare(points))
            cout << "Square" << endl;
        else if (isRectangle(points))
            cout << "Rectangle" << endl;
        else if (isRhombus(points))
            cout << "Rhombus" << endl;
        else if (isParallelogram(lines))
            cout << "Parallelogram" << endl;
        else if (isTrapezoid(lines))
            cout << "Trapezoid" << endl;
        else
            cout << "Other Quadrilateral" << endl;
    }

    inputFile.close();
    return 0;
}

istream& operator>>(istream& in, lineType& line) {
    double a, b, c;
    in >> a >> b >> c;
    line = lineType(a, b, c);
    return in;
}

// Helper Functions

double distance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

bool isSquare(const vector<Point>& points) {
    double d1 = distance(points[0], points[1]);
    double d2 = distance(points[1], points[2]);
    double d3 = distance(points[2], points[3]);
    double d4 = distance(points[3], points[0]);
    double diag1 = distance(points[0], points[2]);
    double diag2 = distance(points[1], points[3]);
    return fabs(d1 - d2) < 1e-6 && fabs(d2 - d3) < 1e-6 && fabs(d3 - d4) < 1e-6 && fabs(diag1 - diag2) < 1e-6;
}

bool isRectangle(const vector<Point>& points) {
    double d1 = distance(points[0], points[1]);
    double d2 = distance(points[1], points[2]);
    double d3 = distance(points[2], points[3]);
    double d4 = distance(points[3], points[0]);
    double diag1 = distance(points[0], points[2]);
    double diag2 = distance(points[1], points[3]);
    return fabs(d1 - d3) < 1e-6 && fabs(d2 - d4) < 1e-6 && fabs(diag1 - diag2) < 1e-6;
}

bool isRhombus(const vector<Point>& points) {
    double d1 = distance(points[0], points[1]);
    double d2 = distance(points[1], points[2]);
    double d3 = distance(points[2], points[3]);
    double d4 = distance(points[3], points[0]);
    return fabs(d1 - d2) < 1e-6 && fabs(d2 - d3) < 1e-6 && fabs(d3 - d4) < 1e-6;
}

bool isParallelogram(const vector<lineType>& lines) {
    return (lines[0].isParallel(lines[1]) && lines[2].isParallel(lines[3]));
}

bool isTrapezoid(const vector<lineType>& lines) {
    int parallelPairs = 0;
    if (lines[0].isParallel(lines[1])) parallelPairs++;
    if (lines[0].isParallel(lines[2])) parallelPairs++;
    if (lines[0].isParallel(lines[3])) parallelPairs++;
    if (lines[1].isParallel(lines[2])) parallelPairs++;
    if (lines[1].isParallel(lines[3])) parallelPairs++;
    if (lines[2].isParallel(lines[3])) parallelPairs++;
    return parallelPairs == 1;
}
