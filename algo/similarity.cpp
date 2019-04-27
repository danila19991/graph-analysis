//
// Created by danila on 27.04.19.
//

#include <cmath>
#include "algorithms.hpp"



mat common_neighbors(const graph& g){
    mat res(g.edges.size(), std::vector<double >(g.edges.size(), 0));
    for(size_t i=0;i<g.edges.size(); ++i){
        for(size_t j=0;j<g.edges.size();++j){
            res[i][j] = intersection(g.edges[i], g.edges[j]).size();
        }
    }
    return res;
}

mat jaccard_metric(const graph& g){
    mat res(g.edges.size(), std::vector<double >(g.edges.size(), 0));
    for(size_t i=0;i<g.edges.size(); ++i){
        for(size_t j=0;j<g.edges.size();++j){
            res[i][j] = static_cast<double>(
                            intersection(g.edges[i], g.edges[j]).size())/
                    merge(g.edges[i], g.edges[j]).size();
        }
    }
    return res;
}


mat adamic_adar_metric(const graph& g){
    mat res(g.edges.size(), std::vector<double >(g.edges.size(), 0));
    for(size_t i=0;i<g.edges.size(); ++i){
        for(size_t j=0;j<g.edges.size();++j){
            if(i!=j){
                auto list = intersection(g.edges[i], g.edges[j]);
                for(auto& it: list){
                    res[i][j] += 1/log(g.edges[it].size());
                }
            }
        }
    }
    return res;
}

mat preferential_attachment(const graph& g){
    mat res(g.edges.size(), std::vector<double >(g.edges.size(), 0));
    for(size_t i=0;i<g.edges.size(); ++i){
        for(size_t j=0;j<g.edges.size();++j){
            res[i][j] = g.edges[i].size()*g.edges[j].size();
        }
    }
    return res;
}

std::vector<int> intersection(const std::vector<int> &l,
        const std::vector<int> &r){
    std::vector<int> res;
    auto it1 = l.begin();
    auto it2 = r.begin();

    while(it1 != l.end() && it2 != r.end()){
        if(*it1 == *it2){
            res.emplace_back(*it1);
            ++it1;
            ++it2;
            continue;
        }
        if(*it1 < *it2){
            ++it1;
        }
        else{
            ++it2;
        }
    }

    return res;
}

std::vector<int> merge(const std::vector<int> &l, const std::vector<int> &r){
    std::vector<int> res;
    auto it1 = l.begin();
    auto it2 = r.begin();

    while(it1 != l.end() && it2 != r.end()){
        if(*it1 == *it2){
            res.emplace_back(*it1);
            ++it1;
            ++it2;
            continue;
        }
        if(*it1 < *it2){
            res.emplace_back(*it1);
            ++it1;
        }
        else{
            res.emplace_back(*it2);
            ++it2;
        }
    }

    while(it1 != l.end()){
        res.emplace_back(*it1);
        ++it1;
    }

    while(it2 != r.end()){
        res.emplace_back(*it2);
        ++it2;
    }

    return res;
}
