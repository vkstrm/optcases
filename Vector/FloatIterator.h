#ifndef FLOAT_ITERATOR_H
#define FLOAT_ITERATOR_H

#include <iterator>

class FloatIterator 
{
    using T = float;
private:
    T* ptr;
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = std::remove_const<T>;
    using pointer = T*;
    using reference = T&;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;

    FloatIterator() : ptr(nullptr)
    {
    };

    FloatIterator(T* p) : ptr(p) 
    {
    };

    FloatIterator(const FloatIterator& other);
    FloatIterator& operator=(const FloatIterator& other); 
    T& operator*(); 
    T* operator->(); 
    T& operator[] (size_t i); 
    FloatIterator& operator++();
    FloatIterator& operator--(); 
    FloatIterator operator++(int); 
    FloatIterator operator--(int); 
    FloatIterator operator+(difference_type i) const; 
    FloatIterator operator-(difference_type i) const; 
    difference_type operator-(const FloatIterator& other) const;

    // FloatIterator(const FloatIterator& other) 
    // { 
    //     this->ptr = other.ptr; 
    // }


    // FloatIterator& operator=(const FloatIterator& other) 
    // { 
    //     this->ptr = other.ptr; return *this; 
    // }

    // T& operator*() 
    // { 
    //     return *ptr; 
    // }

    // T* operator->() 
    // { 
    //     return ptr; 
    // }

    // T& operator[] (size_t i) 
    // { 
    //     return ptr[i];
    // }


    // FloatIterator& operator++() 
    // { 
    //     ++ptr; 
    //     return *this; 
    // }

    // FloatIterator& operator--() 
    // { 
    //     --ptr; 
    //     return *this; 
    // }

    // FloatIterator operator++(int) 
    // { 
    //     FloatIterator temp(*this); 
    //     ++ptr; 
    //     return temp; 
    // }


    // FloatIterator operator--(int) 
    // { 
    //     FloatIterator temp(*this);
    //     --ptr; 
    //     return temp; 
    // }

    // FloatIterator operator+(difference_type i) const 
    // { 
    //     FloatIterator temp(*this); 
    //     temp.ptr += i; 
    //     return temp; 
    // }

    // FloatIterator operator-(difference_type i) const 
    // { 
    //     FloatIterator temp(*this);
    //     temp.ptr -= i; 
    //     return temp; 
    // }

    // difference_type operator-(const FloatIterator& other) const
    // { 
    //     return std::distance(ptr, other.ptr); 
    // }

    //Const variants
    friend bool operator==(const FloatIterator& lhs, const FloatIterator& rhs) { return lhs.ptr == rhs.ptr; };
    friend bool operator!=(const FloatIterator& lhs, const FloatIterator& rhs) { return lhs.ptr != rhs.ptr; };
    friend bool operator<(const FloatIterator& lhs, const FloatIterator& rhs)  { return lhs.ptr < rhs.ptr; };
    friend bool operator>(const FloatIterator& lhs, const FloatIterator& rhs)  { return lhs.ptr > rhs.ptr; };
    friend bool operator>=(const FloatIterator& lhs, const FloatIterator& rhs) { return lhs.ptr >= rhs.ptr; };
    friend bool operator<=(const FloatIterator& lhs, const FloatIterator& rhs) { return lhs.ptr <= rhs.ptr; };
    //Same but non const
    friend bool operator==(FloatIterator& lhs, FloatIterator& rhs) { return lhs.ptr == rhs.ptr; };
    friend bool operator!=(FloatIterator& lhs, FloatIterator& rhs) { return lhs.ptr != rhs.ptr; };
    friend bool operator<(FloatIterator& lhs, FloatIterator& rhs)  { return lhs.ptr < rhs.ptr; }; 
    friend bool operator>(FloatIterator& lhs, FloatIterator& rhs)  { return lhs.ptr > rhs.ptr; };
    friend bool operator>=(FloatIterator& lhs, FloatIterator& rhs) { return lhs.ptr >= rhs.ptr; };
    friend bool operator<=(FloatIterator& lhs, FloatIterator& rhs) { return lhs.ptr <= rhs.ptr; };
};

#endif