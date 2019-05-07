//
// Created by gusef on 24.04.2019.
//

#include "algo/algorithms.hpp"
#include "algo/graph.hpp"
#include "graffic/graffic.h"

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
    for(size_t i=0;i<vertexes.size(); ++i){
        out<<g.get_name(i)<<' '<<vertexes[i].size();
        for(auto& e:vertexes[i]){
            out<<' '<<g.get_name(e);
        }
        out<<'\n';
    }
}

template <typename T>
void write_csv(const std::string& file_name,
        const std::vector<std::vector<T>>& values, const graph& g){
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
        for(size_t j=0;j<values[i].size();++j){
            if(j!=0){
                out<<',';
            }
            out<<values[i][j];
        }
    }

    out.flush();
}

void write_vec(const std::string& file_name, const std::vector<double>& values,
        const graph& g){
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
    out<<'\n';

    for(size_t i=0;i<values.size(); ++i){
        if(i!=0){
            out<<',';
        }
        out<<values[i];
    }

    out.flush();

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

void third_task(const graph& g, bool with_show = false){

    auto m1 = common_neighbors(g);

    if(with_show) {
        show_matrix(m1, "common_neighbors");
    }

    write_csv("../data/common_neighbors.csv", m1, g);

    auto m2 = jaccard_metric(g);

    if(with_show) {
        show_matrix(m2, "jaccard_metric");
    }

    write_csv("../data/jaccard_metric.csv", m2, g);

    auto m3 = adamic_adar_metric(g);

    if(with_show) {
        show_matrix(m3, "adamic_adar_metric");
    }

    write_csv("../data/adamic_adar_metric.csv", m3, g);

    auto m4 = preferential_attachment(g);

    if(with_show) {
        show_matrix(m4, "preferential_attachment");
    }

    write_csv("../data/preferential_attachment.csv", m4, g);
}

void show_test1(){
    std::vector<std::vector<double>> mat{
            {0,   1,   0,   1, 0},
            {1, 0.5,   1, 0.5, 1},
            {0,   1, 0.5,   1, 0},
            {1, 0.5,   1, 0.5, 1},
            {0,   1,   0,   1, 0}
    };

    show_matrix(mat);
}

void show_test2(){
    std::vector<std::vector<int>> e{
            {1, 2, 3, 4},
            {0},
            {0},
            {0},
            {0}
    };

    std::vector<int> n{0, 1, 2, 3, 4};

    graph g(e,n);

    draw_graph dg;

    dg.g = g;
    dg.x = {490, 500, 510, 500, 500};
    dg.y = {500, 500, 500, 510, 490};

    show_graph(dg);
}

void show_test3(){
    std::vector<std::vector<int>> e{
    };

    std::vector<int> n;

    for(size_t i=0;i<100;++i){
        e.emplace_back(std::vector<int>());
        n.emplace_back(i);
    }

    graph g(e,n);

    //draw_graph dg = generate_start_positions(g);
    draw_graph dg = generate_circle_positions(g);

    show_graph(dg);
}

void show(const graph &g){
//    draw_graph dg = generate_start_positions(g);
    draw_graph dg = generate_circle_positions(g);

    show_graph(dg);
}

void fourth_task(const graph& g){
    draw_graph dg = generate_circle_positions(g);

    auto res1 = degree_centrality(g);

    dg.node_colors = res1;

    show_graph(dg, "degree centrality", false);
    write_vec("../data/degree_centrality.csv", res1, g);
//*/

    auto res2 = closness_centrality(g);

    dg.node_colors = res2;

    show_graph(dg, "closeness centrality", false);
    write_vec("../data/closeness_centrality.csv", res2, g);
//*/

    auto res3 = betweenness_centrality(g);

    dg.node_colors = res3;

    show_graph(dg, "betweenness centrality", false);
    write_vec("../data/betweenness_centrality.csv", res3, g);
//*/

    auto res4 = eigenvector_centrality(g);

    dg.node_colors = res4;

    show_graph(dg, "eigenvector centrality", false);
    write_vec("../data/eigenvector_centrality.csv", res4, g);
//*/

    auto res5 = edge_betweenness(g);
    draw_graph dg2 = generate_circle_positions(g);

    dg2.edge_colors = res5;

    show_graph(dg2, "betweenness centrality", false);
    write_csv("../data/edge_betweenness.csv", res5, g);
//*/
}

void zero_task(const graph& g){
    write_csv("../data/matrix.csv",g.get_edge_mat(), g);
    write_csv("../data/connectivity_list.csv", g.edges, g);

    std::ofstream out("../data/list.csv");

    if(!out.is_open()){
        std::cout<<"can't open file\n";
        return;
    }

    auto values = g.get_edge_list();

    for(size_t i=0;i<values.size(); ++i){
        if(i!=0){
            out << '\n';
        }
        out<<g.get_name(values[i].first)<<','<<g.get_name(values[i].second);
    }

    out.flush();
}

graph make_interesting(const graph& g){
    auto c = get_cc(g);

    std::vector<int> tmp;

    for(auto &it: c[0]){
        tmp.emplace_back(g.get_name(it));
    }

    return g.decrease(tmp);
}

int main(int argc, char* argv[]){
    auto g = graph::input_graph("../data/edges.txt");

    show(g);
    zero_task(g);
    first_task(g);

    auto k = make_interesting(g);
    output_graph("../data/edges2.txt", k.edges, k);

    k = k.make_indirected();

    second_task(k, "../data/res2.txt");
    third_task(k, true);
    fourth_task(k);
}
