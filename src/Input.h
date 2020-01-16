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
        T value;
        pStore_->Get(key, value);
        return std::move(value);
    }

    template<typename T, typename... Args>
    T Get(const Args&... args) {
        auto value = Convert(T{});
        std::vector<std::string> vecKey {args...};
        if (pStore_.get() == nullptr) {
            printf("store is null\n");
        }
        pStore_->Get(vecKey, value);
        return std::move(value);
    }

    template<typename T, typename... Args>
    std::vector<T> Array(const Args&... args) {
        std::vector<decltype(Convert(T{}))> value;
        std::vector<std::string> vecKey {args...};
        if (pStore_.get() == nullptr) {
            printf("store is null\n");
        }
        pStore_->Get(vecKey, value);

        std::vector<T> vecRet(value.size());
        for (int i = 0; i < value.size(); ++i) {
            vecRet[i] = std::move(value[i]);
        }
        return std::move(vecRet);
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

