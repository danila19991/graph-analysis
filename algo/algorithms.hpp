//
// Created by gusef on 24.04.2019.
//

#ifndef GRAPH_ALGORITHMS_HPP
#define GRAPH_ALGORITHMS_HPP

#include "graph.hpp"

#include <vector>
#include <string>

/**
 * Function for getting list of strong connectivity components.
 * @param[in] g Graph for analysing.
 * @return List of string connectivity components, sorted by size.
 */
std::vector<std::vector<int>> get_scc(const graph& g);

/**
 * Function for getting list of connectivity components.
 * @warning Graph should be analysing.
 * @param[in] g Graph for changing.
 * @return List of connectivity components, sorted by size.
 */
std::vector<std::vector<int>> get_cc(const graph& g);

typedef std::vector<std::vector<int>>  dist_mat;
typedef std::vector<std::vector<double>>  mat;

dist_mat get_all_distance(const graph& g);

int get_radius(const dist_mat& d);

int get_diametr(const dist_mat& d);

std::vector<int> get_center(const dist_mat& d);

std::vector<int> get_periphery(const dist_mat& d);

double get_average_distance(const dist_mat& d);

mat common_neighbors(const graph& g);

mat jaccard_metric(const graph& g);

mat adamic_adar_metric(const graph& g);

mat preferential_attachment(const graph& g);

/**
 * Function for intersecting two sorted vectors of numbers.
 * @warning Input parametrs must be sorted.
 * @param[in] l First vector for intersecting.
 * @param[in] r Second vector for intersecting.
 * @return Sorted vector with elements which was in l and r.
 */
std::vector<int> intersection(const std::vector<int>& l,
        const std::vector<int>& r);

/**
 * Function for merging two sorted vectors of numbers.
 * @warning Input parametrs must be sorted.
 * @param[in] l First vector for merging.
 * @param[in] r Second vector for merging.
 * @return Sorted vector with elements which was in l or r.
 */
std::vector<int> merge(const std::vector<int>& l, const std::vector<int>& r);

std::vector<double> degree_centrality(const graph& g);

std::vector<double> closness_centrality(const graph& g);

std::vector<double> betweenness_centrality(const graph& g);

std::vector<double> eigenvector_centrality(const graph& g, int iter_num = 1000,
        double eps = 1e-6);

std::vector<std::vector<double>> edge_betweenness(const graph& g);

#endif //GRAPH_ALGORITHMS_HPP
