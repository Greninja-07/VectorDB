#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

#include "../include/vector_io.hpp"
#include "../include/flat_search.hpp"

int main()
{
    auto base_vectors = VectorStoreIO::read_vecs<float>("data/siftsmall_base.fvecs");
    auto query_vectors = VectorStoreIO::read_vecs<float>("data/siftsmall_query.fvecs");
    auto ground_truth = VectorStoreIO::read_vecs<int32_t>("data/siftsmall_groundtruth.ivecs");

    double total_recall = 0.0;

    for (std::size_t i = 0; i < query_vectors.size(); ++i)
    {
        const auto& query = query_vectors[i];
        const auto retrieved_ids = flat_search(query.vector, base_vectors, 100);
        const auto& truth = ground_truth[i].vector;

        int hits = 0;
        for (int id : retrieved_ids)
        {
            if (std::find(truth.begin(), truth.end(), id) != truth.end())
            {
                ++hits;
            }
        }

        total_recall += static_cast<double>(hits) / 100.0;
    }

    const double average_recall = total_recall / static_cast<double>(query_vectors.size());
    std::cout << average_recall << std::endl;
    return 0;
}
