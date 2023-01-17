#include "tspsolver.hpp"

TSPSolver::TSPSolver(ListOfPoints &list) { // do I need to return it here?
  m_list = list;
}

void TSPSolver::solve() {
  if (m_list.getSize() == 0) {return;}
  if (m_list.getSize() <= 3) {
    m_solution.ListOfPoints::operator=(m_list);
    return;
  }
  // above are special cases
  for(int k=0; k<3; k++){
    m_solution.addPoint( m_list.getPointAt(k) );
  }
  
  TSPCycle temp;
  // float temp_length; //temp to record lengths of each options of cycle each time adding a new point in.
  float min_length; 
  string target_name; 
  
  for(int i = 3; i<m_list.getSize(); i++){
    min_length = 100000000.;
    
    for(int j = 0; j<m_solution.getSize(); j++){
      // cout << "j = " << j << endl;
      temp = m_solution;
      //temp.printList();
      // cout << "vv" << endl;
      temp.addAfter(m_list.getPointAt(i), temp.getPointAt(j).getName());
      //temp.printList();
      
      // cout << temp.getLength() << "vs" << min_length << endl;
      // cout << "---------" << endl;     
      
      if (temp.getLength()<min_length){ 
        min_length = temp.getLength();
        target_name = temp.getPointAt(j).getName();// store name
      }
    }
    //insert the new point to m_solution at the min_length position
    m_solution.addAfter(m_list.getPointAt(i),target_name);
  }
}

TSPCycle& TSPSolver::getSolution() {
  return m_solution;
}

