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

void write_csv(const std::string& file_name, const mat& values, const graph& g){
    std::ofstream out(file_name);

    if(!out.is_open()){
        std::cout<<"can't open file\n";
        return;
    }

    for(size_t i=0;i<g.edges.size();++i){
        if(i!=0){
            out<<',';
        }
        out<<g.get_name(i);
    }

    for(size_t i=0;i<values.size(); ++i){
        out<<'\n';
        for(size_t j=0;j<values[j].size();++j){
            if(j!=0){
                out<<',';
            }
            out<<values[i][j];
        }
    }

    out.flags();
}

void first_task(const graph& g){
    if(g.is_indirected())
        std::cout<<"graph is indireted\n";
    else
        std::cout<<"graph is directe\n";

    auto scc = get_scc(g);

    output_graph("../data/scc.txt", scc, g);

    auto cc = get_cc(g);

    output_graph("../data/cc.txt", cc, g);
}

void second_task(const graph& g, const std::string& file_name){
    std::ofstream out(file_name);

    if(!out.is_open()){
        std::cout<<"can't open file\n";
        return;
    }

    auto d = get_all_distance(g);

    out<<"raius: "<<get_radius(d)<<'\n';
    out<<"diametr: "<<get_diametr(d)<<'\n';

    auto q = get_center(d);
    out<<"center: ["<<g.get_name(q[0]);
    for(size_t i=1; i<q.size();++i){
        out<<", "<<g.get_name(q[i]);
    }
    out<<"]\n";
    auto w = get_periphery(d);
    out<<"periphery: ["<<g.get_name(w[0]);
    for(size_t i=1; i<w.size();++i){
        out<<", "<<g.get_name(w[i]);
    }
    out<<"]\n";
    out<<"average: "<<get_average_distance(d)<<'\n';

}

void third_task(const graph& g){

    auto m1 = common_neighbors(g);

    write_csv("../data/common_neighbors.csv", m1, g);

    auto m2 = jaccard_metric(g);

    write_csv("../data/jaccard_metric.csv", m2, g);

    auto m3 = adamic_adar_metric(g);

    write_csv("../data/adamic_adar_metric.csv", m3, g);

    auto m4 = preferential_attachment(g);

    write_csv("../data/preferential_attachment.csv", m4, g);
}

int main(int argc, char* argv[]){
    auto g = graph::input_graph("../data/edges2.txt");

    //first_task(g);

    g = g.make_indirected();

    //second_task(g, "../data/res2.txt");
    third_task(g);

    std::cout<<"hello world\n"<<g.edges.size();
}
