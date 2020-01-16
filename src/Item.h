//#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>

#include "Cursor.h"

using namespace std;

template<typename T>
class ItemTmpl
{
public:
    ItemTmpl() : bDefaultStatus_(true) {}

    ItemTmpl(const T& value, const char* format = nullptr) 
        : value_(value), format_(Format(value, format)), content_(Build(value_)) {}

    void Print() const {
        std::cout << content_;
    }

    operator bool() const {
        return !bDefaultStatus_;
    }

    uint32_t Size() const {
        return content_.size();
    }

private:
    const char* Format(int value, const char* format) {
        if (format == nullptr) {
            return "%d";
        }
        return format;
    }

    const char* Format(const std::string& value, const char* format) {
        if (format == nullptr) {
            return "%s";
        }
        return format;
    }

    std::string Build(int value) const {
        char buf[1024] {};
        snprintf(buf, sizeof(buf), format_, value_);
        return buf;
    }
    
    std::string Build(const std::string& value) const {
        char buf[1024] {};
        snprintf(buf, sizeof(buf), format_, value_.c_str());
        return buf;
    }

private:
    T value_;
    const char* format_ = "%s";
    std::string content_;
    bool bDefaultStatus_ = false;
};

class Item
{
public:
    Item(int value, const char* format = nullptr) 
        : itemInt_(value, format) {}

    Item(const std::string& value, const char* format = nullptr) 
        : itemStr_(value, format) {}

    void Print() const {
        if (itemInt_) { itemInt_.Print(); }
        if (itemStr_) { itemStr_.Print(); }
    }

    uint32_t MaxSize() const { return maxSize_; }
    void SetMaxSize(uint32_t maxSize) { maxSize_ = maxSize; }

    uint32_t Size() const {
       if (itemInt_) { return itemInt_.Size(); } 
       if (itemStr_) { return itemStr_.Size(); } 
       return 0;
    }

private:
    uint32_t maxSize_ {};
    ItemTmpl<int> itemInt_;
    ItemTmpl<std::string> itemStr_;
};

class ItemWrapper
{
public:
    template<typename... Args>
    ItemWrapper(const Item& item, const Args&... items) {
        std::vector<Item> tmpItems {item, items...};
        vecItem_ = std::move(tmpItems);
    }

    template<typename T>
    ItemWrapper(const std::vector<T>& vecVal, const char* format) {
        for (const T& val : vecVal) {
            vecItem_.emplace_back(val, format);
        }
    }

    //~ItemWrapper() { Print(); }

    void Print() const {
        cout << "\033[" << (Cursor::Inst().Get()) << "C";
        cout << "{ ";
        for (int i = 0; i < vecItem_.size(); ++i) {
            const auto& item = vecItem_[i];
            item.Print();
            if (i + 1 < vecItem_.size()) {
                int diff = item.MaxSize() - item.Size();
                if (diff > 0 || item.MaxSize() > 0) {
                    cout << ",";
                    cout << "\033[" << diff + 4 << "C";
//                    cout << "\t";
                } else {
                    cout << ",\t";
                }
            }
        }
        cout << " }" << endl;
  //      Cursor::Inst() -= 4;
    }

    friend class PrettyPrinter;

private:
    std::vector<Item> vecItem_;
};

class PrettyPrinter
{
public:
    PrettyPrinter& operator +=(const ItemWrapper& wrapper) {
        vecItemWrapper_.push_back(wrapper); 
        return *this;
    }

    void Print() {
        UpdateItemMaxSize();
        for (const auto& wrapper : vecItemWrapper_) {
            wrapper.Print();
        }
    }

private:
    void UpdateItemMaxSize() {
        for (const auto& wrapper : vecItemWrapper_) {
            for (int i = 0; i < wrapper.vecItem_.size(); ++i) {
                const auto& item = wrapper.vecItem_[i];
                uint32_t itemSize = item.Size();
                if (i >= vecItemMaxSize_.size()) {
                    vecItemMaxSize_.push_back(itemSize);
                    continue;
                }
                int maxSize = vecItemMaxSize_[i];
                if (itemSize > maxSize) {
                    maxSize = itemSize;
                }
                vecItemMaxSize_[i] = maxSize;
            }
            
        }

        for (auto& wrapper : vecItemWrapper_) {
            for (int i = 0; i < wrapper.vecItem_.size(); ++i) {
                Item& item = wrapper.vecItem_[i];
                uint32_t maxSize = vecItemMaxSize_[i];
                item.SetMaxSize(maxSize);
            }
        }
    }
private:
    std::vector<ItemWrapper> vecItemWrapper_;
    std::vector<uint32_t> vecItemMaxSize_;
};
