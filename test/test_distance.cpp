//
// Created by danila on 26.04.19.
//

#include "../algo/algorithms.hpp"

#include <gtest/gtest.h>

#include <string>

TEST(get_all_distance, tree_3){
    std::vector<std::vector<int>> e{
            {1},
            {0, 2},
            {1}
    };
    std::vector<int> t{0,1,2};
    graph g(e,t);
    auto res = get_all_distance(g);
    dist_mat expected{
            {0, 1, 2},
            {1, 0 ,1},
            {2, 1, 0}
    };
    std::vector<int> was(3, 0);
    ASSERT_EQ(res, expected) << "incorrect distance";
}

TEST(get_radius, tree_3){
    dist_mat d{
            {0, 1, 2},
            {1, 0 ,1},
            {2, 1, 0}
    };
    ASSERT_EQ(get_radius(d), 1) << "incorrect radius";
}

TEST(get_diametr, tree_3){
    dist_mat d{
            {0, 1, 2},
            {1, 0 ,1},
            {2, 1, 0}
    };
    ASSERT_EQ(get_diametr(d), 2) << "incorrect diametr";
}

TEST(get_center, tree_3){
    dist_mat d{
            {0, 1, 2},
            {1, 0 ,1},
            {2, 1, 0}
    };
    ASSERT_EQ(get_center(d), std::vector<int>{1}) << "incorrect center";
}

TEST(get_periphery, tree_3){
    dist_mat d{
            {0, 1, 2},
            {1, 0 ,1},
            {2, 1, 0}
    };
    std::vector<int> was(3,0);

    auto res = get_periphery(d);

    for(auto& it: res){
        was[it] += 1;
    }

    ASSERT_EQ(was, std::vector<int>({1, 0, 1})) << "incorrect periphery";
}

TEST(get_average_distance, tree_3){
    dist_mat d{
            {0, 1, 2},
            {1, 0 ,1},
            {2, 1, 0}
    };
    ASSERT_FLOAT_EQ(get_average_distance(d), 8./6) <<
        "incorrect average distance";
}
