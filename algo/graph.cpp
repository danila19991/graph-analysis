//
// Created by danila on 26.04.19.
//

#include "graph.hpp"

#include <fstream>
#include <iostream>
#include <utility>

int graph::get_id(int name) {
    return from_name_to_id[name];
}

int graph::get_name(int id) {
    return from_id_to_name[id];
}

graph::graph(std::vector<std::vector<int>> _edges,
             std::vector<int> _from_id_to_name,
             std::unordered_map<int, int> _from_name_to_id):
    edges(std::move(_edges)),
    from_name_to_id(std::move(_from_name_to_id)),
    from_id_to_name(std::move(_from_id_to_name)){

}

graph::graph(std::vector<std::vector<int>> _edges,
             std::vector<int> _from_id_to_name):
    edges(std::move(_edges)),
    from_id_to_name(std::move(_from_id_to_name)) {
    for(size_t i=0;i<from_id_to_name.size();++i){
        from_name_to_id[from_id_to_name[i]] = i;
    }
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


