//
// Created by gusef on 04.05.2019.
//

#include "../algo/algorithms.hpp"

#include <gtest/gtest.h>

TEST(test_degree_centrality, tree)
{
std::vector<std::vector<int>> e{
    {1},
    {0, 2},
    {1}
};
std::vector<int> t{0,1,2};
graph g(e,t);
auto res = degree_centrality(g);
ASSERT_EQ(res, std::vector<double>{0.5, 1, 0.5}) << "incorrect centrality";
}

TEST(test_closness_centrality, tree)
{
std::vector<std::vector<int>> e{
    {1},
    {0, 2},
    {1}
};
std::vector<int> t{0,1,2};
graph g(e,t);
auto res = closness_centrality(g);
ASSERT_EQ(res, std::vector<double>{2./3, 1, 2./3}) << "incorrect centrality";
}
