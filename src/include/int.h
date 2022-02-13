#pragma once

#include <string> 

struct Int {
    Int();
    explicit Int(const std::string& name);
    explicit Int(int64_t value);
    Int(const std::string& name, int64_t value);

    Int& operator=(const Int& other);
    operator int64_t() const;

private:
    int64_t value_;
    std::string name_;
};

Int operator+(const Int& lhs, const Int& rhs);