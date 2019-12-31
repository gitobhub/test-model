#pragma once

#include <string>

class Input 
{
public:
    Input() = default;

    void BuildInput(const std::string& name, const Input* parent = nullptr);

    template<typename T>
    T Get(const std::string& key) {
        T value;
        store_.Get(key, value);
        return std::move(value);
    }

    template<typename T, typename... Args>
     T Get(const Args&... args) {
         T value;
         std::vector<std::string> vecKey {args...};
         store_.Get(vecKey, value);
         return std::move(value);
     }

    class Store
    {
    public:
        Store();

        void Get(const std::string& key, int& value);

        void Get(const std::string& key, std::string& value);

        void Get(const std::vector<std::string>& vecKey, Json& value);

        void Get(const std::vector<std::string>& vecKey, int& value);

        void Get(const std::vector<std::string>& vecKey, std::string& value);

        void Get(const Json& objJson, int& value);

        void Get(const Json& objJson, std::string& value);

//        int Read(std::string& input);
    private:
        json11::Json objJson_;
        static json11::Json allObjJson_;
    };

priavte:
    Store store_;
};

