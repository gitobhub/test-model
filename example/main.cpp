#include "TestModel.h"

class TestHelloworld : TestModel<> {
public:
    TestHelloworld() : TestModel(this) {
        Item item("hello world");
        ItemWrapper(item).Print();

        int one = Get<int>("one"); //{"one": 1}

        vector<int> ivec = Array<int>("uids"); //{"uids" : [1, 2, 3]}

        Get<string>("family", "father", "name");    //{"family": {"father": {"name": "bb"}}}

        ItemWrapper(
            Item(1, "%d: Hello world"),
            Item(2, "%d: Hello world")
        ).Print();
    }
};

class TestSubExample : TestModel<TestHelloworld> {
public:
    TestSubExample() : TestModel(this) {}
};

class TestExample : TestMoel<TestSubExample> {
public:
    TestExample() : TestModel(this) {}
};

int main()
{
    TestExample();
}
