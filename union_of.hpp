/*
    MIT License

    Copyright (c) 2020 Victoria Kabaeva

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
    DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
    OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
    OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include <type_traits>
#include <cstring>

template <typename A, typename B, typename... Ts> struct is_same_size
{
    static constexpr bool value = sizeof(A) == sizeof(B) && is_same_size<B, Ts...>::value;
};

template <typename A, typename B> struct is_same_size<A, B>
{
    static constexpr bool value = sizeof(A) == sizeof(B);
};

struct union_set_data_tag
{
};

template <typename T, typename... Ts> struct union_of;

template <typename X, typename... Ts> struct union_of : union_of<Ts...>
{
    static_assert(is_same_size<X, Ts...>::value);
    static_assert(std::is_pod_v<X>);

    using union_of<Ts...>::union_of;
    inline explicit union_of(const X &value) { *this = value; }

    inline explicit operator X *() const { return reinterpret_cast<X *>(this); }
    inline explicit operator X() const { return *reinterpret_cast<const X *>(this); }
    union_of<X, Ts...> &operator=(const X &obj)
    {
        *reinterpret_cast<X *>(this) = obj;
        return *this;
    }
};

template <typename T> struct union_of<T>
{
    static_assert(std::is_pod_v<T>);

    inline union_of() = default;
    inline explicit union_of(const T &value) { *this = value; }
    inline union_of(const void *ptr, union_set_data_tag) { set_data(ptr); }

    inline explicit operator T *() const { return reinterpret_cast<T *>(data); }
    inline explicit operator T() const { return *reinterpret_cast<const T *>(data); }

    inline void set_data(const void *ptr) { std::memcpy(data, ptr, sizeof(data)); }

    union_of<T> &operator=(const T &obj)
    {
        *reinterpret_cast<T *>(this) = obj;
        return *this;
    }

  private:
    unsigned char data[sizeof(T)]{};
};
