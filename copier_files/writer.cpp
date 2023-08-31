/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/

#include "writer.h"

/**
 * provide your implementation for the writer functions here
 **/
writer::writer(const std::string &name)
{
    out.open(name);
    if (!out.is_open())
    {
        throw std::runtime_error("Could not open file " + name);
    }
}

void writer::run()
{
    // No implementation needed. Single Threaded program.
}

void writer::append(const std::string &line)
{
    out << line << std::endl;
}
