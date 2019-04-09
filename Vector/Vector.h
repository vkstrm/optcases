#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <vector>
#include <cassert>
#include <string>
#include <memory>
#include <utility>
#include <type_traits>

#include <string.h>

#include "VectorIterator.h"


template <class T>
class Vector {

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


    using iterator = VectorIterator<T>;
    using const_iterator = VectorIterator<const T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    Vector();
    template<class Titer>
    Vector(size_t newCapacity, const Titer& begin, const Titer& end);
    ~Vector() noexcept;
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

    Vector& assStrong(const Vector& other);
    Vector& assSimple(const Vector& other);
    Vector& assFast(const Vector& other);

    Vector(const char* other) 
    {
        int len = strlen(other);
        _capacity = len;
        _size = len;
        _content = _alloc.allocate(len);
        std::uninitialized_copy(other, other + _size, _content);
    }

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

    Vector& operator+=(const Vector& other);

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
    friend bool operator==(const Vector& lhs, const Vector& other)
    {
        if(lhs._size != other._size) return false;
        for(size_t i = 0; i < lhs._size; i++)
        {
            if(lhs._content[i] != other._content[i]) return false;
        }
        return true;
    };

    friend bool operator!=(const Vector& lhs, const Vector& other)
    {
        if(lhs == other) return false;
        return true;
    };

    friend bool operator<(const Vector& lhs, const Vector& other)
    {
        return std::lexicographical_compare(lhs.begin(), lhs.end(), other.begin(), other.end());
    };
    friend bool operator>(const Vector& lhs, const Vector& other) { return other < lhs; };
    friend bool operator<=(const Vector& lhs, const Vector& other) { return !(other < lhs); };
    friend bool operator>=(const Vector& lhs, const Vector& other) { return !(lhs < other); }; 

    friend bool operator==(Vector& lhs, Vector& other)
    {
        if(lhs._size != other._size) return false;
        for(size_t i = 0; i < lhs._size; i++)
        {
            if(lhs._content[i] != other._content[i]) return false;
        }
        return true;
    };

    friend bool operator!=(Vector& lhs, Vector& other)
    {
        if(lhs == other) return false;
        return true;
    };

    friend bool operator<(Vector& lhs, Vector& other)
    {
        return std::lexicographical_compare(lhs.begin(), lhs.end(), other.begin(), other.end());
    };
    friend bool operator>(Vector& lhs, Vector& other) { return other < lhs; };
    friend bool operator<=(Vector& lhs, Vector& other) { return !(other < lhs); };
    friend bool operator>=(Vector& lhs, Vector& other) { return !(lhs < other); }; 

    friend std::ostream& operator<<(std::ostream& cout, Vector& other)
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
    void swap(Vector& lhs, Vector& rhs) noexcept;
    void swap(Vector& other) noexcept;
    void Check() { assert(invariant()); };
};

/**
 * Default constrcutor
 */
template<class T>
Vector<T>::Vector() : _size(0), _capacity(0) 
{
    _content = _alloc.allocate(_capacity); // If it fails no memory was ever allocated, so no leak.
    invariant();
}

/**
 * Help constructor
 */
template<class T>
template<class Titer>
Vector<T>::Vector(size_t newCapacity, const Titer& begin, const Titer& end)
{
    _content = _alloc.allocate(newCapacity); // Again, program will exit before memory is allocated.
    int i = 0;
    try {
        for(auto it = begin; it != end; ++it)
        {
            new(_content + i++) T(*it);
        }
    } catch (...) { // If copy construction of Titer objects fail
        while(_content++) _content->~T();
        _alloc.deallocate(_content, newCapacity);
        throw;
    }
}

/**
 * Copy constructor
 */
template<class T>
Vector<T>::Vector(const Vector& other) : Vector(other.size()+1, other.begin(), other.end()) 
{
    _capacity = other._capacity;
    _size = other._size;
    invariant();
};

/**
 * Destructor
 */
template <class T>
Vector<T>::~Vector() noexcept
{
    invariant();
    for(size_t i = 0; i < _size; i++)      // Varför ens göra detta??
    {
        _content[i].~T();
    }
    _alloc.deallocate(_content,_capacity);
    _content = nullptr;
    _capacity = 0;
    _size = 0;
}

/**
 * Move constructor
 */
template <class T>
Vector<T>::Vector(Vector&& other) noexcept
{
    _size = other._size;
    _capacity = other._capacity;
    _content = other._content;
    other._size = 0;
    other._capacity = 0;
    other._content = nullptr;
    invariant();
}

/**
 * Copy assignment
 */
