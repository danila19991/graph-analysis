//
// Created by gusef on 24.04.2019.
//

#include "algo/algorithms.hpp"
#include "algo/graph.hpp"

#include <iostream>
#include <fstream>

void output_graph(const std::string& file_name,
                  const std::vector<std::vector<int>>& vertexes,
                  const graph& g){
    std::ofstream out(file_name);

    if(!out.is_open()){
        std::cout<<"can't open file\n";
        return;
    }

    out<<vertexes.size()<<'\n';
    for(auto& t:vertexes){
        out<<t.size();
        for(auto& e:t){
            out<<' '<<g.get_name(e);
        }
        out<<'\n';
    }
}

void first_task(const graph& g){
    if(g.is_indirected())
        std::cout<<"graph is indireted\n";
    else
        std::cout<<"graph is directe\n";

    auto scc = get_scc(g.edges);

    output_graph("../data/scc.txt", scc, g);

    auto cc = get_scc(g.make_indirected().edges);

    output_graph("../data/cc.txt", cc, g);
}

int main(int argc, char* argv[]){
    auto g = graph::input_graph("../data/edges.txt");

    first_task(g);


    std::cout<<"hello world\n"<<g.edges.size();
}
