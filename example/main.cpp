#include "TestModel.h"

class TestHelloworld : public TestModel<Nil> {
public:
    TestHelloworld() : TestModel(this) {}
    
    void Work() override {
        Item item("hello world");
        ItemWrapper(item).Print();

        int one = Get<int>("one"); //{"one": 1}

        ItemWrapper(
            Item(one),
            Item(Get<int>("two")),
            Item(Get<int>("three", "value"))
        ).Print();

//        vector<int> ivec = Array<int>("uids"); //{"uids" : [1, 2, 3]}

//        Get<string>("family", "father", "name");    //{"family": {"father": {"name": "bb"}}}

        ItemWrapper(
            Item(1, "%d: Hello world"),
            Item(2, "%d: Hello world")
        ).Print();
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
