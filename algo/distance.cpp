//
// Created by danila on 26.04.19.
//

#include "algorithms.hpp"

dist_mat get_all_distance(const graph& g){
    std::vector<std::vector<int>> d(g.edges.size(),
                                    std::vector<int>(g.edges.size(),
                                            g.edges.size()));

    for(size_t i=0;i<g.edges.size(); ++i){
        d[i][i] = 0;
    }

    for(size_t i=0;i<g.edges.size(); ++i){
        for(size_t j=0;j<g.edges[i].size();++j){
            d[i][g.edges[i][j]] = 1;
        }
    }

    for(size_t k=0;k<g.edges.size();++k){
        for(size_t i=0;i<g.edges.size();++i){
            for(size_t j=0; j<g.edges.size();++j){
                d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }

    return d;
}

int get_max(const std::vector<int>& val){
    int res = val[0];
    for(auto& it:val){
        res = std::max(res,it);
    }
    return res;
}

int get_radius(const dist_mat& d){
    int res = get_max(d[0]);
    for(auto& it: d){
        res = std::min(res, get_max(it));
    }
    return res;
}

int get_diametr(const dist_mat& d){
    int res = get_max(d[0]);
    for(auto& it: d){
        res = std::max(res, get_max(it));
    }
    return res;
}

std::vector<int> get_center(const dist_mat& d){
    int r = get_radius(d);

    std::vector<int> res;

    for(size_t i=0;i<d.size();++i){
        if(get_max(d[i]) == r){
            res.emplace_back(i);
        }
    }

    return res;
}

std::vector<int> get_periphery(const dist_mat& d){
    int r = get_diametr(d);

    std::vector<int> res;

    for(size_t i=0;i<d.size();++i){
        if(get_max(d[i]) == r){
            res.emplace_back(i);
        }
    }

    return res;
}

#include <iostream>

double get_average_distance(const dist_mat& d){
    double s=0, k=0;

    for(size_t i=0;i<d.size();++i){
        for(size_t j=0;j<d[i].size();++j){
            if(i!=j){
                s += d[i][j];
                k += 1;
            }
        }
    }

    return s/k;
}
