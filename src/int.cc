// int.cc

#include <int.h>
#include <logger.h>
#include <utils.h>

uint64_t Int::CopyCount_    = 0;
uint64_t Int::TmpCount_     = 0;
uint64_t Int::CurrVarCount_ = 0;

#define LOG_FUNC \
    Logger::log(string_format("%s, %d: %lli, [%p], <%s>, {%llu}", \
    __func__, __LINE__,                                           \
    value_, this, name_.c_str(), index_))

#define LOG_FUNC_BIN \
    Logger::log(string_format("%s, %d: %lli, [%p], <%s>, {%llu} and %lli, [%p], <%s>, {%llu}", \
    __func__, __LINE__,                                                                        \
    lhs.value_, &lhs, lhs.name_.c_str(), lhs.index_,                                           \
    rhs.value_, &rhs, rhs.name_.c_str(), rhs.index_))

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
    value_(value)
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

Int::Int(const Int& other) {

}

Int& Int::operator=(const Int& other) {
    value_ = other.value_;
    LOG_FUNC;

    return *this;
}


Int::Int(Int&& other) {
    
}

Int& Int::operator=(Int&& other) {
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
    LOG_FUNC_BIN;
    return Int(lhs.value_ + rhs.value_);
}

Int operator-(const Int& lhs, const Int& rhs) {
    LOG_FUNC_BIN;
    return Int(lhs.value_ - rhs.value_);
}

Int operator*(const Int& lhs, const Int& rhs) {
    LOG_FUNC_BIN;
    return Int(lhs.value_ * rhs.value_);
}

Int operator/(const Int& lhs, const Int& rhs) {
    LOG_FUNC_BIN;
    return Int(lhs.value_ / rhs.value_);
}

Int operator%(const Int& lhs, const Int& rhs) {
    LOG_FUNC_BIN;
    return Int(lhs.value_ % rhs.value_);
}

// ================================================================================
// ====================== Binary assignment operators =============================
// ================================================================================

Int& operator+=(Int& lhs, const Int& rhs) {
    lhs.value_ += rhs.value_;
    LOG_FUNC_BIN;
    return lhs;
}

Int& operator-=(Int& lhs, const Int& rhs) {
    lhs.value_ -= rhs.value_;
    LOG_FUNC_BIN;
    return lhs;
}

Int& operator*=(Int& lhs, const Int& rhs) {
    lhs.value_ *= rhs.value_;
    LOG_FUNC_BIN;
    return lhs;
}

Int& operator/=(Int& lhs, const Int& rhs) {
    lhs.value_ /= rhs.value_;
    LOG_FUNC_BIN;
    return lhs;
}

Int& operator%=(Int& lhs, const Int& rhs) {
    lhs.value_ %= rhs.value_;
    LOG_FUNC_BIN;
    return lhs;
}

// ================================================================================
// ====================== Comparison operators ====================================
// ================================================================================

bool operator==(const Int& lhs, const Int& rhs) {
    LOG_FUNC_BIN;
    return lhs.value_ == rhs.value_;
}

bool operator!=(const Int& lhs, const Int& rhs) {
    LOG_FUNC_BIN;
    return lhs.value_ != rhs.value_;
}

bool operator<=(const Int& lhs, const Int& rhs) {
    LOG_FUNC_BIN;
    return lhs.value_ <= rhs.value_;
}

bool operator>=(const Int& lhs, const Int& rhs) {
    LOG_FUNC_BIN;
    return lhs.value_ >= rhs.value_;
}

bool operator< (const Int& lhs, const Int& rhs) {
    LOG_FUNC_BIN;
    return lhs.value_ < rhs.value_;
}

bool operator> (const Int& lhs, const Int& rhs) {
    LOG_FUNC_BIN;
    return lhs.value_ > rhs.value_;
}
