// Compile with:
// g++  -Wformat=0 -std=c++11 mixmax.cpp example_checkpointing.cpp -o mxmx
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
using namespace std;

#include "mixmax.hpp"

int main(int argc, char** argv){
  int nrand = 10000;
  mixmax_engine mxmx(0,0,0,1);
  if(argc >= 2) nrand = atoi(argv[1]);
  //mxmx.print_state();
  mxmx.seed(42347987324);
  cout << "mixmax : "; for(int i=1;i<=5;i++) cout << mxmx.get_next_float() << " ";cout << endl;
  //Standard distributions:
  uniform_real_distribution<double> drandom;
  normal_distribution      <double> gaussran; //gaussran(0.0,1.0/sqrt(2.0));
  cout << "uniform: ";for(int i=1;i<=5;i++) cout << drandom(mxmx) << " ";cout << endl;
  mxmx.print_state("mixmax.seeds.0"); //save state in a file
  cout << "more   : ";for(int i=1;i<=5;i++) cout << drandom(mxmx) << " ";cout << endl;
  mxmx.read_state("mixmax.seeds.0");
  cout << "same?  : ";for(int i=1;i<=5;i++) cout << drandom(mxmx) << " ";cout << endl;
  ofstream myfile("mixmax.seeds.1");
  mxmx.print_state(myfile); myfile.close();
  cout << "more   : ";for(int i=1;i<=5;i++) cout << drandom(mxmx) << " ";cout << endl;
  ifstream ifile("mixmax.seeds.1");
  mxmx.read_state(ifile);ifile.close();
  cout << "same?  : ";for(int i=1;i<=5;i++) cout << drandom(mxmx) << " ";cout << endl;
  myfile.open("mixmax.seeds.2");
  myfile << mxmx << endl;myfile.close();
  cout << "more   : ";for(int i=1;i<=5;i++) cout << drandom(mxmx) << " ";cout << endl;
  ifile.open("mixmax.seeds.2");
  ifile >> mxmx; ifile.close();
  cout << "same?  : ";for(int i=1;i<=5;i++) cout << drandom(mxmx) << " ";cout << endl;
  // generate distributions for study:
  myfile.open("mixmax.dat");myfile.precision(17);
  for(int i=0;i<nrand;i++)
    myfile << drandom(mxmx) << " " << gaussran(mxmx) << '\n';
  myfile.close();
}
