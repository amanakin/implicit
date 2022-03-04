// int.cc

#include <int.h>
#include <logger.h>
#include <utils.h>
#include <rec_cnt.h>

uint64_t Int::CopyCount_    = 0;
uint64_t Int::TmpCount_     = 0;
uint64_t Int::MoveCount_    = 0;

uint64_t Int::CurrVarCount_ = 0;

std::string Int::DefaultName_ = "tmp_var";

std::string Int::getVarInfo() const {
    auto color = IntToHex(reinterpret_cast<uint64_t>(this)); 
    return
    StringFormat("[<font color=#%s>%p</font>] \"%-20s(%10lli) {%llu}",
        color.c_str(),
        this,
        (name_ + "\"").c_str(),
        value_,
        index_);
}

void Int::logConstruct(const std::string& constructFunction) {
    lastId_ = GraphLogger::addVarNode(constructFunction, *this);
}

#define LOG_CONSTRUCT logConstruct(__PRETTY_FUNCTION__)

void Int::logCopyConstruct(const std::string& copyFunction, bool isMove, GraphLogger::Id other) {
    lastId_ = GraphLogger::addVarNode(copyFunction, *this, isMove ? Colors::LIGHT_GREEN : Colors::RED);
    GraphLogger::addEdge(other, lastId_, GraphLogger::EdgeType::Dashed);
}

#define LOG_COPY_CONSTRUCT(isMove) logCopyConstruct(__PRETTY_FUNCTION__, isMove, other.lastId_)

void Int::logCopyAssign(const std::string& copyFunction, bool isMove, GraphLogger::Id other) {
    auto prevId = lastId_;
    lastId_ =  GraphLogger::addVarNode(copyFunction, *this, isMove ? Colors::LIGHT_GREEN : Colors::RED);
    GraphLogger::addEdge(other, lastId_, GraphLogger::EdgeType::Dashed);
    GraphLogger::addEdge(prevId, lastId_);
}

#define LOG_COPY_ASSIGN(isMove) logCopyAssign(__PRETTY_FUNCTION__, isMove, other.lastId_)

void Int::logUnary(const std::string& incFunction) {
    auto prevId = lastId_;
    lastId_ = GraphLogger::addVarNode(incFunction, *this);
    GraphLogger::addEdge(prevId, lastId_);
}

#define LOG_UNARY logUnary(__PRETTY_FUNCTION__)

void Int::logAssignBinary(const std::string& unaryFunction, GraphLogger::Id other) {
    auto prevId = lastId_;
    lastId_ = GraphLogger::addVarNode(unaryFunction, *this);
    GraphLogger::addEdge(other,  lastId_, GraphLogger::EdgeType::Dashed);
    GraphLogger::addEdge(prevId, lastId_);
}

#define LOG_ASSIGN_BINARY lhs.logAssignBinary(__PRETTY_FUNCTION__, rhs.lastId_)

void LogBinary(const std::string& binaryFucntion, GraphLogger::Id lhs, GraphLogger::Id rhs) {
    auto id = GraphLogger::addFunctionNode(binaryFucntion);
    GraphLogger::addEdge(lhs, id, GraphLogger::EdgeType::Dotted);
    GraphLogger::addEdge(rhs, id, GraphLogger::EdgeType::Dotted);
    GraphLogger::addEdge(id, GraphLogger::getCurrId());
}

#define LOG_BINARY LogBinary(__PRETTY_FUNCTION__, lhs.lastId_, rhs.lastId_)

#define LOG_FUNC                                  \
    Logger::log(StringFormat("%5.*s: %-45s: %s",  \
    RecCnt::GetRecoursiveLevel(),                 \
    "******",                                     \
    __PRETTY_FUNCTION__,                          \
    getVarInfo().c_str()))                        \

