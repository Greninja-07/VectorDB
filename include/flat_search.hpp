#pragma once

#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

#include "types.hpp"

inline float squared_l2_distance(const std::vector<float>& a, const std::vector<float>& b)
{
    const std::size_t size = std::min(a.size(), b.size());
    float sum = 0.0f;

    for (std::size_t i = 0; i < size; ++i)
    {
        const float diff = a[i] - b[i];
        sum += diff * diff;
    }

    if (a.size() > b.size())
    {
        for (std::size_t i = size; i < a.size(); ++i)
        {
            const float diff = a[i];
            sum += diff * diff;
        }
    }
    else if (b.size() > a.size())
    {
        for (std::size_t i = size; i < b.size(); ++i)
        {
            const float diff = b[i];
            sum += diff * diff;
        }
    }

    return sum;
}

inline std::vector<int> flat_search(const std::vector<float>& query,
                                   const std::vector<VectorRecord<float>>& base_vectors,
                                   size_t k)
{
    std::priority_queue<std::pair<float, int>> pq;

    for (const auto& record : base_vectors)
    {
        const float distance = squared_l2_distance(query, record.vector);

        if (pq.size() < k)
        {
            pq.emplace(distance, record.id);
        }
        else if (distance < pq.top().first)
        {
            pq.pop();
            pq.emplace(distance, record.id);
        }
    }

    std::vector<int> result;
    result.reserve(pq.size());

    while (!pq.empty())
    {
        result.push_back(pq.top().second);
        pq.pop();
    }

    std::reverse(result.begin(), result.end());
    return result;
}
