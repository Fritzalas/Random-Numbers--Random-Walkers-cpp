//===================================================
//Function to produce random numbers distributed
//according to the gaussian distribution
//g(x) = 1/(sigma*sqrt(2*pi))*exp(-x^2/(2*sigma^2))
//===================================================
#include <cmath>
double drandom ();
double gaussran(){
  const  double sigma = 1.0;
  const  double PI2   = 6.28318530717958648;
  static bool   newx  = true;
  static double x;
  double        r,phi;

  if(newx){
    newx =  false;
    r    =  drandom();
    phi  =  drandom()*PI2;
    r    =  sigma*sqrt(-2.0*log(r));
    x    =  r*cos(phi);
    return  r*sin(phi);
  }else{
    newx =  true;
    return x;
  }
}
//===================================================
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
int main(){
  for(int i=1;i<=100000;i++)
  cout << gaussran() << '\n';
}
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
static  int seed = 323412;
double drandom(){
  const int    a = 16807;     //a = 7**5                                                                                                                                                                                                   
  const int    m = 2147483647;//m = a*q+r = 2**31-1                                                                                                                                                                                        
  const int    q = 127773;    //q = [m/a]                                                                                                                                                                                                  
  const int    r = 2836;      //r = m % a                                                                                                                                                                                                  
  const double f = 1.0/m;
  int     p;
  double dr;

 compute:
  p    = seed/q;              //p = [seed/q]                                                                                                                                                                                               
  //seed = a*(seed % q)-r*[seed/q] = (a*seed) % m                                                                                                                                                                                          
  seed = a*(seed-q*p) - r*p;
  if(seed < 0) seed +=m;
  dr=f*(seed-1);
  if(dr <= 0.0 || dr >= 1.0) goto compute;
  return dr;
}

