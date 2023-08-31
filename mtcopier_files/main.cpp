/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"
#include "writer.h"
#include <cstdlib>
/**
 * these need to be global variables as you'll need handle cleaning them up in
 *cleanup which will automatically be called on program exit
 **/
reader *readers;
writer *writers;
bool timingEnabled = false;

void cleanup()
{
    delete[] readers;
    delete[] writers;
}

int main(int argc, char **argv)
{
    atexit(cleanup);

    if (argc < 4)
    {
        std::cerr << "Usage: " << argv[0] << " <num threads> <input file> <output file> <optional -t>"
                  << std::endl;
        return EXIT_FAILURE;
    }

    if (argc == 5 && std::string(argv[4]) == "-t")
    {
        timingEnabled = true;
    }

    int numThreads = std::stoi(argv[1]);
    std::string input_file(argv[2]);
    std::string output_file(argv[3]);

    reader::init(input_file);
    writer::init(output_file);

    readers = new reader[numThreads];
    writers = new writer[numThreads];

    for (int i = 0; i < numThreads; ++i)
    {
        readers[i].run();
        writers[i].run();
    }

    for (int i = 0; i < numThreads; ++i)
    {
        readers[i].join();
        writers[i].join();
    }

    reader::displayTotalTime();

    return EXIT_SUCCESS;
}
