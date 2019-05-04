//
// Created by danila on 27.04.19.
//

#include <gtest/gtest.h>

#include "../algo/algorithms.hpp"
#include "test_utils.h"

#include <math.h>

TEST(test_common_neighbors, empty_graph)
{
    std::vector<std::vector<int>> e;
    std::vector<int> t;
    graph g(e,t);
    auto res = common_neighbors(g);
    ASSERT_EQ(res, mat{}) << "empty graph is indirect";
}

TEST(test_common_neighbors, tree)
{
    std::vector<std::vector<int>> e{
            {1},
            {0, 2},
            {1}
    };
    std::vector<int> t{0,1,2};
    graph g(e,t);
    auto res = common_neighbors(g);
    ASSERT_EQ(res, mat({{1, 0, 1},{0, 2, 0},{1, 0, 1}})) << "similarity is incorrect";
}

TEST(test_jaccard_metric, tree)
{
    std::vector<std::vector<int>> e{
            {1},
            {0, 2},
            {1}
    };
    std::vector<int> t{0,1,2};
    graph g(e,t);
    auto res = jaccard_metric(g);
    ASSERT_EQ(res, mat({{1, 0, 1},{0, 1, 0},{1, 0, 1}})) << "empty graph is indirect";
}

TEST(test_adamic_adar_metric, tree)
{
    std::vector<std::vector<int>> e{
            {1},
            {0, 2},
            {1}
    };
    std::vector<int> t{0,1,2};
    graph g(e,t);
    auto res = adamic_adar_metric(g);
    ASSERT_EQ(res, mat({{0, 0, 1./log(2.)},{0, 0, 0},{1./log(2.), 0, 0}})) << "empty graph is indirect";
}

TEST(test_preferential_attachment, tree)
{
    std::vector<std::vector<int>> e{
            {1},
            {0, 2},
            {1}
    };
    std::vector<int> t{0,1,2};
    graph g(e,t);
    auto res = preferential_attachment(g);
    ASSERT_EQ(res, mat({{1, 2, 1},{2, 4, 2},{1, 2, 1}})) << "empty graph is indirect";
}

TEST(test_intersection, empty)
{
    std::vector<int> e;
    std::vector<int> t;
    std::vector<int> expected;
    auto res = intersection(e, t);
    ASSERT_EQ(res, expected) << "not correct intersection";
}

TEST(test_intersection, empty_intersection)
{
    std::vector<int> e{0,2,4};
    std::vector<int> t{1,3,5};
    std::vector<int> expected;
    auto res = intersection(e, t);
    ASSERT_EQ(res, expected) << "not correct intersection";
}

TEST(test_intersection, not_empty_intesection)
{
    std::vector<int> e{0,1,3,5};
    std::vector<int> t{1,2,3,4,6};
    std::vector<int> expected{1,3};
    auto res = intersection(e, t);
    ASSERT_EQ(res, expected) << "not correct intersection";
}

TEST(test_intersection, equal_vectors)
{
    std::vector<int> e{1,2,3};
    std::vector<int> t{1,2,3};
    std::vector<int> expected{1,2,3};
    auto res = intersection(e, t);
    ASSERT_EQ(res, expected) << "not correct intersection";
}

TEST(test_merge, empty)
{
    std::vector<int> e;
    std::vector<int> t;
    std::vector<int> expected;
    auto res = merge(e, t);
    ASSERT_EQ(res, expected) << "not correct intersection";
}

TEST(test_merge, empty_intersection)
{
    std::vector<int> e{0,2,4};
    std::vector<int> t{1,3,5};
    std::vector<int> expected{0,1,2,3,4,5};
    auto res = merge(e, t);
    ASSERT_EQ(res, expected) << "not correct intersection";
}

TEST(test_merge, not_empty_intesection)
{
    std::vector<int> e{0,1,3,5};
    std::vector<int> t{1,2,3,4,6};
    std::vector<int> expected{0,1,2,3,4,5,6};
    auto res = merge(e, t);
    ASSERT_EQ(res, expected) << "not correct intersection";
}

TEST(test_merge, equal_vectors)
{
    std::vector<int> e{1,2,3};
    std::vector<int> t{1,2,3};
    std::vector<int> expected{1,2,3};
    auto res = merge(e, t);
    ASSERT_EQ(res, expected) << "not correct intersection";
}
