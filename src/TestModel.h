#pragma once

#include <tuple>
#include <cxxabi.h>
#include <thread>

#include "Item.h"
#include "Input.h"
#include "Output.h"

using namespace std;

template<typename... Args>
class TestModel : public Input, private Output {
public:
    template<typename Derive>
    TestModel(const Derive& derive) {
        //std::this_thread::sleep_for(std::chrono::seconds(1));
        string name = abi::__cxa_demangle(typeid(derive).name(), nullptr, nullptr, nullptr);
        name_ = name.substr(0, name.rfind('*'));

    }

    virtual ~TestModel() {
        Output::Close();
    }
    
    void Run(const Input* root = nullptr) { 
        //printf("run\n"); 

        Output::Open(name_);

        Input::Build(name_, root);

        Work();

        BuildSubModel();
        //printf("contructor end\n");
    };

    virtual void Work() { 
        //printf("work\n"); 
    }

    void Init(const Input* root) const {
        //printf("init\n");
        Input::Build(name_, root);
    }

    void BuildSubModel() {
        //std::this_thread::sleep_for(std::chrono::seconds(1));
        //printf("%s\n", __func__);
        IterBuild();
    };

    template<std::size_t I = 0>
    typename std::enable_if<I < sizeof...(Args)>::type
    IterBuild() {
        //std::this_thread::sleep_for(std::chrono::seconds(1));
        //printf("%s < \n", __func__);
        //printf("1\n");              
        //TestModel& model = const_cast<TestModel&>(std::get<I>(tupleSubModel_));
        auto& model = std::get<I>(tupleSubModel_);
        //printf("%s\n", abi::__cxa_demangle(typeid(model).name(), nullptr, nullptr, nullptr));
        //printf("2\n");              
        model.Run(this);
//        delete &model;

        //printf("name: %s\n", name_.c_str());
        IterBuild<I+1>();
    }

    template<std::size_t I>
    typename std::enable_if<I == sizeof...(Args)>::type
    IterBuild() {
        //std::this_thread::sleep_for(std::chrono::seconds(1));
        //printf("%s == \n", __func__);
    }

//    static void SetGlobalContext(void* context) {
//        context_ = context;
//    }

//    void* GetGlobalContext() { return context_; }

//    template<typename... Args>
//    void Println(Args... args) {
//        //printf(args...);
//        cout << endl;
//        cout << "\033[1B";
//        cout << "\033[" << (Cursor::Inst() += 4) << "C";
//    }

private:
    std::tuple<Args...> tupleSubModel_;

    std::string name_;
  //  static void* context_;
};

class Nil {
public:
    void Run(TestModel<Nil>*) { 
        //printf("nil\n"); 
    }
};

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

