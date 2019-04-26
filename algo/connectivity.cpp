//
// Created by danila on 25.04.19.
//

#include "algorithms.hpp"

#include <algorithm>

std::vector<std::vector<int>> revert(const std::vector<std::vector<int>>& g){
    std::vector<std::vector<int>> res(g.size(), std::vector<int>());

    for(size_t i=0;i<g.size();++i){
        for(size_t j=0;j<g[i].size();++j){
            res[g[i][j]].emplace_back(i);
        }
    }

    return res;
}

void dfs_scc(const std::vector<std::vector<int>>& g, std::vector<int>& was,
            int v, std::vector<int>& res, int c){
    was[v] = c;
    for(auto&t:g[v]){
        if(was[t] != c){
            dfs_scc(g, was, t, res, c);
        }
    }
    res.emplace_back(v);
}

bool cmp(const std::vector<int> &l, const std::vector<int> &r){
    return l.size() > r.size();
}


std::vector<std::vector<int>> get_scc(const std::vector<std::vector<int>>& g){
    auto gr = revert(g);

    std::vector<int> top_sort;
    std::vector<int> was(g.size(), 0);

    for(size_t i=0;i<g.size();++i) {
        if (was[i] == 0) {
            dfs_scc(gr, was, i, top_sort, 1);
        }
    }

    std::vector<std::vector<int>> res;

    for(auto it=top_sort.rbegin();it!=top_sort.rend();++it) {
        if (was[*it] == 1) {
            std::vector<int> component;
            dfs_scc(g, was, *it, component, 2);
            res.emplace_back(component);
        }
    }

    std::sort(res.begin(), res.end(), cmp);

    return res;
}

void dfs_cc(const std::vector<std::vector<int>>& g, std::vector<int>& was,
        int v, int c){
    was[v] = c;
    for(auto&t:g[v]){
        if(was[t] == 0){
            dfs_cc(g, was, t, c);
        }
    }
}

std::vector<std::vector<int>> get_cc(const std::vector<std::vector<int>>& g){
    int c = 1;
    std::vector<int> col(g.size(),0);
    for(size_t i=0;i<g.size();++i){
        if(col[i] == 0){
            dfs_cc(g,col,i,c);
            ++c;
        }
    }

    std::vector<std::vector<int>> res(c-1, std::vector<int>());

    for(size_t i=0;i<g.size(); ++i){
        res[col[i]-1].emplace_back(i);
    }

    std::sort(res.begin(), res.end(), cmp);

    return res;
}
