#pragma once

#include <array>
#include <CircularBuffer.hpp>

template<class T, std::size_t N>
class Statistics
{
private:
    CircularBuffer<T, N> buffer{};
public:
    void add_entry(T entry);

    std::array<T, N>* get_data();

    void clear();
};