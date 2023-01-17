#include <iostream>

#include "tspcycle.hpp"

TSPCycle::TSPCycle() {
//  cout << "default TSPCycle constructor" << endl;
}

// returns the length of the cycle
float TSPCycle::getLength() const {
  int n = getSize();
  float dis = m_points[n-1].getDistance(m_points[0]);
  // float x1 = m_points.getPointAt[0].getX();
  // float y1 = m_points.getPointAt[0].getY();
  for(int i = 1; i < n; i++){
    dis += m_points[i-1].getDistance(m_points[i]);
    // float x2 = m_points.getPointAt[i].getX();
    // float y2 = m_points.getPointAt[i].getY();
    // dis += pow( ((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)),0.5);
    // x1 = x2;
    // y1 = y2;
  }
  // x1 = m_points.getPointAt[0].getX();
  // y1 = m_points.getPointAt[0].getY();
  // dis += pow( ((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)),0.5);
  return dis;
}
