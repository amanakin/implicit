#pragma once

#include <memory>
#include <string>
#include <stdexcept>

std::string CurrentDateTime();

std::string IntToHex(uint64_t val);

template<typename ... Args>
std::string StringFormat( const std::string& format, Args ... args )
{
    int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
    auto size = static_cast<size_t>( size_s );
    auto buf = std::make_unique<char[]>( size );
    std::snprintf( buf.get(), size, format.c_str(), args ... );
    return { buf.get(), buf.get() + size - 1 }; // We don't want the '\0' inside
}

int HexToDec(unsigned char c);

bool CmpFloat(float a, float b);
