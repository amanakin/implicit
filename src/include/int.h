#pragma once

#include <string> 

struct Int {
    explicit Int(int64_t value);

    // Could be called by anyone
    Int();
    explicit Int(const std::string& name);
    Int(const std::string& name, int64_t value);

    explicit operator int64_t() const;

    Int(const Int& other);
    Int(const std::string& name, const Int& other);
    Int& operator=(const Int& other);

    Int(Int&& other);
    Int(const std::string& name, Int&& other);
    Int& operator=(Int&& other);

    Int& operator++();
    Int  operator++(int);
    Int& operator--();
    Int  operator--(int);

    static uint64_t CopyCount_;
    static uint64_t MoveCount_;
    static uint64_t TmpCount_;
    
private:
    int64_t     value_;
    std::string name_;
    uint64_t    index_;

    static uint64_t CurrVarCount_;

    std::string getVarInfo() const;

    static std::string DefaultName;

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
