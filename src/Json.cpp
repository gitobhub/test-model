#include "json11.hpp"

#include "Json.h"

#include <iostream>

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
    //std::cout << all_["TestExample"]["TestSubExample"]["TestHelloworld"]["one"].int_value() << std::endl;
}

int Json::Launcher::Read(std::string& strJson)
{
    strJson = "{\"TestExample\": {\"TestSubExample\": {\"TestHelloworld\": {\"one\": 1, \"two\": 2, \"three\": { \"value\": 3}}}}}";
    return 0;
}

Json::Json(const std::string& name, const Input::Store* root) 
    : name_(name), root_(Build(root)) {}

void Json::Get(const std::string& key, int& value)
{
    //printf("%s\n", __func__);
    const json11::Json& json = Get(key);
    Get(json, value);
}

void Json::Get(const std::string& key, std::string& value)
{
    const json11::Json& json = Get(key);
    Get(json, value);
}

void Json::Get(const std::vector<std::string>& vecKey, int& value) 
{
    const json11::Json& json = Get(vecKey);
    Get(json, value);
}

void Json::Get(const std::vector<std::string>& vecKey, std::string& value) 
{
    const json11::Json& json = Get(vecKey);
    Get(json, value);
}

const json11::Json& Json::Build(const Input::Store* root)
{
    if (root == nullptr) {
        const json11::Json& all = Json::Launcher::Inst()->All();
        const json11::Json& json = all[name_];
        //std::cout << all["TestExample"]["TestSubExample"]["TestHelloworld"]["one"].int_value() << std::endl;
        //std::cout << json["TestSubExample"]["TestHelloworld"]["one"].int_value() << std::endl;
        return json;
    }
    return (dynamic_cast<const Json*>(root))->Get(name_);
}

const json11::Json& Json::Get(const std::string& key) const
{
    //printf("%s\n", __func__);
    const json11::Json& json = root_[key];
    //std::cout << key << ": " << json["TestHelloworld"]["one"].int_value() << std::endl;
    //std::cout << key << ": " << json["one"].int_value() << std::endl;
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

void Json::Get(const json11::Json& json, int& value)
{
    //printf("is null %d\n", json.is_null());
    //printf("is int  %d\n", json.is_number());
    //printf("is bool  %d\n", json.is_bool());
    //printf("is str  %d\n", json.is_string());
    //printf("is arr  %d\n", json.is_array());
    //printf("is obj  %d\n", json.is_object());
    value = json.int_value();
    //printf("int %d", value);
}

void Json::Get(const json11::Json& json, std::string& value)
{
    value = json.string_value();
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
