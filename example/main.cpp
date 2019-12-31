#include "TestModel.h"

class TestHelloworld : TestModel {
public:
    TestHelloworld(Parent parent) : TestModel(this, parent) {
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

class TestSubExample : TestModel {
public:
    TestSubExample(Parent parent) : TestModel(this, parent) {
        TestHelloWorld(this);
    }
}

class TestExample : TestModel {
public:
    TestExample() : TestModel(this) {
        TestSubExample(this);
    }
};

int main()
{
    TestExample();
}
