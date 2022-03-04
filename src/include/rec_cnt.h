#pragma once

#include <cstdint>

struct RecCnt {
    RecCnt();
    ~RecCnt();

    static uint64_t GetRecoursiveLevel();
private:
    static uint64_t CurrRec_;
};