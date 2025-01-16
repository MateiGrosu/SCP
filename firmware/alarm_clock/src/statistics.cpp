#include "statistics.h"

template <class T, std::size_t N>
void Statistics<T, N>::add_entry(T entry)
{
    this->buffer.push_back(entry);
}

template <class T, std::size_t N>
std::array<T, N>* Statistics<T, N>::get_data()
{
    return this->buffer;
}

template <class T, std::size_t N>
void Statistics<T, N>::clear()
{
    this->buffer.clear();
}
