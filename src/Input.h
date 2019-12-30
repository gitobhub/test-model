#pragma once

class Input 
{
public:
    static Input& Inst() { 
        static Input instance;
        return instance;
    }

    void Init();

priavte:
    Input() { }
};
