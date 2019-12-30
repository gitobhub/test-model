#include "Input.h"

void Input::Init()
{
    ReadConfig();

    std::string strJsonError;
    json11::Json input = json11::Json::parse(strConfContent, strJsonError);

}
