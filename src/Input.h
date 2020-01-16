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
        decltype(Convert(T{})) value;
        std::vector<std::string> vecKey {args...};
        if (pStore_.get() == nullptr) {
            printf("store is null\n");
        }
        pStore_->Get(vecKey, value);
        return std::move(value);
    }

    template<typename T, typename... Args>
    std::vector<T> Array(const Args&... args) {
//        printf("Input::Get args...\n");
        std::vector<T> value;
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

        virtual void Get(const std::string& key, uint64_t& value) = 0;

        virtual void Get(const std::string& key, std::string& value) = 0;

        virtual void Get(const std::vector<std::string>& vecKey, uint64_t& value) = 0;

        virtual void Get(const std::vector<std::string>& vecKey, std::string& value) = 0;

        virtual void Get(const std::string& key, std::vector<uint64_t>& value) = 0;

        virtual void Get(const std::string& key, std::vector<std::string>& value) = 0;

        virtual void Get(const std::vector<std::string>& vecKey, std::vector<uint64_t>& value) = 0;

        virtual void Get(const std::vector<std::string>& vecKey, std::vector<std::string>& value) = 0;

    };

private:
    uint64_t Convert(int val) { return val; }
    std::string Convert(const std::string& val) { return std::move(val); }

private:
    mutable std::unique_ptr<Store> pStore_;
};