template <class T>
Vector<T>& Vector<T>::assSimple(const Vector& other)
{
    T* temp;
    try {
        temp = _alloc.allocate(other._capacity);
        std::uninitialized_copy(other._content, other._content + other._size, temp);
        _alloc.deallocate(_content, _capacity);
    } catch (...) {
        _alloc.deallocate(temp, other._capacity);
        throw;
    }
    _size = other._size;
    _capacity = other._capacity;
    _content = temp;
    invariant();
    return *this;
}

template <class T>
Vector<T>& Vector<T>::assStrong(const Vector& other)
{
    Vector<T> v(other);
    swap(v);
    return *this;
}

template <class T>
Vector<T>& Vector<T>::assFast(const Vector& other) 
{
    if(_capacity < other.size())
    {
        Vector<T> temp(other);
        swap(temp);
        return *this;
    }
    if(*this == other) return *this;
    if(_size > other.size())
    {
        std::copy(other._content, other._content + other._size, _content);
        for(T* ptr = _content + other._size; ptr != _content + _size; ptr++)
        {
            ptr->~T();
        }
    }
    else if(_size < other._size)
    {
        std::copy(other._content, other._content + _size, _content);
        std::uninitialized_copy(other._content + _size, other._content + other._size, _content + _size);
    }
    else
    {
        std::copy(other._content, other._content + other._size, _content);
    }
    _size = other._size;
    invariant();
    return *this;
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector& other)
{
    if(_capacity < other.size())
    {
        Vector<T> temp(other);
        swap(temp);
        return *this;
    }
    if(*this == other) return *this;
    if(_size > other.size())
    {
        std::copy(other._content, other._content + other._size, _content);
        for(T* ptr = _content + other._size; ptr != _content + _size; ptr++)
        {
            ptr->~T();
        }
    }
    else if(_size < other._size)
    {
        std::copy(other._content, other._content + _size, _content);
        std::uninitialized_copy(other._content + _size, other._content + other._size, _content + _size);
    }
    else
    {
        std::copy(other._content, other._content + other._size, _content);
    }
    _size = other._size;
    invariant();
    return *this;
}


/**
 * Move assignment
 */
template <class T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept
{
    if(&other == this) return *this;
    _alloc.deallocate(_content, _capacity);
    _size = other._size;
    _capacity = other._capacity;
    _content = other._content;
    other._size = 0;
    other._capacity = 0;
    other._content = nullptr;
    invariant();
    return *this;
}

/**
 * Subscript operator
 */
template <class T>
T& Vector<T>::operator[] (size_t i)
{
    return _content[i];
}

/**
 * At function checking for out of range
 */
template <class T>
T& Vector<T>::at(size_t i)
{
    if(i >= _size) throw std::out_of_range("Requested index out of range");
    return _content[i];
}

/**
 * Const subscript operator
 */
template <class T>
const T& Vector<T>::operator[](size_t i) const
{
    return _content[i];
}

/**
 * Const At function checking for out of range
 */
template <class T>
const T& Vector<T>::at(size_t i) const
{
    if(i >= _size) throw std::out_of_range("Requested index out of range");
    return _content[i];
}

/**
 * Return the current size, number of elements
 */
template <class T>
size_t Vector<T>::size() const noexcept
{
    return _size;
}

/**
 * Change the total capacity to passed value
 */
template <class T>
void Vector<T>::reserve(size_t n)
{
    if(n <= _capacity) return;
    T* temp = _alloc.allocate(n);
    try {
        std::uninitialized_copy(_content, _content + _size, temp);
    } catch (...) {
        _alloc.deallocate(temp, n);
        throw;
    }
    _alloc.deallocate(_content, _capacity);
    _capacity = n;
    _content = temp;
}

/**
 * Returns the current capacity
 */
template <class T>
size_t Vector<T>::capacity() const noexcept
{
    return _capacity;
}

/**
 * Changes capacity to current number of elements
 */
template <class T>
void Vector<T>::shrink_to_fit()
{
    if(_size == _capacity) return;
    T* temp = _alloc.allocate(_size);
    try {
        std::copy(_content, _content + _size, temp);
    } catch (...) {
        _alloc.deallocate(temp, _size);
        throw;
    }
    _alloc.deallocate(_content, _capacity);
    _content = temp;
    _capacity = _size;
}

/**
 * Add element at the last index via lvalue reference
 */
template <class T>
void Vector<T>::push_back(const T& c)
{
    if(_size >= _capacity)
    {
        // Vector<T> temp;
        // temp._size = _size;
        // temp.reserve((_size + 1) * 1.5);
        // std::uninitialized_copy(begin(), end(), temp.begin());
        // new(temp._content + temp._size) T(c);
        // ++temp._size;
        // // _alloc.deallocate(_content, _capacity);
        // swap(temp);
        // return;

        size_t oldcap = _capacity;
        _capacity = (_size + 1) * 1.5;
        T* temp = _alloc.allocate(_capacity);
        try {
            std::uninitialized_copy(_content, _content + _size, temp);
        } catch (...) {
            _alloc.deallocate(temp, _capacity);
            _capacity = oldcap;
            throw;
        }
        _alloc.deallocate(_content, oldcap);
        _content = temp;
    }
    new(_content + _size) T(c);
    ++_size;
}

