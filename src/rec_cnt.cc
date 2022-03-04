// rec_cnt.cc

#include <iostream>

#include <rec_cnt.h>
#include <utils.h>

uint64_t RecCnt::CurrRec_ = 0;

RecCnt::RecCnt() {
    CurrRec_++;
}

RecCnt::~RecCnt() {
    CurrRec_--;
}

uint64_t RecCnt::GetRecoursiveLevel() {
    return CurrRec_;
}