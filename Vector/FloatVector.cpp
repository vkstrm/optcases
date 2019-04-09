#include "FloatVector.h"


/**
 * Default constrcutor
 */
FloatVector::FloatVector() : _size(0), _capacity(0) 
{
    _content = _alloc.allocate(_capacity); // If it fails no memory was ever allocated, so no leak.
    invariant();
}

/**
 * Help constructor
 */
template<class Titer>
FloatVector::FloatVector(size_t newCapacity, const Titer& begin, const Titer& end)
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
FloatVector::FloatVector(const FloatVector& other) : FloatVector(other.size()+1, other.begin(), other.end()) 
{
    _capacity = other._capacity;
    _size = other._size;
    invariant();
};

/**
 * Destructor
 */
FloatVector::~FloatVector() noexcept
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
FloatVector::FloatVector(FloatVector&& other) noexcept
{
    _size = other._size;
    _capacity = other._capacity;
    _content = other._content;
    other._size = 0;
    other._capacity = 0;
    other._content = nullptr;
    invariant();
}

FloatVector& FloatVector::operator=(const FloatVector& other)
{
    if(_capacity < other.size())
    {
        FloatVector temp(other);
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
FloatVector& FloatVector::operator=(FloatVector&& other) noexcept
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
float& FloatVector::operator[] (size_t i)
{
    return _content[i];
}

/**
 * At function checking for out of range
 */
float& FloatVector::at(size_t i)
{
    if(i >= _size) throw std::out_of_range("Requested index out of range");
    return _content[i];
}

/**
 * Const subscript operator
 */
const float& FloatVector::operator[](size_t i) const
{
    return _content[i];
}

/**
 * Const At function checking for out of range
 */
const float& FloatVector::at(size_t i) const
{
    if(i >= _size) throw std::out_of_range("Requested index out of range");
    return _content[i];
}

/**
 * Return the current size, number of elements
 */
size_t FloatVector::size() const noexcept
{
    return _size;
}

/**
 * Change the total capacity to passed value
 */
void FloatVector::reserve(size_t n)
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
size_t FloatVector::capacity() const noexcept
{
    return _capacity;
}

/**
 * Changes capacity to current number of elements
 */
void FloatVector::shrink_to_fit()
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
void FloatVector::push_back(const T& c)
{
    if(_size >= _capacity)
    {
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
void FloatVector::push_back(T&& c)
{
    if(_size >= _capacity)
    {
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
    new(_content + _size) T(std::forward<T>(c));
    ++_size;
}

/**
 * Change capacity to passed capacity.
 */
void FloatVector::resize(size_t n)
{
    if(n > _capacity) // Doesn't fit? Make new memory
    {
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
FloatVector& FloatVector::operator+=(const FloatVector& other)
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

typename FloatVector::iterator FloatVector::begin() 
{ 
    return iterator(_content); 
}

typename FloatVector::iterator FloatVector::end() 
{ 
    return iterator(_content + _size); 
}

typename FloatVector::const_iterator FloatVector::begin() const
{ 
    return const_iterator(_content); 
}

typename FloatVector::const_iterator FloatVector::end() const
{ 
    return const_iterator(_content + _size); 
}

typename FloatVector::const_iterator FloatVector::cbegin() const 
{ 
    return const_iterator(_content); 
}

typename FloatVector::const_iterator FloatVector::cend() const 
{ 
    return const_iterator(_content + _size); 
}

typename FloatVector::reverse_iterator FloatVector::rbegin() 
{ 
    return reverse_iterator(end());
}

typename FloatVector::reverse_iterator FloatVector::rend()
{ 
    return reverse_iterator(begin());
}

typename FloatVector::const_reverse_iterator FloatVector::rbegin() const
{ 
    return const_reverse_iterator(end());
}

typename FloatVector::const_reverse_iterator FloatVector::rend() const
{ 
    return const_reverse_iterator(begin());
}

typename FloatVector::const_reverse_iterator FloatVector::crbegin() const 
{ 
    return const_reverse_iterator(cend());
}

typename FloatVector::const_reverse_iterator FloatVector::crend() const 
{ 
    return const_reverse_iterator(cbegin());
}

void FloatVector::swap(FloatVector& lhs, FloatVector& rhs) noexcept
{
    std::swap(lhs._size, rhs._size);
    std::swap(lhs._capacity, rhs._capacity);
    std::swap(lhs._content, rhs._content);
}

void FloatVector::swap(FloatVector& other) noexcept
{
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
    std::swap(_content, other._content);
}