#ifndef ARRAY_TPP
#define ARRAY_TPP

template <typename T>
Array<T>::Array() : _arr(NULL), _size(0)
{
}

template <typename T>
Array<T>::Array(unsigned int i) : _arr(new T[i]()), _size(i)
{
}

template <typename T>
Array<T>::Array(Array const &other) : _arr(new T[other._size]), _size(other._size)
{
    for (unsigned int i = 0; i < _size; i++)
        _arr[i] = other._arr[i];
}

template <typename T>
Array<T>::~Array()
{
    delete[] _arr;
}

template <typename T>
Array<T> &Array<T>::operator=(Array const &other)
{
    if (this != &other)
    {
        T *newArr = new T[other._size];
        try
        {
            for (unsigned int i = 0; i < other._size; i++)
                newArr[i] = other._arr[i];
        }
        catch (...)
        {
            delete[] newArr;
            throw;
        }
        delete[] _arr;
        _arr = newArr;
        _size = other._size;
    }
    return (*this);
}

template <typename T>
T &Array<T>::operator[](unsigned int i)
{
    if (i >= _size)
        throw OutOfRangeException();
    return (_arr[i]);
}

template <typename T>
T const &Array<T>::operator[](unsigned int i) const
{
    if (i >= _size)
        throw OutOfRangeException();
    return (_arr[i]);
}

template <typename T>
unsigned int Array<T>::size() const
{
    return (_size);
}

template <typename T>
const char *Array<T>::OutOfRangeException::what() const throw()
{
    return ("Index out of bounds");
}

#endif
