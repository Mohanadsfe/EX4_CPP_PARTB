#ifndef POINT_HPP
#define POINT_HPP
#include <string>
using namespace std;

class Point{
    private:
        double x, y;
    
    public:
        Point();
        Point(double, double);
        ~Point(); 
        Point(const Point& other); 
        Point(Point&& other) noexcept; 

        Point& operator=(const Point&);
        Point& operator=(Point&&) noexcept;

        friend std::ostream &operator<<(std::ostream& ost, const Point& point);

        double distance(const Point&);
        string print();
        static Point moveTowards(Point&, Point&, double);
        double getX();
        double getY();
        void setX(double x_Cor);
        void setY(double y_Cor);
};
#endif