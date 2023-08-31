/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "writer.h"

#include "reader.h"

/**
 * implement these functions requred for the writer class
 **/

std::ofstream writer::out;
pthread_mutex_t writer::writeLock = PTHREAD_MUTEX_INITIALIZER;
std::deque<std::string> writer::queue;
void writer::init(const std::string &name)
{
    out.open(name);
}

void writer::run()
{
    pthread_create(&writeThread, nullptr, runner, nullptr);
}

void *writer::runner(void *arg)
{
    while (true)
    {
        pthread_mutex_lock(&writeLock);
        /**
        while (queue.empty())
        {
            pthread_mutex_unlock(&writeLock);
            reader::waitReadingComplete();
            pthread_mutex_lock(&writeLock);


            if (reader::isReadingComplete())
            {
                pthread_mutex_unlock(&writeLock);
                return nullptr;
            }

        }
        **/
        if (queue.empty() && !reader::isReadingComplete())
        {
            pthread_mutex_unlock(&writeLock);
            reader::waitReadingComplete();
            continue;
        }

        if (queue.empty() && reader::isReadingComplete())
        {
            pthread_mutex_unlock(&writeLock);
            return nullptr;
        }
        if (!queue.empty())
        {
            std::string line = queue.front();
            out << line << std::endl;
            queue.pop_front();
        }
        pthread_mutex_unlock(&writeLock);
    }

    return nullptr;
}

void writer::append(const std::string &line)
{
    pthread_mutex_lock(&writeLock);
    queue.push_back(line);
    pthread_mutex_unlock(&writeLock);
}

void writer::join()
{
    pthread_join(writeThread, nullptr);
}
