#pragma once

class Cursor {
public:
    static Cursor& Inst() {
        static Cursor instance_;
        return instance_;
    }

    int Get() {
        return indent_;
    }

    void Set(int indent) {
        indent_ = indent;
    }

    int operator +=(int val) {
        indent_ += val;
        //printf(" +%d ", indent_);
        return indent_;
    }

    int operator -=(int val) {
        indent_ -= val;
        //printf(" -%d ", indent_);
        return indent_;
    }

private:
    Cursor() {
    }

    int indent_ {};
};

