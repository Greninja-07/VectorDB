#pragma once

#include <any>
#include <string>
#include <unordered_map>
#include <vector>

struct Metadata
{
    std::unordered_map<std::string, std::any> values;
};

template <typename T>
struct VectorRecord
{
    int id{};
    std::vector<T> vector{};
    Metadata metadata{};

    size_t dimension() const
    {
        return vector.size();
    }
};