//
// Created by danila on 26.04.19.
//

#include "graph.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <utility>

int graph::get_id(int name) const {
    return from_name_to_id.at(name);
}

int graph::get_name(int id) const {
    return from_id_to_name[id];
}

graph::graph(std::vector<std::vector<int>> _edges,
             std::vector<int> _from_id_to_name,
             std::unordered_map<int, int> _from_name_to_id):
    edges(std::move(_edges)),
    from_name_to_id(std::move(_from_name_to_id)),
    from_id_to_name(std::move(_from_id_to_name)){
    normalise();
}

graph::graph(std::vector<std::vector<int>> _edges,
             std::vector<int> _from_id_to_name):
    edges(std::move(_edges)),
    from_id_to_name(std::move(_from_id_to_name)) {
    for(size_t i=0;i<from_id_to_name.size();++i){
        from_name_to_id[from_id_to_name[i]] = i;
    }

    normalise();
}

graph graph::input_graph(const std::string &file_name) {
    std::ifstream in(file_name);

    if(!in.is_open()){
        std::cout<<"can't open file\n";
        return graph({}, {});
    }

    std::vector<std::vector<int>> res;
    std::vector<int> names;
    std::unordered_map<int, int> ids;

    int n;
    in>>n;
    res.reserve(n);
    names.resize(n);
    for(int i=0;i<n;++i){
        int m;
        in>>names[i]>>m;
        ids[names[i]] = i;
        std::vector<int> links;
        links.reserve(m);
        for(int j=0;j<m;++j){
            int t;
            in>>t;
            links.emplace_back(t);
        }
        res.emplace_back(links);
    }

    for(auto& link: res){
        for(auto& v:link){
            v = ids[v];
        }
    }

    return graph(res, names, ids);
}

bool graph::is_indirected() const {
    for(size_t i=0;i<edges.size();++i){
        for(size_t j =0; j<edges[i].size();++j){
            if(edges[i][j] >= edges.size())
                return false;
            bool was = false;
            for(int k=0;k<edges[edges[i][j]].size();++k){
                if(edges[edges[i][j]][k] == i){
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

graph graph::make_indirected() const {
    graph res(*this);
    for(size_t i=0;i<res.edges.size();++i){
        for(size_t j =0; j<res.edges[i].size();++j){
            if(res.edges[i][j] >= res.edges.size())
                throw std::exception();
            bool was = false;
            for(int k=0;k<res.edges[res.edges[i][j]].size();++k){
                if(res.edges[res.edges[i][j]][k] == i){
                    was = true;
                    break;
                }
            }
            if(!was){
                res.edges[res.edges[i][j]].emplace_back(i);
            }
        }
    }
    res.normalise();
    return res;
}

bool operator==(const graph &l, const graph &r) {
    return (l.edges==r.edges) && (l.from_name_to_id==r.from_name_to_id) &&
            (l.from_id_to_name == r.from_id_to_name);
}

graph graph::revert() const {
    std::vector<std::vector<int>> res(edges.size(), std::vector<int>());

    for(size_t i=0;i<edges.size();++i){
        for(size_t j=0;j<edges[i].size();++j){
            res[edges[i][j]].emplace_back(i);
        }
    }

    return graph(res, from_id_to_name, from_name_to_id);
}

void graph::normalise() {
    for(auto& it:edges){
        std::sort(it.begin(), it.end());
    }
}

std::vector<std::pair<int, int>> graph::get_edge_list() const {
    std::vector<std::pair<int, int>> res;

    for(size_t i=0;i<edges.size();++i){
        for(size_t j=0;j<edges[i].size();++j){
            res.emplace_back(std::make_pair(i,edges[i][j]));
        }
    }

    return res;
}

std::vector<std::vector<int>> graph::get_edge_mat() const {
    std::vector<std::vector<int>> res(edges.size(),
            std::vector<int>(edges.size(), 0));

    for(size_t i=0;i<edges.size();++i){
        for(size_t j=0;j<edges[i].size();++j){
            res[i][edges[i][j]] = 1;
        }
    }

    return res;
}

graph graph::decrease(const std::vector<int>& allowed) const
{
    std::unordered_map<int, int> nti;

    for(size_t i=0; i<allowed.size(); ++i){
        nti[allowed[i]] = i;
    }

    graph res({}, allowed, nti);
    res.edges.resize(allowed.size());

    for(size_t i=0; i< edges.size(); ++i){
        if(res.from_name_to_id.count(get_name(i))){
            for(size_t j=0; j<edges[i].size(); ++j)
            {
                if(res.from_name_to_id.count(get_name(edges[i][j])))
                {
                    res.edges[res.get_id(get_name(i))].emplace_back(res.get_id(get_name(edges[i][j])));
                }
            }
        }
    }

    return res;
}


