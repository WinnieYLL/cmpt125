#ifndef _LIST_OF_POINT_HPP
#define _LIST_OF_POINT_HPP

#include <iostream>
#include <vector>

#include "point.hpp"

#define MAX_X 20
#define MAX_Y 20

// the class stores an ordered list of points
// used to store the input to the problem
// may be also used to store a partial solution to the TSP problem
class ListOfPoints
{
  protected: //  children of the class can access the protected data fields
    // currently m_points stores the points in a vector 
    // but you may decide to use a different container. Up to you
    std::vector<Point> m_points;

  public:
    ListOfPoints();

    // adds a new point after a point with the given name in the list
    void addAfter(Point& newPt, string name);

    // adds a new point to the end of the list
    void addPoint(Point& newPt);
    
    // gets a point from the list at index i
    Point& getPointAt(unsigned int i);

    // gets the size of the list
    int getSize() const;

    // prints the list of points
    void printList() const;
    
    // draws the points
    void draw() const;

    // operator =
    ListOfPoints& operator=(const ListOfPoints& other);
};

#endif
