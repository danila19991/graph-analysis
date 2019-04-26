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

dist_mat get_all_distance(const graph& g);

int get_radius(const dist_mat& d);

int get_diametr(const dist_mat& d);

std::vector<int> get_center(const dist_mat& d);

std::vector<int> get_periphery(const dist_mat& d);

double get_average_distance(const dist_mat& d);

#endif //GRAPH_ALGORITHMS_HPP