#define LOG_COPY                                           \
    Logger::log(StringFormat("%5.*s: %-45s: %-80s by %s",  \
    RecCnt::GetRecoursiveLevel(),                           \
    "******",                                               \
    __PRETTY_FUNCTION__,                                    \
    getVarInfo().c_str(),                                   \
    other.getVarInfo().c_str()))                    

#define LOG_FUNC_BIN(OPER)                                  \
    Logger::log(StringFormat("%5.*s: %-45s: %-80s %2s %s",  \
    RecCnt::GetRecoursiveLevel(),                           \
    "******",                                               \
    __PRETTY_FUNCTION__,                                    \
    lhs.getVarInfo().c_str(),                               \
    #OPER,                                                  \
    rhs.getVarInfo().c_str()))

// ================================================================================
// ====================== Constructors ============================================
// ================================================================================

Int::Int(int64_t value)
    : name_(DefaultName_),
    value_(value),
    index_(CurrVarCount_++) {
    RecCnt rec;
    LOG_FUNC;
    TmpCount_++;
    LOG_CONSTRUCT;
}

Int::Int()
    : name_(DefaultName_),
    value_(std::rand()),
    index_(CurrVarCount_++)
{
    RecCnt rec;
    LOG_FUNC;
    TmpCount_++;
    LOG_CONSTRUCT;
}

Int::Int(const std::string& name) 
    : name_(name),
    value_(std::rand()),
    index_(CurrVarCount_++)
{
    RecCnt rec;
    LOG_FUNC;
    LOG_CONSTRUCT;
}

Int::Int(const std::string& name, int64_t value) 
    : name_(name),
    value_(value),
    index_(CurrVarCount_++)
{
    RecCnt rec;
    LOG_FUNC;
    LOG_CONSTRUCT;
}

// ================================================================================
// ====================== Internal methods ========================================
// ================================================================================

Int::operator int64_t() const {
    RecCnt rec;
    LOG_FUNC;
    return value_;
}

Int::Int(const Int& other)
    : name_(DefaultName_),
    value_(other.value_),
    index_(CurrVarCount_++) 
{
    RecCnt rec;
    LOG_COPY;
    TmpCount_++;
    CopyCount_++;
    LOG_COPY_CONSTRUCT(false);
}

Int::Int(const std::string& name, const Int& other)
    : name_(name),
    value_(other.value_),
    index_(CurrVarCount_++)
{   
    RecCnt rec;
    LOG_COPY;
    CopyCount_++;
    LOG_COPY_CONSTRUCT(false);
}

Int& Int::operator=(const Int& other) {
    RecCnt rec;
    value_ = other.value_;
    LOG_COPY;
    CopyCount_++;

    LOG_COPY_ASSIGN(false);
    return *this;
}

#ifdef MOVE_AVAIL
Int::Int(Int&& other) noexcept
    : name_(DefaultName_),
    value_(other.value_),
    index_(CurrVarCount_++)
{
    RecCnt rec;
    LOG_COPY; 
    TmpCount_++;
    MoveCount_++;
    LOG_COPY_CONSTRUCT(true);
}

Int::Int(const std::string& name, Int&& other) noexcept
    : name_(name),
    value_(other.value_),
    index_(CurrVarCount_++)
{
    RecCnt rec;
    LOG_COPY;
    MoveCount_++;
    LOG_COPY_CONSTRUCT(true);
}


Int& Int::operator=(Int&& other) noexcept {
    RecCnt rec;
    value_ = other.value_;
    LOG_COPY;
    MoveCount_++;
    LOG_COPY_ASSIGN(true);

    return *this;
}

#endif

// ================================================================================
// ====================== Unary arithmetic operators ==============================
// ================================================================================

Int& Int::operator++() {
    RecCnt rec;
    value_++;
    LOG_FUNC;

    LOG_UNARY;
    return *this;
}

Int Int::operator++(int) {
    RecCnt rec;
    Int old = *this;
    operator++();
    LOG_FUNC;

    LOG_UNARY;
    return old;
}

