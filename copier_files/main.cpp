/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"
#include "writer.h"
#include <cstdlib>
/* global variables if needed go here */
int main(int argc, char **argv)
{
    /* check command line arguments */
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>" << std::endl;
        return EXIT_FAILURE;
    }

    /* load the file and copy it to the destination */
    writer myWriter(argv[2]);
    reader myReader(argv[1], myWriter);

    myReader.run();

    return EXIT_SUCCESS;
}
