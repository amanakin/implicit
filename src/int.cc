// int.cc

#include <int.h>
#include <logger.h>

Int::Int() 
    : name_("default_name"),
    value_(std::rand())
{
    Logger::log("Int()");
}

Int::Int(const std::string& name) 
    : name_(name),
    value_(std::rand())
{
    Logger::log("Int(name)");
}

Int::Int(int64_t value) 
    : name_("default_name"),
    value_(value)
{
    Logger::log("Int(value)");
}

Int::Int(const std::string& name, int64_t value) 
    : name_(name),
    value_(value)
{
    Logger::log("Int(name, value)");
}

Int::operator int64_t() const {
    Logger::log("operator int64_t()");
    return value_;
}

Int& Int::operator=(const Int& other) {
    value_ = other.value_;

    Logger::log("operator=");

    return *this;
}


Int operator+(const Int& lhs, const Int& rhs) {
    Logger::log("operator+(const Int& lhs, const Int& rhs)");

    return Int(static_cast<int64_t>(lhs) + static_cast<int64_t>(rhs));
}
