#ifndef FLOAT_VECTOR_H
#define FLOAT_VECTOR_H

#include <algorithm>
#include <cassert>
#include <string>
#include <memory>
#include <utility>
#include <type_traits>

#include <string.h>

#include "FloatIterator.h"


class FloatVector {
using T = float;
private:
    size_t _size;
    size_t _capacity;
    T* _content;
    std::allocator<T> _alloc = std::allocator<T>();
public:

    using value_type = std::remove_const<T>;
    using size_type = size_t; 
    using difference_type = std::ptrdiff_t;
    using const_pointer = const T*;
    using pointer = T*;
    using const_reference = const T&;
    using reference = T&;


    // using iterator = FloatIterator<T>;
    // using const_iterator = FloatIterator<const T>;
    using iterator = FloatIterator;
    using const_iterator = FloatIterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    FloatVector();
    template<class Titer>
    FloatVector(size_t newCapacity, const Titer& begin, const Titer& end);
    ~FloatVector() noexcept;
    FloatVector(const FloatVector& other);
    FloatVector(FloatVector&& other) noexcept;
    FloatVector& operator=(const FloatVector& other);
    FloatVector& operator=(FloatVector&& other) noexcept;

    const T* data() const { return _content; };
    T* data() { return _content; };

    T& operator[] (size_t i);
    T& at(size_t i);
    const T& operator[](size_t i) const;
    const T& at(size_t i) const;

    size_t size() const noexcept;
    void reserve(size_t n);
    size_t capacity() const noexcept;
    void shrink_to_fit();

    void push_back(const T& c);
    void push_back(T&& c);
    void resize(size_t n);

    FloatVector& operator+=(const FloatVector& other);

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;

    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    reverse_iterator rbegin();
    const_reverse_iterator crbegin() const;

    reverse_iterator rend();
    const_reverse_iterator crend() const;

    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;

    //Global functions
    friend bool operator==(const FloatVector& lhs, const FloatVector& other)
    {
        if(lhs._size != other._size) return false;
        for(size_t i = 0; i < lhs._size; i++)
        {
            if(lhs._content[i] != other._content[i]) return false;
        }
        return true;
    };

    friend bool operator!=(const FloatVector& lhs, const FloatVector& other)
    {
        if(lhs == other) return false;
        return true;
    };

    friend bool operator<(const FloatVector& lhs, const FloatVector& other)
    {
        return std::lexicographical_compare(lhs.begin(), lhs.end(), other.begin(), other.end());
    };
    friend bool operator>(const FloatVector& lhs, const FloatVector& other) { return other < lhs; };
    friend bool operator<=(const FloatVector& lhs, const FloatVector& other) { return !(other < lhs); };
    friend bool operator>=(const FloatVector& lhs, const FloatVector& other) { return !(lhs < other); }; 

    friend bool operator==(FloatVector& lhs, FloatVector& other)
    {
        if(lhs._size != other._size) return false;
        for(size_t i = 0; i < lhs._size; i++)
        {
            if(lhs._content[i] != other._content[i]) return false;
        }
        return true;
    };

    friend bool operator!=(FloatVector& lhs, FloatVector& other)
    {
        if(lhs == other) return false;
        return true;
    };

    friend bool operator<(FloatVector& lhs, FloatVector& other)
    {
        return std::lexicographical_compare(lhs.begin(), lhs.end(), other.begin(), other.end());
    };
    friend bool operator>(FloatVector& lhs, FloatVector& other) { return other < lhs; };
    friend bool operator<=(FloatVector& lhs, FloatVector& other) { return !(other < lhs); };
    friend bool operator>=(FloatVector& lhs, FloatVector& other) { return !(lhs < other); }; 

    friend std::ostream& operator<<(std::ostream& cout, FloatVector& other)
    {
        for(size_t i = 0; i < other.size(); ++i)
        {
            cout << other[i];
        }
        return cout;
    };

    bool invariant()
    {
        assert(_size >= 0);
        assert(_capacity >= 0);
        assert(_capacity >= _size);
        return true;
    };
    void swap(FloatVector& lhs, FloatVector& rhs) noexcept;
    void swap(FloatVector& other) noexcept;
    void Check() { assert(invariant()); };
};

#endif
