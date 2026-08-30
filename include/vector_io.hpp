#pragma once

#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "types.hpp"

class VectorStoreIO
{
public:
    template <typename T>
    static std::vector<VectorRecord<T>> read_vecs(const std::string& file_path)
    {
        std::ifstream file(file_path, std::ios::binary);
        if (!file)
        {
            throw std::runtime_error("Failed to open vector file: " + file_path);
        }

        std::vector<VectorRecord<T>> records;
        int id_counter = 0;

        while (true)
        {
            int32_t dim = 0;
            file.read(reinterpret_cast<char*>(&dim), sizeof(dim));

            if (!file || file.eof())
            {
                break;
            }

            VectorRecord<T> record;
            record.id = id_counter++;
            record.vector.resize(static_cast<std::size_t>(dim));

            file.read(reinterpret_cast<char*>(record.vector.data()), dim * static_cast<int32_t>(sizeof(T)));
            records.push_back(record);
        }

        return records;
    }
};
