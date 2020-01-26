#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <string>
#include <vector>

class Parameters
{
public:
    static Parameters * Instance();

    void ClearSymbolPaths();
    void AddSymbolsPath(std::string path);
    void Save();

    std::vector<std::string> symbolsPaths;
    std::string pipeName;

private:
    Parameters();
    void LoadFile();

    static Parameters * _instance;
};

#endif // PARAMETERS_H
