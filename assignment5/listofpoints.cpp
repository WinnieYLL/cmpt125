#include "listofpoints.hpp"


ListOfPoints::ListOfPoints() {
}

void ListOfPoints::addAfter(Point& newPt, string name) {
  for (long unsigned int i = 0; i < m_points.size(); i++){
    if (m_points[i].getName() == name) {
      m_points.insert(m_points.begin()+i+1, newPt);
      return;
    }
  }  
}

void ListOfPoints::addPoint(Point& newPt)  {
   m_points.push_back(newPt);
}

Point& ListOfPoints::getPointAt(unsigned int i) {
  return m_points[i];
}

int ListOfPoints::getSize() const {
  return m_points.size();
}

void ListOfPoints::printList() const {
  int i = 0;
  for (i=0; i < getSize(); i++){
    cout << m_points[i].getName() << ": (" << m_points[i].getX() << "," << m_points[i].getY() << ")" << endl;
  }
}

void ListOfPoints::draw() const {
  int i=0, j=0, k=0;
  int point_here;
  for (j=20; j>=0; j--){
    if (j >= 10) {
      cout << j << " ";
    }
    else {
      cout << " " << j << " ";
    }
    for (i=0; i<=20; i++){
      point_here = 0;
      for (k=0; k<getSize(); k++){
        if (i == m_points[k].getX() && j == m_points[k].getY()){
          cout << m_points[k].getName();
          point_here = 1;
          break;
        }
      }  
      if (!point_here) {
        cout << "-";
      }
    }
    cout << endl;
  }
  
  cout << "   ";
  for (i=0; i<=20; i++){
    cout << i%10;
  }
  cout << endl;

}

    // operator =
ListOfPoints& ListOfPoints::operator=(const ListOfPoints& other) {
  m_points = other.m_points;
  return *this;
}
 
