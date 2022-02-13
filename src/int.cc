// int.cc

#include <random>

#include <int.h>

Int::Int() 
    : name_("default_name"),
    value_(std::rand())
{}

Int::Int(const std::string& name) 
    : name_(name),
    value_(std::rand())
{}

Int::Int(int64_t value) 
    : name_("default_name"),
    value_(value)
{}

Int::Int(const std::string& name, int64_t value) 
    : name_(name),
    value_(value)
{}

Int::operator int() const {
    return value_;
}

Int& Int::operator=(const Int& other) {
    value_ = other.value_;

    return *this;
}


Int operator+(const Int& lhs, const Int& rhs) {
    return Int(static_cast<int64_t>(lhs) + static_cast<int64_t>(rhs));
}
