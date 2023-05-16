#include <bits/stdc++.h>
#include "Point.hpp"
using namespace std;

Point::Point() : x(0.0), y(0.0) {}

Point::Point(double x, double y) : x(x), y(y) {}

Point::~Point(){} 


Point::Point(const Point& other) : Point(other.x, other.y) {}


Point::Point(Point&& other) noexcept : x(other.x), y(other.y){} 

Point& Point::operator=(const Point& other) {
    x = other.x;
    y = other.y;
    return *this;
}

Point& Point::operator=(Point&& other) noexcept{
    this->x = other.x;
    this->y = other.y;
    return *this;
}

std::ostream &operator<<(std::ostream& ost, const Point& point) {
    ost << "(" << point.x << "," << point.y << ")" << endl;
    return ost;
}

double Point::distance(const Point& point2){
    return sqrt(pow(point2.x - x, 2) + pow(point2.y - y, 2) * 1.0);
}

string Point::print(){
    return "(" + to_string(x) + "," + to_string(y) + ")";
}

Point Point::moveTowards(Point& src, Point& dest, double distance){
    if(distance < 0) {
        throw std::invalid_argument("Can't move in negative length.");
    }

    double dist = src.distance(dest);
    if(dist <= distance) {
        return dest;
    }

    double xd = (dest.x - src.x) / dist;
    double yd = (dest.y - src.y) / dist;

    double x = src.x + (xd * distance);
    double y = src.y + (yd * distance);
    return Point(x, y);
}

double Point::getX(){
    return x;
}

double Point::getY(){
    return y;
}

void Point::setX(double x_Cor){
    this->x = x_Cor;
}

void Point::setY(double y_Cor){
    this->y = y_Cor;
}