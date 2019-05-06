//
// Created by danila on 26.04.19.
//

//
// Created by gusef on 24.04.2019.
//

#include <gtest/gtest.h>

#include "../algo/graph.hpp"
#include "test_utils.h"

TEST(test_is_indirect, empty_graph)
{
    std::vector<std::vector<int>> e;
    std::vector<int> t;
    graph g(e,t);
    ASSERT_TRUE(g.is_indirected()) << "empty graph is indirect";
}

TEST(test_is_indirect, full_graph)
{
    std::vector<std::vector<int>> e{
            {1, 2},
            {0, 2},
            {0, 1}
    };
    std::vector<int> t{0,1,2};
    graph g(e,t);
    ASSERT_TRUE(g.is_indirected()) << "full graph is indirect";
}

TEST(test_is_indirect, indirect_graph)
{
    std::vector<std::vector<int>> e{
            {1},
            {0},
            {3},
            {2}
    };
    std::vector<int> t{0,1,2,3};
    graph g(e,t);
    ASSERT_TRUE(g.is_indirected()) << "two indirect edge graph is indirect";
}

TEST(test_is_indirect, direct_graph)
{
    std::vector<std::vector<int>> e{
            {1},
            {2},
            {0}
    };
    std::vector<int> t{0,1,2};
    graph g(e,t);
    ASSERT_FALSE(g.is_indirected()) << "direct k3";
}

TEST(test_make_indirect, empty_graph)
{
    std::vector<std::vector<int>> e;
    std::vector<int> t;
    graph g(e,t);
    auto actual = g.make_indirected();
    ASSERT_EQ(g,actual) << "empty graph is indirect";
}

TEST(test_make_indirect, full_graph)
{
    std::vector<std::vector<int>> e{
            {1, 2},
            {0, 2},
            {0, 1}
    };
    std::vector<int> t{0,1,2};
    graph g(e,t);
    auto actual = g.make_indirected();
    ASSERT_TRUE(actual.is_indirected()) << "full graph is indirect";
}

TEST(test_make_indirect, indirect_graph)
{
    std::vector<std::vector<int>> e{
            {1},
            {0},
            {3},
            {2}
    };
    std::vector<int> t{0,1,2,3};
    graph g(e,t);
    auto actual = g.make_indirected();
    ASSERT_TRUE(actual.is_indirected()) << "two indirect edge graph is indirect";
}

TEST(test_make_indirect, direct_graph)
{
    std::vector<std::vector<int>> e{
            {1},
            {2},
            {0}
    };
    std::vector<int> t{0,1,2};
    graph g(e,t);
    auto actual = g.make_indirected();
    ASSERT_TRUE(actual.is_indirected()) << "direct k3";
}

TEST(test_revert, emty_graph)
{
    std::vector<std::vector<int>> e{};
    std::vector<int> t{};
    graph g(e,t);
    auto actual = g.revert();
    ASSERT_EQ(actual, g) << "empty reverted graph is empty";
}

TEST(test_revert, direct_graph)
{
    std::vector<std::vector<int>> e{
            {1},
            {2},
            {0}
    };
    std::vector<std::vector<int>> e2{
            {2},
            {0},
            {1}
    };
    std::stringstream ss;
    std::vector<int> t{0,1,2};
    graph g(e,t);
    auto actual = g.revert();
    graph expected(e2, t);
    ss << actual.edges << " ";
    ss << expected.edges << "incorrect reverted graph for direct one";
    ASSERT_EQ(actual, expected) << ss.str();
}

TEST(test_revert, indirect_graph)
{
    std::vector<std::vector<int>> e{
            {1},
            {0}
    };
    std::stringstream ss;
    std::vector<int> t{0,1};
    graph g(e,t);
    auto actual = g.revert();
    ss << actual.edges << " ";
    ss << g.edges << "incorrect reverted graph for direct one";
    ASSERT_EQ(actual, g) << "reverted direct k3 is k3";
}

TEST(test_decrease, tree)
{
std::vector<std::vector<int>> e{
    {1},
    {0, 2},
    {1}
};
std::vector<int> t{0,1,2};
std::vector<int> k{0,2};
graph g(e,t);
auto res = g.decrease(k);
graph need({}, k);
ASSERT_EQ(res, need) << "incorrect centrality";
}
