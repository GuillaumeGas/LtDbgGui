#include "parameters.h"

const std::string DEFAULT_PIPE_NAME    = "\\\\.\\pipe\\ltdbgpipe";
const std::string DEFAULT_SYMBOLS_PATH = "C:\\Users\\Guillaume\\Documents\\Visual Studio 2017\\Projects\\LtMicros\\LtMicros\\iso\\boot\\ltmicros.img";

Parameters * Parameters::_instance = nullptr;

Parameters::Parameters()
{

}

Parameters * Parameters::Instance()
{
    if (_instance == nullptr)
    {
        _instance = new Parameters();
        _instance->symbolsPath = DEFAULT_SYMBOLS_PATH;
        _instance->pipeName = DEFAULT_PIPE_NAME;
    }

    return _instance;
}
