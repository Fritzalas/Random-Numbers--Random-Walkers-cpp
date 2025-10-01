// Compile:
// g++ -std=c++11 test_ranlux.cpp -o r
#include <random>
#include <iostream>
#include <fstream>
using namespace std;

int main(){
  //The object rlx is a Ranlux random number engine:
  ranlux48 rlx;
  //drandom is a distribution that produces uniformly
  //distributed numbers in [0,1)
  uniform_real_distribution<double> drandom;
  //--------------------------------------------------
  //Random numbers starting from the default state:
  cout  << "ranlux: ";
  for(int i=1;i<=5;i++) cout << drandom(rlx) << " ";
  cout  << endl;
  //--------------------------------------------------
  //Seeding by a seed:
  rlx.seed(377493872);
  cout  << "seed  : ";
  for(int i=1;i<=5;i++) cout << drandom(rlx) << " ";
  cout  << endl;
  //--------------------------------------------------
  //Saving the state to a file "seeds":
  ofstream oseed("seeds");
  oseed << rlx << endl;
  cout  << "more  : ";
  for(int i=1;i<=5;i++) cout << drandom(rlx) << " ";
  cout  << endl;
  //--------------------------------------------------
  //Reading an old state from the file seeds:
  ifstream iseed("seeds");
  iseed >> rlx;
  cout  << "same  : ";
  for(int i=1;i<=5;i++) cout << drandom(rlx) << " ";
  cout  << endl;
}//main

