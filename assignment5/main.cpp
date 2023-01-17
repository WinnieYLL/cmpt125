#include <iostream>
#include <cstdlib>
#include <math.h>
#include <algorithm>

#define PI 3.14159265

#include "point.hpp"
#include "listofpoints.hpp"
#include "tspsolver.hpp"
#include "tspcycle.hpp"

using namespace std;

void testPoint() {
  Point origin(0,0,"ORIGIN");
  cout << "--print using printPoint():" << endl;
  origin.printPoint();
  cout << "--print using toString():" << endl;
  cout << origin.toString() << endl;
  cout << "--print using << operator:" << endl;
  cout << origin << endl;
  

  Point q(3,4,"Q");
  //distance should be 5
  cout << "distance between ORIGIN and Q is " << q.getDistance(origin) << endl;

}

void test_getDistance() {
  Point x(0,0,"x");
  Point y(3,4,"y");
  cout << x.getDistance(y) << endl;
  
  Point a(-2,-1,"a");
  Point b(3,11,"b");
  cout << b.getDistance(a) << endl;  
}

void test_getLength() {
  TSPCycle cycle1;
  Point a(0,0,"a");
  Point b(0,5,"b");  
  Point c(-12,0,"c");    
  cycle1.addPoint(a);
  cycle1.addPoint(b);
  cycle1.addPoint(c);  
  
  cout << cycle1.getLength() << endl;

}

void test_addAfter(){
  ListOfPoints notcycle1;
  Point a(0,0,"a");
  Point b(0,5,"b");  
  Point c(-12,0,"c");    
  notcycle1.addPoint(a);
  notcycle1.addPoint(b);
  notcycle1.addPoint(c);    
  
  Point d(3,3,"d");
  notcycle1.addAfter(d, "a");
  notcycle1.printList();
  
  cout << endl;
  
  Point e(5,3,"e");
  notcycle1.addAfter(e, "c");
  notcycle1.printList();  
  
}
// gets a list of points and runs the solver on this list
// used in test1 and test2 below
void testSolver(ListOfPoints &input) {
  cout << "---run the solver---" << endl;
  TSPSolver solver(input);
  solver.solve();
  TSPCycle solution = solver.getSolution();


  cout << "Solution found is: " << endl;
  solution.printList();
  cout << "the length of the solution is: " << solution.getLength() << endl;
}

void test1() {
  Point p[4] = {Point(2,2,"A"),
                Point(2,6,"B"),
                Point(5,6,"C"),
                Point(5,9,"D")};

  cout << "Creating a list of points:" << endl;
  ListOfPoints inputTSP;
  for (int i=0;i<4;i++)
    inputTSP.addPoint(p[i]);
  
  cout << "Printing the list:" << endl;
  inputTSP.printList();  
  inputTSP.draw();  

  testSolver(inputTSP);
}


void test2() {
  ListOfPoints inputTSP;
  Point p(0,0,"A");
  cout << "Creating a list of points:" << endl;

  for (int i=0;i<10;i++) {
    string s;
    s = 'A'+i;
    p = Point(i,0,s);
    inputTSP.addPoint(p);
  }
  
  cout << "Printing the list:" << endl;
  inputTSP.printList();  
  inputTSP.draw();  

  testSolver(inputTSP);
}


void test3() {
  ListOfPoints inputTSP;
  Point p(0,0,"O");
  cout << "Creating a list of points:" << endl;

  for (int i=0;i<50;i++) {
    p = Point(rand() % 1000, rand() % 1000,"P"+to_string(i));
    inputTSP.addPoint(p);
  }
  // some coordinates values more than 20, so we do not use draw here

  testSolver(inputTSP);
}

void test4() {
  ListOfPoints inputTSP;
  int n = 100;
  vector<double> theta;
  Point p(0,0,"O");
  
  for (int i = 0; i < n; i++) {
    theta.push_back(2*i*PI/n);
  }
  
  random_shuffle(theta.begin()+3, theta.end());
  
  cout << "Creating a list of points:" << endl;  
  for (int i = 0; i < n; i++) {
    p = Point(100*cos(theta[i]), 100*sin(theta[i]), "P"+to_string(i));
    inputTSP.addPoint(p);  
  }

  testSolver(inputTSP); // length should be about 100*2*PI
}


int main() {

  cout << "****Test point**" << endl;
  testPoint();
  cout << "****End of test point**" << endl << endl;

  cout << "****Test getDistance()**" << endl;
  test_getDistance();
  cout << "****End of test getDistance()**" << endl << endl;
  
  cout << "****Test getLength()**" << endl;
  test_getLength();
  cout << "****End of test getLength()**" << endl << endl;

  cout << "****Test addAfter()**" << endl;
  test_addAfter();
  cout << "****End of test addAfter()**" << endl << endl;  
 
  
  cout << "****test1**:" << endl;
  test1();
  cout << "****end of test1**:" << endl << endl;
 
  cout << "****test2**:" << endl;
  test2();
  cout << "****end of test2**:" << endl << endl;

 
 cout << "****test3**:" << endl;
 test3();
 cout << "****end of test3**:" << endl << endl;

  cout << "****test4**:" << endl;
  test4();
  cout << "****end of test4**:" << endl << endl;
  return 0;
}
