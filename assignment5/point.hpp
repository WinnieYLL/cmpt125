#ifndef _POINT_HPP
#define _POINT_HPP

#include <iostream>
#include <cmath>
#include <string>

using namespace std;

// the class represents a point in 2D and its name
class Point
{
  private:
    int m_x;
    int m_y;
    string m_name;

  public:
    Point(int x, int y, string name)
      : m_x(x), m_y(y), m_name(name)
    {}

    int getX() const {return m_x;}
    void setX(int x) {m_x=x;}

    int getY() const {return m_y;}
    void setY(int y) {m_y=y;}

    string getName() const {return m_name;}

    float getDistance(const Point &other) const; 

    string toString() const;

    void printPoint() const;

    // used for printing Point using << operator. For example:
    // Point p(1,2,"A");
    // cout << p << endl;
    friend ostream& operator<<(ostream &os, const Point &p);

};


#endif
