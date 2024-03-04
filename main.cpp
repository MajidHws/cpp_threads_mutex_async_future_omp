#include <iostream>
#include <thread>
#include <mutex>
#include <future>

#ifdef _OPENMP
#include <omp.h>
#endif

using namespace std;

mutex carMutex;

void driveCar(string driverName) {
  // unique_lock<mutex> carLock(carMutex); // here the code code to lock the critical code
  lock_guard<mutex> carLock(carMutex); // this is a short way of locking the code, no need to use the unique_lock.
  
  // this is the start of the critical code 
  cout << driverName << " is driving" << endl; 
  this_thread::sleep_for(chrono::seconds(2));
  cout << driverName << " has done driving" << endl;
  // this is the end of the critical code 
  
  // carLock.unlock(); // here the code code to unlock the critical code
} // lock guard will automatically unlock the code when the function ends 

void threadUsingMutex() {
  thread t1(driveCar, "Majid");
  thread t2(driveCar, "Malick");

  t1.join();
  t2.join();
}

void threadUsingOMP() {
  // to run this function we need to use the -fopenmp flag in the compiler
  #pragma omp parallel
  {
    #pragma omp critical 
    { // this is tell the compiler that this is the critical code and needs to be 
      cout << "printting from thread: "<< omp_get_thread_num() << "\n" << endl;
    }
  }
}

int sequre(int x) {
  return x * x;
}
void threadUsingAsynchronus() {
  
  std::future<int> asyncFunction = std::async(std::launch::deferred, &sequre, 5); // this is the function that we want to run in a thread so we pass its address to the async function usin the & operator, std::launch::deferred is used to tell the compiler that we want to run the function on the same thread that is calling the function.
  
  // std::future<int> asyncFunction = std::async(&sequre, 5); // this is the function that we want to run in a thread so we pass its address to the async function usin the & operator.
  cout << "The result is: " << asyncFunction.get() << endl;
  
}
int main() {
  // threadUsingMutex();
  // threadUsingOMP();
  // threadUsingAsynchronus();
  

  return 0;
}