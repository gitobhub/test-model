#include "TestModel.h"

class TestHelloworld : public TestModel<Nil> {
public:
    TestHelloworld() : TestModel(this) {}
    
    void Work() override {
        PrettyPrinter printer;

        Item item("hello world");
        printer += ItemWrapper(item);

        int one = Get<int>("one"); //{"one": 1}
        
        printer += ItemWrapper(
            Item(one),
            Item(Get<int>("two")),
            Item(Get<string>("three", "value"))
        );

        vector<int> ivec = Array<int>("uids"); //{"uids" : [1, 2, 3]}
        printer += ItemWrapper(ivec);

//        Get<string>("family", "father", "name");    //{"family": {"father": {"name": "bb"}}}

        printer += ItemWrapper(
            Item(1, "%d: Hello world"),
            Item(2, "%d: Hello world")
        );

        printer.Print();
    }
};

class TestSubExample : public TestModel<TestHelloworld> {
public:
    TestSubExample() : TestModel(this) {}
};

class TestExample : public TestModel<TestSubExample> {
public:
    TestExample() : TestModel(this) {}
};

int main()
{
    TestExample().Run();
}
