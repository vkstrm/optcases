#include "FloatIterator.h"

FloatIterator::FloatIterator(const FloatIterator& other) 
{ 
    this->ptr = other.ptr; 
};

FloatIterator& FloatIterator::operator=(const FloatIterator& other) 
{ 
    this->ptr = other.ptr; return *this; 
};

float& FloatIterator::operator*() 
{ 
    return *ptr; 
};

float* FloatIterator::operator->() 
{ 
    return ptr; 
};

float& FloatIterator::operator[] (size_t i) 
{ 
    return ptr[i];
};

FloatIterator& FloatIterator::operator++() 
{ 
    ++ptr;
    return *this; 
};

FloatIterator& FloatIterator::operator--() 
{ 
    --ptr; 
    return *this; 
};

FloatIterator FloatIterator::operator++(int) 
{ 
    FloatIterator temp(*this); 
    ++ptr; 
    return temp; 
};

FloatIterator FloatIterator::operator--(int) 
{ 
    FloatIterator temp(*this);
    --ptr; 
    return temp; 
};

FloatIterator FloatIterator::operator+(difference_type i) const 
{ 
    FloatIterator temp(*this); 
    temp.ptr += i; 
    return temp; 
};

FloatIterator FloatIterator::operator-(difference_type i) const 
{ 
    FloatIterator temp(*this);
    temp.ptr -= i; 
    return temp; 
};

std::ptrdiff_t FloatIterator::operator-(const FloatIterator& other) const
{ 
    return std::distance(ptr, other.ptr); 
};