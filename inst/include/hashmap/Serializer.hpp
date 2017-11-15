// vim: set softtabstop=4:expandtab:number:syntax on:wildmenu:showmatch
//
// Serializer.hpp
//
// Copyright (C) 2017 Nathan Russell
//
// This file is part of hashmap.
//
// hashmap is free software: you can redistribute it and/or
// modify it under the terms of the MIT License.
//
// hashmap is provided "as is", without warranty of any kind,
// express or implied, including but not limited to the
// warranties of merchantability, fitness for a particular
// purpose and noninfringement.
//
// You should have received a copy of the MIT License
// along with hashmap. If not, see
// <https://opensource.org/licenses/MIT>.

#ifndef hashmap__Serializer__hpp
#define hashmap__Serializer__hpp

#include <cstdio>
#include <new>
#include <utility>
#include <string>

namespace hashmap {

struct Serializer
{
    // write T
    template <typename T>
    bool operator()(std::FILE* fp, const T& value)
    {
        return std::fwrite((const void*)&value, sizeof(value), 1, fp) == 1;
    }

    // read T
    template <typename T>
    bool operator()(std::FILE* fp, T* value)
    {
        return std::fread((void*)value, sizeof(*value), 1, fp) == 1;
    }

    // write std::string
    bool operator()(std::FILE* fp, const std::string& value)
    {
        const std::size_t size = value.size();
        return (*this)(fp, size) &&
            std::fwrite(value.c_str(), size, 1, fp) == 1;
    }

    // read std::string
    bool operator()(std::FILE* fp, std::string* value)
    {
        std::size_t size;
        if (!(*this)(fp, &size)) {
            return false;
        }

        char* buf = new char[size];
        if (std::fread(buf, size, 1, fp) != 1) {
            delete[] buf;
            return false;
        }

        new (value) std::string(buf, (std::size_t)size);
        delete[] buf;

        return true;
    }

    // write std::pair<const K, V>
    template <typename K, typename V>
    bool operator()(std::FILE* fp, const std::pair<const K, V>& value)
    {
        return (*this)(fp, value.first) &&
            (*this)(fp, value.second);
    }

    // read std::pair<const K, V>
    template <typename K, typename V>
    bool operator()(std::FILE* fp, std::pair<const K, V>* value)
    {
        return (*this)(fp, (K*)&value->first) &&
            (*this)(fp, &value->second);
    }
};

} // hashmap

#endif // hashmap__Serializer__hpp
