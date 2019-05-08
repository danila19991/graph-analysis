//
// Created by danila on 28.04.19.
//

#ifndef GRAPH_GRAFFIC_H
#define GRAPH_GRAFFIC_H

#include "../algo/graph.hpp"

#include <vector>
#include <string>

struct draw_graph{
    graph g;
    std::vector<double> x;
    std::vector<double> y;
    double maxx = 1000;
    double maxy = 1000;
    std::vector<double> node_colors;
    std::vector<std::vector<double>> edge_colors;
    draw_graph():g({},{}){}
};

draw_graph generate_start_positions(const graph &g);

draw_graph generate_circle_positions(const graph &g);

void iterate_draw_graph(draw_graph& dg, double k=1e-2);

void show_matrix(const std::vector<std::vector<double>>& mat,
        const std::string& name = "show matrix");

void show_graph(draw_graph& g, const std::string& name = "show matrix",
        bool need_iteration = false);

#endif //GRAPH_GRAFFIC_H
