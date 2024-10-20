#include <include.h>

std::vector<std::string> argvToVector(int argc, char** argv)
{
    std::vector<std::string> argvVector;

    for (int i = 1; i < argc; i++)
    {
        argvVector.push_back(argv[i]);
    }

    return argvVector;
}