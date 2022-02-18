#pragma once

#include <string> 

struct Int {
    explicit Int(int64_t value);

    // Could be called by anyone
    Int();
    explicit Int(const std::string& name);
    Int(const std::string& name, int64_t value);
    Int(const std::string& name, const Int&)

    explicit operator int64_t() const;

    Int(const Int& other);
    Int& operator=(const Int& other);

    Int(Int&& other);
    Int& operator=(Int&& other);

    Int& operator++();
    Int  operator++(int);
    Int& operator--();
    Int  operator--(int);

private:
    int64_t     value_;
    std::string name_;
    uint64_t    index_;

    static uint64_t CopyCount_;
    static uint64_t TmpCount_;
    static uint64_t CurrVarCount_;

    std::string getVarInfo() const;

    friend Int operator+(const Int& lhs, const Int& rhs);
    friend Int operator-(const Int& lhs, const Int& rhs);
    friend Int operator*(const Int& lhs, const Int& rhs);
    friend Int operator/(const Int& lhs, const Int& rhs);
    friend Int operator%(const Int& lhs, const Int& rhs);

    friend Int& operator+=(Int& lhs, const Int& rhs);
    friend Int& operator-=(Int& lhs, const Int& rhs);
    friend Int& operator*=(Int& lhs, const Int& rhs);
    friend Int& operator/=(Int& lhs, const Int& rhs);
    friend Int& operator%=(Int& lhs, const Int& rhs);

    friend bool operator==(const Int& lhs, const Int& rhs);
    friend bool operator!=(const Int& lhs, const Int& rhs);
    friend bool operator<=(const Int& lhs, const Int& rhs);
    friend bool operator>=(const Int& lhs, const Int& rhs);
    friend bool operator< (const Int& lhs, const Int& rhs);
    friend bool operator> (const Int& lhs, const Int& rhs);
};

Int operator+(const Int& lhs, const Int& rhs);
Int operator-(const Int& lhs, const Int& rhs);
Int operator*(const Int& lhs, const Int& rhs);
Int operator/(const Int& lhs, const Int& rhs);
Int operator%(const Int& lhs, const Int& rhs);

Int& operator+=(Int& lhs, const Int& rhs);
Int& operator-=(Int& lhs, const Int& rhs);
Int& operator*=(Int& lhs, const Int& rhs);
Int& operator/=(Int& lhs, const Int& rhs);
Int& operator%=(Int& lhs, const Int& rhs);

bool operator==(const Int& lhs, const Int& rhs);
bool operator!=(const Int& lhs, const Int& rhs);
bool operator<=(const Int& lhs, const Int& rhs);
bool operator>=(const Int& lhs, const Int& rhs);
bool operator< (const Int& lhs, const Int& rhs);
bool operator> (const Int& lhs, const Int& rhs);
