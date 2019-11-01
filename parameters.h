#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <string>

class Parameters
{
public:
    static Parameters * Instance();

    std::string symbolsPath;
    std::string pipeName;

private:
    Parameters();

    static Parameters * _instance;
};

#endif // PARAMETERS_H
