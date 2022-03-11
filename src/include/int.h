#pragma once

#include <string> 

#include <graph_logger.h>

#define MOVE_AVAIL

struct Int {
    Int();
    explicit Int(const std::string& name);
    Int(const std::string& name, int64_t value);
    Int(int64_t value); // allow implicit conversions

    explicit operator int64_t() const;

    Int(const Int& other);
    Int(const std::string& name, const Int& other);
    Int& operator=(const Int& other);

#ifdef MOVE_AVAIL
    Int(Int&& other) noexcept;
    Int(const std::string& name, Int&& other) noexcept;
    Int& operator=(Int&& other) noexcept;
#endif

    Int& operator++();
    Int operator++(int);
    Int& operator--();
    Int operator--(int);

    static uint64_t CopyCount_;
    static uint64_t MoveCount_;
    static uint64_t TmpCount_;
    
private:
    int64_t     value_;
    std::string name_;
    uint64_t    index_;

    GraphLogger::Id lastId_; // last id of node where this used

    static uint64_t CurrVarCount_;
    static std::string DefaultName_;

    // Text log info
    [[nodiscard]] std::string getVarInfo() const;

    // Graph log info
    void logConstruct(const std::string& constructFunction);
    void logCopyConstruct(const std::string& copyFunction, bool isMove, GraphLogger::Id other);
    void logCopyAssign(const std::string& copyFunction, bool isMove, GraphLogger::Id other);

    void logUnary(const std::string& incFunction);
    void logAssignBinary(const std::string& unaryFunction, GraphLogger::Id other);

    friend GraphLogger;

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

    friend void LogBinary(const std::string& binaryFucntion, GraphLogger::Id lhs, GraphLogger::Id rhs);
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

void LogBinary(const std::string& binaryFucntion, GraphLogger::Id lhs, GraphLogger::Id rhs);