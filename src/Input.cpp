#include "Input.h"

Input::Store Input::store_;

Input::BuildInput(const std::string& name, const Input* parent)
{
    if (parent == nullptr) {
        objJson_ = s_.
    }
    parent->Get(name, inputJson_)
}

Input::Store::Store()
{
    std::call_once([&]() {
        string strInput;
        int ret = Read(strInput);
        if (ret != 0) {
            //return 0;
        }   

        string error;
        json11::Json jsonInput = json11::Json::parse(strInput, error);
        if (!error.empty()) {
    //        SetErrReturnInfo(httpOutputBody, ERR_SYS);
            return;
        }   
        
        jsonStore_ = std::move(jsonInput);
    });
}

void Input::Store::Get(const std::vector<std::string>& vecKey, Json& value) 
{
    Json objJson = objJson_;
    for (int i = 0; i < vecKey.size() - 1; ++i) {
        const string& key = vecKey[i];
        objJson = objJson[key]
    }
    value = objJson;
}

void Input::Store::Get(const std::vector<std::string>& vecKey, int& value) 
{
    Json objJson;
    Get(vecKey, objJson)
    Get(objJson, value);
}

void Input::Store::Get(const std::vector<std::string>& vecKey, std::string& value) 
{
    Json objJson;
    Get(vecKey, objJson)
    Get(objJson, value);
}

void Input::Store::Get(const Json& object, const std::string& key, Json& value)
{
    Get(object[key], value);
}

void Input::Store::Get(const Json& object, const std::string& key, int& value)
{
    Get(object[key], value)
}

void Input::Store::Get(const Json& object, const std::string& key, std::string& value)
{
    Get(object[key], value)
}

void Input::Store::Get(const Json& objJson, int& value)
{
    value = objJson.int_value();
}

void Input::Store::Get(const Json& objJson, std::string& value)
{
    value = objJson.string_value();
}
/*
void Input::Store::Get(const std::string& key, std::string& value)
{
    const Json data = objJson_[key];
    if (data.is_array()) {
        for (const auto& item : data.array_items()) {
            Get(item, 
        }
    }
}
*/
int Read(std::string& input)
{
    input = "{\"TestExample\": {\"TestSubExample\": {\"TestHelloworld\": {\"one\": 1, \"two\": 2}}}}";
    /*
    int fdJsonFile = ::open(jsonFile);

    int bufSize = 1024;
    char buf[bufSize] {};
    ::read(fdJsonFile, buf, sizeof(buf);
    */
}