/**
 * Add element at last index via rvalue reference
 */
template <class T>
void Vector<T>::push_back(T&& c)
{
    if(_size >= _capacity)
    {
        // Vector<T> temp;
        // temp._size = _size;
        // temp.reserve((_size + 1) * 1.5);
        // std::uninitialized_copy(begin(), end(), temp.begin());
        // new (temp._content + temp._size) T(std::forward<T>(c));
        // ++temp._size;
        // // _alloc.deallocate(_content, _capacity);
        // swap(temp);
        // return;



        size_t oldcap = _capacity;
        _capacity = (_size + 1) * 1.5;
        T* temp = _alloc.allocate(_capacity);
        try {
            std::copy(_content, _content + _size, temp);
        } catch (...) {
            _alloc.deallocate(temp, _capacity);
            _capacity = oldcap;
            throw;
        }
        _alloc.deallocate(_content, oldcap);    
        _content = temp;
    }
    new(_content + _size) T(std::forward<T>(c)); // Är det här korrekt/nödvändigt?
    ++_size;
}

/**
 * Change capacity to passed capacity.
 */
template <class T>
void Vector<T>::resize(size_t n)
{
    if(n > _capacity) // Doesn't fit? Make new memory
    {
        // size_t oldcap = _capacity;
        // _capacity = n;
        T* temp = _alloc.allocate(n);
        std::uninitialized_copy(_content, _content + _size, temp);
        _alloc.deallocate(_content, _capacity);
        _content = temp;
        _capacity = n;
    }
    if(n > _size) // Fits? Construct Ts.
    {
        for(size_t i = _size; i < n; ++i)
        {
            // _content[i] = T();
            new(_content + i) T();
        }
    }
    _size = n;
}

/**
 * Concantentation
 */
template <class T>
Vector<T>& Vector<T>::operator+=(const Vector& other)
{
    if(_size + other._size <= _capacity)
    {
        std::copy(other._content, other._content + other._size, _content + _size);
    }
    else
    {
        T* temp = _alloc.allocate(_capacity + other._size);
        std::copy(_content, _content + _size, temp);
        std::copy(other._content, other._content + other._size, temp + _size);
        _alloc.deallocate(_content, _capacity);
        _content = temp;
        _capacity += other._size;
        _size += other._size;
    }
    return *this;
}

template <class T>
typename Vector<T>::iterator Vector<T>::begin() 
{ 
    return iterator(_content); 
}

template <class T>
typename Vector<T>::iterator Vector<T>::end() 
{ 
    return iterator(_content + _size); 
}

template <class T>
typename Vector<T>::const_iterator Vector<T>::begin() const
{ 
    return const_iterator(_content); 
}

template <class T>
typename Vector<T>::const_iterator Vector<T>::end() const
{ 
    return const_iterator(_content + _size); 
}

template <class T>
typename Vector<T>::const_iterator Vector<T>::cbegin() const 
{ 
    return const_iterator(_content); 
}

template <class T>
typename Vector<T>::const_iterator Vector<T>::cend() const 
{ 
    return const_iterator(_content + _size); 
}

template <class T>
typename Vector<T>::reverse_iterator Vector<T>::rbegin() 
{ 
    return reverse_iterator(end());
}

template <class T>
typename Vector<T>::reverse_iterator Vector<T>::rend()
{ 
    return reverse_iterator(begin());
}

template <class T>
typename Vector<T>::const_reverse_iterator Vector<T>::rbegin() const
{ 
    return const_reverse_iterator(end());
}

template <class T>
typename Vector<T>::const_reverse_iterator Vector<T>::rend() const
{ 
    return const_reverse_iterator(begin());
}

template <class T>
typename Vector<T>::const_reverse_iterator Vector<T>::crbegin() const 
{ 
    return const_reverse_iterator(cend());
}

template <class T>
typename Vector<T>::const_reverse_iterator Vector<T>::crend() const 
{ 
    return const_reverse_iterator(cbegin());
}

template <class T>
void Vector<T>::swap(Vector<T>& lhs, Vector<T>& rhs) noexcept
{
    std::swap(lhs._size, rhs._size);
    std::swap(lhs._capacity, rhs._capacity);
    std::swap(lhs._content, rhs._content);
}

template <class T>
void Vector<T>::swap(Vector<T>& other) noexcept
{
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
    std::swap(_content, other._content);
}


#endif