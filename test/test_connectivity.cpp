//
// Created by danila on 25.04.19.
//

#include "../algo/algorithms.hpp"

#include <gtest/gtest.h>

#include <string>

TEST(get_cc, without_edges){
    std::vector<std::vector<int>> e{
        {},
        {},
        {}
    };
    std::vector<int> t{0,1,2};
    graph g(e,t);
    auto res = get_cc(g);
    std::vector<int> was(3, 0);
    for(auto& t :res){
        ASSERT_EQ(1, t.size()) << "one element in each component";
        was[t[0]] += 1;
    }
    for(auto& t: was){
        ASSERT_EQ(1,t)<<"every vertex should be in list only once";
    }
}

TEST(get_cc, components_2){
    std::vector<std::vector<int>> e{
            {1},
            {0},
            {}
    };
    std::vector<int> t{0,1,2};
    graph g(e,t);
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
}

TEST(get_scc, without_edges){
    std::vector<std::vector<int>> e{
            {},
            {},
            {}
    };
    std::vector<int> t{0,1,2};
    graph g(e,t);
    auto res = get_scc(g);
    std::vector<int> was(3, 0);
    for(auto& t :res){
        ASSERT_EQ(1, t.size()) << "one element in each component";
        was[t[0]] += 1;
    }
    for(auto& t: was){
        ASSERT_EQ(1,t)<<"every vertex should be in list only once";
    }
}

TEST(get_scc, components_2){
    std::vector<std::vector<int>> e{
            {1},
            {0},
            {}
    };
    std::vector<int> t{0,1,2};
    graph g(e,t);
    auto res = get_scc(g);
    std::vector<int> was(3, 0);
    for(auto& t :res){
        for(auto& u:t){
            was[u] += 1;
        }
    }
    ASSERT_EQ(res.size(), 2) << "need 2 component";
    ASSERT_EQ(res[1].size(), 1) << "in 2 component only 1 vertex";
    ASSERT_EQ(res[1][0], 2) << "in 2 component vertex number 2";
    for(auto& t: was){
        ASSERT_EQ(1,t)<<"every vertex should be in list only once";
    }
}

TEST(get_scc, components_2_cycles){
    std::vector<std::vector<int>> e{
            {1, 2},
            {0, 3},
            {3},
            {4},
            {2}
    };
    std::vector<int> t{0,1,2};
    graph g(e,t);
    auto res = get_scc(g);
    std::vector<int> was(3, 0);
    for(auto& t :res){
        for(auto& u:t){
            was[u] += 1;
        }
    }
    if((res[1] !=  std::vector<int>{0, 1})&&(res[1] != std::vector<int>{1, 0})){
        std::stringstream ss;
        for (auto& it:res[1]) {
            ss << it << " ";
        }

        ss << "not 0 and 1 vertex";

        FAIL() << ss.str();
    }
    for(auto& t: was){
        ASSERT_EQ(1,t)<<"every vertex should be in list only once";
    }
}

TEST(get_scc, components_2_cycle_and_vertex){
    std::vector<std::vector<int>> e{
            {1, 2, 3},
            {2},
            {3},
            {1}
    };
    std::vector<int> t{0,1,2};
    graph g(e,t);
    auto res = get_scc(g);
    std::vector<int> was(3, 0);
    for(auto& t :res){
        for(auto& u:t){
            was[u] += 1;
        }
    }
    ASSERT_EQ(res.size(), 2) << "need 2 component";
    ASSERT_EQ(res[1].size(), 1) << "in 2 component only 1 vertex";
    ASSERT_EQ(res[1][0], 0) << "in 2 component vertex number 0";
    for(auto& t: was){
        ASSERT_EQ(1,t)<<"every vertex should be in list only once";
    }
}

TEST(get_scc, components_2_vertex_and_cycle){
    std::vector<std::vector<int>> e{
            {1, 3},
            {2, 3},
            {0, 3},
            {}
    };
    std::vector<int> t{0,1,2};
    graph g(e,t);
    auto res = get_scc(g);
    std::vector<int> was(3, 0);
    for(auto& t :res){
        for(auto& u:t){
            was[u] += 1;
        }
    }
    ASSERT_EQ(res.size(), 2) << "need 2 component";
    ASSERT_EQ(res[1].size(), 1) << "in 2 component only 1 vertex";
    ASSERT_EQ(res[1][0], 3) << "in 2 component vertex number 0";
    for(auto& t: was){
        ASSERT_EQ(1,t)<<"every vertex should be in list only once";
    }
}
