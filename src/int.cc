// int.cc

#include <int.h>
#include <logger.h>
#include <utils.h>

uint64_t Int::CopyCount_    = 0;
uint64_t Int::TmpCount_     = 0;
uint64_t Int::CurrVarCount_ = 0;

std::string Int::getVarInfo() const {
    auto color = IntToHex(reinterpret_cast<uint64_t>(this)); 
    //std::reverse(color.begin(), color.end());
    return 
    string_format("[<font color=#%s>%p</font>] \"%-20s(%10lli) {%llu}",
        color.c_str(),
        this,
        (name_ + "\"").c_str(),
        value_,
        index_);
}                              

#define LOG_FUNC                            \
    Logger::log(string_format("%-40s: %s",  \
    __PRETTY_FUNCTION__,                    \
    getVarInfo().c_str()))

#define LOG_CONSTR                                  \
    Logger::log(string_format("%-40: %-80s by %s",  \
    __PRETTY_FUNCTION__,                            \
    getVarInfo().c_str(),                           \
    other.getVarInfo().c_str()))                    

#define LOG_FUNC_BIN(OPER)                               \
    Logger::log(string_format("%-40s: %-80s "#OPER" %s", \
    __PRETTY_FUNCTION__,                                 \
    lhs.getVarInfo().c_str(),                            \
    rhs.getVarInfo().c_str()))

// ================================================================================
// ====================== Constructors ============================================
// ================================================================================

Int::Int()
    : name_("default_name"),
    value_(std::rand()),
    index_(CurrVarCount_++)
{
    LOG_FUNC;
}

Int::Int(const std::string& name) 
    : name_(name),
    value_(std::rand()),
    index_(CurrVarCount_++)
{
    LOG_FUNC;
}

Int::Int(const std::string& name, int64_t value) 
    : name_(name),
    value_(value),
    index_(CurrVarCount_++)
{
    LOG_FUNC;
}

Int::Int(int64_t value) 
    : name_("default_name"),
    value_(value),
    index_(CurrVarCount_++)
{
    LOG_FUNC;
}

// ================================================================================
// ====================== Internal methods ========================================
// ================================================================================

Int::operator int64_t() const {
    LOG_FUNC;
    return value_;
}

Int::Int(const Int& other)
    : name_("default_name"),
    value_(other.value_),
    index_(CurrVarCount_++) 
{
    LOG_CONSTR;
}

Int& Int::operator=(const Int& other) {
    value_ = other.value_;
    LOG_CONSTR;

    return *this;
}


Int::Int(Int&& other) 
    : name_("default_name"),
    value_(other.value_),
    index_(CurrVarCount_++) 
{
    LOG_CONSTR; 
}

Int& Int::operator=(Int&& other) {
    value_ = other.value_;
    LOG_CONSTR;

    return *this;
}

// ================================================================================
// ====================== Unary arithmetic operators ==============================
// ================================================================================

Int& Int::operator++() {
    value_++;
    LOG_FUNC;
    return *this;
}

Int Int::operator++(int) {
    Int old = *this;
    operator++();
    LOG_FUNC;
    return old;
}

Int& Int::operator--() {
    value_--;
    LOG_FUNC;
    return *this;
}

Int  Int::operator--(int) {
    Int old = *this;
    operator--();
    LOG_FUNC;
    return old;
}

// ================================================================================
// ====================== Binary arithmetic operators =============================
// ================================================================================

Int operator+(const Int& lhs, const Int& rhs) {
    LOG_FUNC_BIN(+);
    return Int(lhs.value_ + rhs.value_);
}

Int operator-(const Int& lhs, const Int& rhs) {
    LOG_FUNC_BIN(-);
    return Int(lhs.value_ - rhs.value_);
}

Int operator*(const Int& lhs, const Int& rhs) {
    LOG_FUNC_BIN(*);
    return Int(lhs.value_ * rhs.value_);
}

Int operator/(const Int& lhs, const Int& rhs) {
    LOG_FUNC_BIN(/);
    return Int(lhs.value_ / rhs.value_);
}

Int operator%(const Int& lhs, const Int& rhs) {
    LOG_FUNC_BIN(%);
    return Int(lhs.value_ % rhs.value_);
}

// ================================================================================
// ====================== Binary assignment operators =============================
// ================================================================================

Int& operator+=(Int& lhs, const Int& rhs) {
    lhs.value_ += rhs.value_;
    LOG_FUNC_BIN(+=);
    return lhs;
}

Int& operator-=(Int& lhs, const Int& rhs) {
    lhs.value_ -= rhs.value_;
    LOG_FUNC_BIN(-=);
    return lhs;
}

Int& operator*=(Int& lhs, const Int& rhs) {
    lhs.value_ *= rhs.value_;
    LOG_FUNC_BIN(*=);
    return lhs;
}

Int& operator/=(Int& lhs, const Int& rhs) {
    lhs.value_ /= rhs.value_;
    LOG_FUNC_BIN(/=);
    return lhs;
}

Int& operator%=(Int& lhs, const Int& rhs) {
    lhs.value_ %= rhs.value_;
    LOG_FUNC_BIN(%=);
    return lhs;
}

// ================================================================================
// ====================== Comparison operators ====================================
// ================================================================================

bool operator==(const Int& lhs, const Int& rhs) {
    LOG_FUNC_BIN(==);
    return lhs.value_ == rhs.value_;
}

bool operator!=(const Int& lhs, const Int& rhs) {
    LOG_FUNC_BIN(!=);
    return lhs.value_ != rhs.value_;
}

bool operator<=(const Int& lhs, const Int& rhs) {
    LOG_FUNC_BIN(<=);
    return lhs.value_ <= rhs.value_;
}

bool operator>=(const Int& lhs, const Int& rhs) {
    LOG_FUNC_BIN(>=);
    return lhs.value_ >= rhs.value_;
}

bool operator< (const Int& lhs, const Int& rhs) {
    LOG_FUNC_BIN(<);
    return lhs.value_ < rhs.value_;
}

bool operator> (const Int& lhs, const Int& rhs) {
    LOG_FUNC_BIN(>);
    return lhs.value_ > rhs.value_;
}
