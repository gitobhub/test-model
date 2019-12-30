#include "TestModel.h"

class TestHelloworld : TestModel {
public:
    TestHelloworld() : TestModel("TestHelloworld") {
        Item item("hello world");
        ItemWrapper(item).Print();

        ItemWrapper(
            Item(1, "%d: Hello world"),
            Item(2, "%d: Hello world")
        ).Print();
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
