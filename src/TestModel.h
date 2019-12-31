#pragma once

#include <cxxabi.h>

#include "Item.h"
#include "Input.h"

using namespace std;

class TestModel : Input {
public:
    template<typename T>
    TestModel(const T& t, Parent parent = nullptr) {
        string name = abi::__cxa_demangle(typeid(t).name(), nullptr, nullptr, nullptr);

        BuildInput(name, parent);

        int indent = (Cursor::Inst().Get() == 0 ? 0 : Cursor::Inst().Get());
        cout << "\033[" << indent << "C";
        cout << name << " {" << endl;
        Cursor::Inst() += 4;
    }
    ~TestModel() {
        cout << "\033[" << (Cursor::Inst() -= 4) << "C";
        cout << "}" << endl;
    }

    template<typename... Args>
    void Println(Args... args) {
        printf(args...);
        cout << endl;
        cout << "\033[1B";
        cout << "\033[" << (Cursor::Inst() += 4) << "C";
    }

    static void SetGlobalContext(void* context) {
        context_ = context;
    }

    void* GetGlobalContext() { return context_; }

private:
    static void* context_;
};

using Parent = const TestModel *;

template<typename... Args>
class TestWrapper {
public:
    TestWrapper() {
//        RunTestModel();
    }
/*
    template<>
     void RunTestModel() {
         get<I>(tupleTestModel_)
     }
*/
private:
    tuple<Args...> tupleTestModel_;
};

