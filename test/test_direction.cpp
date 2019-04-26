//
// Created by gusef on 24.04.2019.
//

#include <gtest/gtest.h>

#include "../algo/algorithms.hpp"

TEST(test_is_indirect, empty_graph)
{
    std::vector<std::vector<int>> g;
    ASSERT_TRUE(is_indirected(g)) << "empty graph is indirect";
}

TEST(test_is_indirect, full_graph)
{
    std::vector<std::vector<int>> g{
        {1, 2},
        {0, 2},
        {0, 1}
    };
    ASSERT_TRUE(is_indirected(g)) << "full graph is indirect";
}

TEST(test_is_indirect, indirect_graph)
{
    std::vector<std::vector<int>> g{
        {1},
        {0},
        {3},
        {2}
    };
    ASSERT_TRUE(is_indirected(g)) << "two indirect edge graph is indirect";
}

TEST(test_is_indirect, direct_graph)
{
    std::vector<std::vector<int>> g{
        {1},
        {2},
        {0}
    };
    ASSERT_FALSE(is_indirected(g)) << "direct k3";
}

TEST(test_make_indirect, empty_graph)
{
    std::vector<std::vector<int>> g;
    auto t = make_indirected(g);
    ASSERT_EQ(g,t) << "empty graph is indirect";
}

TEST(test_make_indirect, full_graph)
{
    std::vector<std::vector<int>> g{
        {1, 2},
        {0, 2},
        {0, 1}
    };
    auto t = make_indirected(g);
    ASSERT_TRUE(is_indirected(t)) << "full graph is indirect";
}

TEST(test_make_indirect, indirect_graph)
{
    std::vector<std::vector<int>> g{
        {1},
        {0},
        {3},
        {2}
    };
    auto t = make_indirected(g);
    ASSERT_TRUE(is_indirected(t)) << "two indirect edge graph is indirect";
}

TEST(test_make_indirect, direct_graph)
{
    std::vector<std::vector<int>> g{
        {1},
        {2},
        {0}
    };
    auto t = make_indirected(g);
    ASSERT_TRUE(is_indirected(t)) << "direct k3";
}
