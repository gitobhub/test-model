//#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Cursor.h"

using namespace std;

template<typename T>
class ItemTmpl
{
public:
    ItemTmpl() : defaultStatus_(true) {}

    ItemTmpl(const T& value, const char* format = nullptr) 
        : value_(value) {
        if (format == nullptr) {
            format_ = DefaultFormat(value, format);
        } else {
            format_ = format;
        }
    }

    void Print() const {
        Print(value_);
    }

    operator bool() const {
        return !defaultStatus_;
    }

private:
    const char* DefaultFormat(int value, const char* format) {
        return "%d";
    }

    const char* DefaultFormat(const std::string& value, const char* format) {
        return "%s";
    }

    void Print(int value) const {
        printf(format_, value_);
    }
    
    void Print(const std::string& value) const {
        printf(format_, value_.c_str());
    }

private:
    T value_;
    const char* format_ = "%s";
    bool defaultStatus_ = false;
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

private:
    ItemTmpl<int> itemInt_;
    ItemTmpl<std::string> itemStr_;
};

class ItemWrapper
{
public:
    template<typename... Args>
    ItemWrapper(const Args&... items) {
        std::vector<Item> tmpItems {items...};
        vecItem_ = std::move(tmpItems);
    }

    //~ItemWrapper() { Print(); }

    void Print() {
        cout << "\033[" << (Cursor::Inst().Get()) << "C";
        cout << "{ ";
        for (int i = 0; i < vecItem_.size(); ++i) {
            vecItem_[i].Print();
            if (i + 1 < vecItem_.size()) {
                cout << ",\t";
            }
        }
        cout << " }" << endl;
  //      Cursor::Inst() -= 4;
    }

private:
    std::vector<Item> vecItem_;
};
