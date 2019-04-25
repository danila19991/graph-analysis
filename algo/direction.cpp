//
// Created by gusef on 24.04.2019.
//

#include "algorithms.hpp"


bool is_indirected(const std::vector<std::vector<int>>& g){
    for(size_t i=0;i<g.size();++i){
        for(size_t j =0; j<g[i].size();++j){
            if(g[i][j] >= g.size())
                return false;
            bool was = false;
            for(int k=0;k<g[g[i][j]].size();++k){
                if(g[g[i][j]][k] == i){
                    was = true;
                    break;
                }
            }
            if(!was){
                return false;
            }
        }
    }
    return true;
}

std::vector<std::vector<int>> make_indirected(std::vector<std::vector<int>> g){
    for(size_t i=0;i<g.size();++i){
        for(size_t j =0; j<g[i].size();++j){
            if(g[i][j] >= g.size())
                throw std::exception();
            bool was = false;
            for(int k=0;k<g[g[i][j]].size();++k){
                if(g[g[i][j]][k] == i){
                    was = true;
                    break;
                }
            }
            if(!was){
                g[g[i][j]].emplace_back(i);
            }
        }
    }
    return g;
}
