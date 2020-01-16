#include <fcntl.h>
#include <unistd.h>

#include "json11.hpp"

#include "Json.h"

using namespace std;

Json::Launcher::Launcher()
{
    string strJson;
    int ret = Read(strJson);
    if (ret != 0) {
        //return 0;
    }   

    string error;
    json11::Json json = json11::Json::parse(strJson, error);
    if (!error.empty()) {
//        SetErrReturnInfo(httpOutputBody, ERR_SYS);
        return;
    }   
    
//    all_ = std::move(json);
    all_ = json;
}

int Json::Launcher::Read(std::string& strJson)
{
    //strJson = "{\"TestExample\": {\"TestSubExample\": {\"TestHelloworld\": {\"one\": 1, \"two\": 2, \"three\": { \"value\": 3}}}}}";

    int fd = ::open(jsonFile_.c_str(), O_RDONLY);
    if (fd == -1) {
        return -1;
    }

    char buf[4096] {};
    int ret = ::read(fd, buf, sizeof(buf));
    if (ret == -1) {
        return -1;
    }

    strJson = buf;

    return 0;
}

Json::Json(const std::string& name, const Input::Store* root) 
    : name_(name), root_(Build(root)) {}

void Json::Get(const std::string& key, uint64_t& value)
{
    const json11::Json& json = Get(key);
    Get(json, value);
}

void Json::Get(const std::string& key, std::string& value)
{
    const json11::Json& json = Get(key);
    Get(json, value);
}

void Json::Get(const std::vector<std::string>& vecKey, uint64_t& value) 
{
    const json11::Json& json = Get(vecKey);
    Get(json, value);
}

void Json::Get(const std::vector<std::string>& vecKey, std::string& value) 
{
    const json11::Json& json = Get(vecKey);
    Get(json, value);
}

void Json::Get(const std::string& key, std::vector<uint64_t>& value)
{
    const json11::Json& json = Get(key);
    Get(json, value);
}

void Json::Get(const std::string& key, std::vector<std::string>& value)
{
    const json11::Json& json = Get(key);
    Get(json, value);
}

void Json::Get(const std::vector<std::string>& vecKey, std::vector<uint64_t>& value) 
{
    const json11::Json& json = Get(vecKey);
    Get(json, value);
}

void Json::Get(const std::vector<std::string>& vecKey, std::vector<std::string>& value) 
{
    const json11::Json& json = Get(vecKey);
    Get(json, value);
}

const json11::Json& Json::Build(const Input::Store* root)
{
    if (root == nullptr) {
        const json11::Json& all = Json::Launcher::Inst()->All();
        const json11::Json& json = all[name_];
        return json;
    }
    return (dynamic_cast<const Json*>(root))->Get(name_);
}

const json11::Json& Json::Get(const std::string& key) const
{
    const json11::Json& json = root_[key];
    return json;
}

const json11::Json& Json::Get(const std::vector<std::string>& vecKey) const
{
    const json11::Json* pJson = &root_;
    for (int i = 0; i < vecKey.size(); ++i) {
        const string& key = vecKey[i];
        pJson = &((*pJson)[key]);
    }
    return *pJson;
}

void Json::Get(const json11::Json& json, uint64_t& value)
{
    value = json.number_value();
}

void Json::Get(const json11::Json& json, std::string& value)
{
    value = json.string_value();
}

void Json::Get(const json11::Json& json, std::vector<uint64_t>& value)
{
    const auto& items = json.array_items();
    for (const auto& item : items) {
        uint64_t iVal {};
        Get(item, iVal);
        value.push_back(iVal);
    }
}

void Json::Get(const json11::Json& json, std::vector<std::string>& value)
{
    const auto& items = json.array_items();
    for (const auto& item : items) {
        string strVal;
        Get(item, strVal);
        value.push_back(strVal);
    }
}

/*
void Json::Get(const std::string& key, std::string& value)
{
    const Json data = objJson_[key];
    if (data.is_array()) {
        for (const auto& item : data.array_items()) {
            Get(item, 
        }
    }
}
*/
