// Compile with:
// g++ -std=c++11 test_mixmax.cpp MIXMAX/mixmax.cpp -o mxmx
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
using namespace std;

#include "MIXMAX/mixmax.hpp"

int main(){

  //The object mxmx is a MIXMAX random number engine:
  mixmax_engine mxmx(0,0,0,1);
  //The object drandom is a uniform distribution:
  uniform_real_distribution<double> drandom;
  //--------------------------------------------------
  //Random numbers after seeding with a chosen seed:
  mxmx.seed(1234);
  cout   << "mixmax: ";
  for(int i=1;i<=5;i++) cout << drandom(mxmx) << " ";
  cout   << endl;
  //--------------------------------------------------
  //Saving the state to a file "seeds":
  ofstream oseeds("seeds");
  oseeds << mxmx << endl;oseeds.close();
  cout   << "more  : ";
  for(int i=1;i<=5;i++) cout << drandom(mxmx) << " ";
  cout   << endl;
  //--------------------------------------------------
  //Reading an old state from the file seeds:
  ifstream iseeds("seeds");
  iseeds >> mxmx; iseeds.close();
  cout   << "same  : ";
  for(int i=1;i<=5;i++) cout << drandom(mxmx) << " ";
  cout   << endl;
  
}//main()

