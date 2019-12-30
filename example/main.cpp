#include "TestModel.h"

class TestHelloworld : TestModel {
public:
    TestHelloworld() : TestModel("TestHelloworld") {
        Item item("hello world");
        ItemPrinter(item).Print();
    }
};

class TestExample : TestModel {
public:
    TestExample() : TestModel("TestExample") {
        TestHelloworld();
    }
};

int main()
{
    TestExample();
}
