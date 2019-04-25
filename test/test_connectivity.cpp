//
// Created by danila on 25.04.19.
//

#include <gtest/gtest.h>

#include "../algo/algorithms.hpp"

TEST(get_cc, without_edges){
    std::vector<std::vector<int>> g{
        {},
        {},
        {}
    };
    auto res = get_cc(g);
    std::vector<int> was(3, 0);
    for(auto& t :res){
        ASSERT_EQ(1, t.size()) << "one element in each component";
        was[t[0]] += 1;
    }
    for(auto& t: was){
        ASSERT_EQ(1,t)<<"every vertex should be in list only once";
    }
    ASSERT_TRUE(is_indirected(g)) << "empty graph is indirect";
}

TEST(get_cc, components_2){
    std::vector<std::vector<int>> g{
            {1},
            {0},
            {}
    };
    auto res = get_cc(g);
    std::vector<int> was(3, 0);
    for(auto& t :res){
        for(auto& u:t){
            was[u] += 1;
        }
    }
    ASSERT_EQ(res[1], std::vector<int>{2}) << "in 2 component only 2 vertex";
    for(auto& t: was){
        ASSERT_EQ(1,t)<<"every vertex should be in list only once";
    }
    ASSERT_TRUE(is_indirected(g)) << "empty graph is indirect";
}

TEST(get_scc, without_edges){
    std::vector<std::vector<int>> g{
            {},
            {},
            {}
    };
    auto res = get_scc(g);
    std::vector<int> was(3, 0);
    for(auto& t :res){
        ASSERT_EQ(1, t.size()) << "one element in each component";
        was[t[0]] += 1;
    }
    for(auto& t: was){
        ASSERT_EQ(1,t)<<"every vertex should be in list only once";
    }
    ASSERT_TRUE(is_indirected(g)) << "empty graph is indirect";
}

TEST(get_scc, components_2){
    std::vector<std::vector<int>> g{
            {1},
            {0},
            {}
    };
    auto res = get_cc(g);
    std::vector<int> was(3, 0);
    for(auto& t :res){
        for(auto& u:t){
            was[u] += 1;
        }
    }
    ASSERT_EQ(res[1], std::vector<int>{2}) << "in 2 component only 2 vertex";
    for(auto& t: was){
        ASSERT_EQ(1,t)<<"every vertex should be in list only once";
    }
    ASSERT_TRUE(is_indirected(g)) << "empty graph is indirect";
}

TEST(get_scc, components_2_cycles){
    std::vector<std::vector<int>> g{
            {1, 2},
            {0, 3},
            {3},
            {4},
            {2}
    };
    auto res = get_cc(g);
    std::vector<int> was(3, 0);
    for(auto& t :res){
        for(auto& u:t){
            was[u] += 1;
        }
    }
    const bool is_second_correct = (res[1] ==  std::vector<int>{2, 3}) ||
            (res[1] ==  std::vector<int>{3, 2});
    ASSERT_TRUE(is_second_correct) << "in 2 component 2 ans 3 vertex";
    for(auto& t: was){
        ASSERT_EQ(1,t)<<"every vertex should be in list only once";
    }
    ASSERT_TRUE(is_indirected(g)) << "empty graph is indirect";
}
