#pragma once

#include <vector>

#include <string>
#include <memory>

class Input 
{
public:
    Input() = default;

    void Build(const std::string& name, const Input* parent = nullptr) const;

    template<typename T>
    T Get(const std::string& key) {
//        printf("Input::Get key\n");
        T value;
        pStore_->Get(key, value);
        return std::move(value);
    }

    template<typename T, typename... Args>
    T Get(const Args&... args) {
//        printf("Input::Get args...\n");
        T value;
        std::vector<std::string> vecKey {args...};
        if (pStore_.get() == nullptr) {
            printf("store is null\n");
        }
        pStore_->Get(vecKey, value);
        return std::move(value);
    }

    class Store {
    public:
        virtual ~Store() = default;

        virtual void Get(const std::string& key, int& value) = 0;

        virtual void Get(const std::string& key, std::string& value) = 0;

        virtual void Get(const std::vector<std::string>& vecKey, int& value) = 0;

        virtual void Get(const std::vector<std::string>& vecKey, std::string& value) = 0;
    };

private:
    mutable std::unique_ptr<Store> pStore_;
};

