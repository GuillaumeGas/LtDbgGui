#include "parameters.h"

#include <fstream>

using namespace std;

const std::string DEFAULT_PIPE_NAME    = "\\\\.\\pipe\\ltdbgpipe";
const std::string FILE_NAME = "ltdbg.conf";

Parameters * Parameters::_instance = nullptr;

Parameters::Parameters()
{

}

Parameters * Parameters::Instance()
{
    if (_instance == nullptr)
    {
        _instance = new Parameters();
        _instance->pipeName = DEFAULT_PIPE_NAME;

        _instance->LoadFile();
    }

    return _instance;
}

void Parameters::LoadFile()
{
    ifstream file(FILE_NAME);
    string line;

    while (getline(file, line))
    {
        symbolsPaths.push_back(line);
    }

    file.close();
}

void Parameters::ClearSymbolPaths()
{
    symbolsPaths.clear();
}

void Parameters::AddSymbolsPath(std::string path)
{
    symbolsPaths.push_back(path);
}

void Parameters::Save()
{
    ofstream file(FILE_NAME);
    file.clear();

    for (const string & it: symbolsPaths)
    {
        file << it << endl;
    }

    file.close();
}