Int& Int::operator--() {
    RecCnt rec;
    value_--;
    LOG_FUNC;

    LOG_UNARY;
    return *this;
}

Int Int::operator--(int) {
    RecCnt rec;
    Int old = *this;
    operator--();
    LOG_FUNC;

    LOG_UNARY;
    return old;
}

// ================================================================================
// ====================== Binary arithmetic operators =============================
// ================================================================================

Int operator+(const Int& lhs, const Int& rhs) {
    RecCnt rec;
    LOG_FUNC_BIN(+);
    LOG_BINARY;
    return Int{lhs.value_ + rhs.value_};
}

Int operator-(const Int& lhs, const Int& rhs) {
    RecCnt rec;
    LOG_FUNC_BIN(-);
    LOG_BINARY;
    return Int{lhs.value_ - rhs.value_};
}

Int operator*(const Int& lhs, const Int& rhs) {
    RecCnt rec;
    LOG_FUNC_BIN(*);
    LOG_BINARY;
    return Int{lhs.value_ * rhs.value_};
}

Int operator/(const Int& lhs, const Int& rhs) {
    RecCnt rec;
    LOG_FUNC_BIN(/);
    LOG_BINARY;
    return Int{lhs.value_ / rhs.value_};
}

Int operator%(const Int& lhs, const Int& rhs) {
    RecCnt rec;
    LOG_FUNC_BIN(%);
    LOG_BINARY;
    return Int{lhs.value_ % rhs.value_};
}

// ================================================================================
// ====================== Binary assignment operators =============================
// ================================================================================

Int& operator+=(Int& lhs, const Int& rhs) {
    RecCnt rec;
    lhs.value_ += rhs.value_;
    LOG_FUNC_BIN(+=);
    LOG_ASSIGN_BINARY;
    return lhs;
}

Int& operator-=(Int& lhs, const Int& rhs) {
    RecCnt rec;
    lhs.value_ -= rhs.value_;
    LOG_FUNC_BIN(-=);
    LOG_ASSIGN_BINARY;
    return lhs;
}

Int& operator*=(Int& lhs, const Int& rhs) {
    RecCnt rec;
    lhs.value_ *= rhs.value_;
    LOG_FUNC_BIN(*=);
    LOG_ASSIGN_BINARY;
    return lhs;
}

Int& operator/=(Int& lhs, const Int& rhs) {
    RecCnt rec;
    lhs.value_ /= rhs.value_;
    LOG_FUNC_BIN(/=);
    LOG_ASSIGN_BINARY;
    return lhs;
}

Int& operator%=(Int& lhs, const Int& rhs) {
    RecCnt rec;
    lhs.value_ %= rhs.value_;
    LOG_FUNC_BIN(%=);
    LOG_ASSIGN_BINARY;
    return lhs;
}

// ================================================================================
// ====================== Comparison operators ====================================
// ================================================================================

bool operator==(const Int& lhs, const Int& rhs) {
    RecCnt rec;
    LOG_FUNC_BIN(==);
    return lhs.value_ == rhs.value_;
}

bool operator!=(const Int& lhs, const Int& rhs) {
    RecCnt rec;
    LOG_FUNC_BIN(!=);
    return lhs.value_ != rhs.value_;
}

bool operator<=(const Int& lhs, const Int& rhs) {
    RecCnt rec;
    LOG_FUNC_BIN(<=);
    return lhs.value_ <= rhs.value_;
}

bool operator>=(const Int& lhs, const Int& rhs) {
    RecCnt rec;
    LOG_FUNC_BIN(>=);
    return lhs.value_ >= rhs.value_;
}

bool operator< (const Int& lhs, const Int& rhs) {
    RecCnt rec;
    LOG_FUNC_BIN(<);
    return lhs.value_ < rhs.value_;
}

bool operator> (const Int& lhs, const Int& rhs) {
    RecCnt rec;
    LOG_FUNC_BIN(>);
    return lhs.value_ > rhs.value_;
}
