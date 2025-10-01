// Compile:
// g++ urandom.cpp -o u ; ./u
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int seedby_urandom();
int seedby_pid    ();
int main(){
  cout << seedby_urandom() << endl;
  cout << seedby_pid    () << endl;
}

// Use /dev/urandom for more randomness.
#include <unistd.h>
#include <fcntl.h>
int seedby_urandom(){
  int ur,fd;
  fd = open("/dev/urandom", O_RDONLY);
  read (fd,&ur,sizeof(int));
  close(fd);
  return (ur>0)?ur:-ur;
}
// Seed using the time of running and the
// process id (pid) in the system
#include <sys/types.h>
#include <sys/stat.h>
int seedby_pid(){
  int pid,sd;
  sd   = (int) time( (time_t) 0);
  pid  = (int) getpid(); //Process ID number
  sd   = sd ^ (pid + (pid << 15));
  return (sd>0)?sd:-sd;
}
