//
// Created by gusef on 24.04.2019.
//

#include "algorithms.hpp"

#include <fstream>

#include <iostream>

std::vector<std::vector<int>> input_graph(const std::string& file_name){
    std::ifstream in(file_name);

    std::vector<std::vector<int>> res;

    if(!in.is_open()){
        std::cout<<"can't open file\n";
        return res;
    }

    int n;
    in>>n;
    res.reserve(n);
    for(int i=0;i<n;++i){
        int m;
        in>>m;
        std::vector<int> links;
        links.reserve(m);
        for(int j=0;j<m;++j){
            int t;
            in>>t;
            links.emplace_back(t);
        }
        res.emplace_back(links);
    }

    return res;
}
