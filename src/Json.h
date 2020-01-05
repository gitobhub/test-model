#pragma once

#include "json11.hpp"

#include "Input.h"

//namespace model {

class Json : public Input::Store
{
public:
    class Launcher;

public:
    Json(const std::string& name, const Input::Store* root);

    void Get(const std::string& key, int& value) override;

    void Get(const std::string& key, std::string& value) override;

    void Get(const std::vector<std::string>& vecKey, int& value) override;

    void Get(const std::vector<std::string>& vecKey, std::string& value) override;

private:
    const json11::Json& Build(const Input::Store* root);

    const json11::Json& Get(const std::string& key) const;

    const json11::Json& Get(const std::vector<std::string>& vecKey) const;

    void Get(const json11::Json& json, int& value);

    void Get(const json11::Json& json, std::string& value);
 
private:
    std::string name_;
    const json11::Json& root_;

};

class Json::Launcher 
{
public: 
    static Launcher* Inst() {
        static Launcher instance;
        return &instance;
    }

    const json11::Json& All() { return all_; }

private:
    Launcher();

    int Read(std::string& strJson);

private:
    json11::Json all_;
};

//} // namespace
