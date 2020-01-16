#pragma once

#include <atomic>

#include "Cursor.h"

class Output
{
public:
    void Open(const std::string& name) {
        int indent = (Cursor::Inst().Get() == 0 ? 0 : Cursor::Inst().Get());
        cout << "\033[" << indent << "C";
        cout << name << " {" << endl;
        Cursor::Inst() += 4;
    }

    void Close() {
        if (!bClosed_) {
            cout << "\033[" << (Cursor::Inst() -= 4) << "C";
            cout << "}" << endl;
            bClosed_ = true;
        }
    }

private:
    std::atomic<bool> bClosed_ {false};
};
