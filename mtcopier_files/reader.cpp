/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"

#include "writer.h"

#include <pthread.h>

#include <ctime>

/**
 * implement the functions needed for this class
 **/
std::ifstream reader::in;

bool reader::readingComplete = false;
extern bool timingEnabled;

pthread_mutex_t reader::readLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t reader::readCondLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t reader::readCond = PTHREAD_COND_INITIALIZER;

clock_t reader::totalReadDuration = 0;
clock_t reader::totalLockDuration = 0;
pthread_mutex_t reader::timingLock = PTHREAD_MUTEX_INITIALIZER;

void reader::init(const std::string &name)
{
    in.open(name);
}

void reader::run()
{
    pthread_create(&readThread, nullptr, runner, nullptr);
}

void *reader::runner(void *arg)
{
    // For timing
    clock_t start, end, lockStart, lockEnd;
    clock_t readDuration = 0, lockDuration = 0;

    std::string line;
    while (true)
    {
        // For timing
        lockStart = clock();
        if (lockStart == (clock_t)-1)
        {
            std::cerr << "Lock Timing Failed in lockStart\n";
        }

        pthread_mutex_lock(&readLock);

        lockEnd = clock();
        if (lockEnd == (clock_t)-1)
        {
            std::cerr << "Lock Timing Failed in lockEnd\n";
        }
        lockDuration += (lockEnd - lockStart);
        pthread_mutex_lock(&timingLock);
        totalLockDuration += lockDuration;
        pthread_mutex_unlock(&timingLock);

        start = clock();
        if (start == (clock_t)-1)
        {
            std::cerr << "Read Timing Failed in start\n";
        }

        if (!std::getline(in, line))
        {
            // For timing
            end = clock();
            if (end == (clock_t)-1)
            {
                std::cerr << "Read Timing Failed in end\n";
            }
            readDuration += (end - start);
            pthread_mutex_lock(&timingLock);
            totalReadDuration += readDuration;
            pthread_mutex_unlock(&timingLock);
            // End timing

            pthread_mutex_lock(&readCondLock);
            readingComplete = true;
            pthread_cond_broadcast(&readCond);
            pthread_mutex_unlock(&readCondLock);
            pthread_mutex_unlock(&readLock);
            return nullptr;
        }
        else
        {
            end = clock();
            if (end == (clock_t)-1)
            {
                std::cerr << "Read Timing Failed in end\n";
            }
            readDuration += (end - start);
            pthread_mutex_lock(&timingLock);
            totalReadDuration += readDuration;
            pthread_mutex_unlock(&timingLock);
        }
        writer::append(line);
        pthread_mutex_unlock(&readLock);
    }
    return nullptr;
}

void reader::join()
{
    pthread_join(readThread, nullptr);
}

void reader::waitReadingComplete()
{
    pthread_mutex_lock(&readCondLock);
    while (!readingComplete)
    {
        pthread_cond_wait(&readCond, &readCondLock);
    }
    pthread_mutex_unlock(&readCondLock);
}

void reader::displayTotalTime()
{
    if (timingEnabled)
    {
        int totalReadTime = (double)totalReadDuration / (int)CLOCKS_PER_SEC;
        int totalLockTime = (double)totalLockDuration / (int)CLOCKS_PER_SEC;
        std::cout << "Reader: Total time spent reading by all threads: " << totalReadTime << " seconds" << std::endl;
        std::cout << "Reader: Total time spent locking by all threads: " << totalLockTime << " seconds" << std::endl;
    }
}
