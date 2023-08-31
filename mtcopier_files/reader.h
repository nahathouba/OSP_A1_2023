/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include <pthread.h>

#include <fstream>
#include <iostream>
#include <string>
#ifndef READER
#define READER
class reader
{
public:
  /* this class has a bunch of static (which means shared in a class)
   * because we need to share the state between threads. For example, we
   * are reading from the same file, should have the same locks for all
   * readers, etc.
   **/

  /** initialize the shared data for the class - for example, open the
   * file. There will be other things which you will need to figure out
   * as you complete the assignment.
   **/
  static void init(const std::string &name);

  /**
   * the method that implements the thread. It has to be static as the first
   * implicit argument to all instance methods is 'this' and c functions don't
   * know about classes
   **/
  static void *runner(void *);

  /**
   * does the setup for and launches the threads
   **/
  void run();
  /**
   * there may be other functions you need so declare them.
   **/

  static bool isReadingComplete() { return readingComplete; }
  void join();
  static void waitReadingComplete();
  static void displayTotalTime();

private:
  static std::ifstream in;
  /**
   * There may be other private instance data you need so declare those here.
   **/

  static pthread_mutex_t readLock;
  static bool readingComplete;
  static pthread_cond_t readCond;
  static pthread_mutex_t readCondLock;
  pthread_t readThread;

  // For timing
  static clock_t totalReadDuration;
  static clock_t totalLockDuration;
  static pthread_mutex_t timingLock;
};
#endif