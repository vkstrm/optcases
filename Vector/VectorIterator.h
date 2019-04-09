#ifndef VECTOR_ITERATOR_H
#define VECTOR_ITERATOR_H

#include <iterator>

template<class T>
class VectorIterator 
{
private:
    T* ptr;
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = std::remove_const<T>;
    using pointer = T*;
    using reference = T&;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;

    VectorIterator() : ptr(nullptr)
    {
    };

    VectorIterator(T* p) : ptr(p) 
    {
    };

    VectorIterator(const VectorIterator& other) 
    { 
        this->ptr = other.ptr; 
    };

    VectorIterator& operator=(const VectorIterator& other) 
    { 
        this->ptr = other.ptr; return *this; 
    };

    T& operator*() 
    { 
        return *ptr; 
    };

    T* operator->() 
    { 
        return ptr; 
    };

    T& operator[] (size_t i) 
    { 
        return ptr[i];
    };

    VectorIterator& operator++() 
    { 
        ++ptr; 
        return *this; 
    };

    VectorIterator& operator--() 
    { 
        --ptr; 
        return *this; 
    };

    VectorIterator operator++(int) 
    { 
        VectorIterator temp(*this); 
        ++ptr; 
        return temp; 
    };

    VectorIterator operator--(int) 
    { 
        VectorIterator temp(*this);
        --ptr; 
        return temp; 
    };

    VectorIterator operator+(difference_type i) const 
    { 
        VectorIterator temp(*this); 
        temp.ptr += i; 
        return temp; 
    };

    VectorIterator operator-(difference_type i) const 
    { 
        VectorIterator temp(*this);
        temp.ptr -= i; 
        return temp; 
    };

    difference_type operator-(const VectorIterator& other) const 
    { 
        return std::distance(ptr, other.ptr); 
    };

    //Const variants
    friend bool operator==(const VectorIterator& lhs, const VectorIterator& rhs) { return lhs.ptr == rhs.ptr; };
    friend bool operator!=(const VectorIterator& lhs, const VectorIterator& rhs) { return lhs.ptr != rhs.ptr; };
    friend bool operator<(const VectorIterator& lhs, const VectorIterator& rhs)  { return lhs.ptr < rhs.ptr; };
    friend bool operator>(const VectorIterator& lhs, const VectorIterator& rhs)  { return lhs.ptr > rhs.ptr; };
    friend bool operator>=(const VectorIterator& lhs, const VectorIterator& rhs) { return lhs.ptr >= rhs.ptr; };
    friend bool operator<=(const VectorIterator& lhs, const VectorIterator& rhs) { return lhs.ptr <= rhs.ptr; };
    //Same but non const
    friend bool operator==(VectorIterator& lhs, VectorIterator& rhs) { return lhs.ptr == rhs.ptr; };
    friend bool operator!=(VectorIterator& lhs, VectorIterator& rhs) { return lhs.ptr != rhs.ptr; };
    friend bool operator<(VectorIterator& lhs, VectorIterator& rhs)  { return lhs.ptr < rhs.ptr; }; 
    friend bool operator>(VectorIterator& lhs, VectorIterator& rhs)  { return lhs.ptr > rhs.ptr; };
    friend bool operator>=(VectorIterator& lhs, VectorIterator& rhs) { return lhs.ptr >= rhs.ptr; };
    friend bool operator<=(VectorIterator& lhs, VectorIterator& rhs) { return lhs.ptr <= rhs.ptr; };
};

#endif