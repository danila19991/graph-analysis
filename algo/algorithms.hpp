//
// Created by gusef on 24.04.2019.
//

#ifndef GRAPH_ALGORITHMS_HPP
#define GRAPH_ALGORITHMS_HPP

#include <vector>
#include <string>

/**
 * Function for getting list of strong connectivity components.
 * @param[in] g Graph for analysing.
 * @return List of string connectivity components, sorted by size.
 */
std::vector<std::vector<int>> get_scc(const std::vector<std::vector<int>>& g);

/**
 * Function for getting list of connectivity components.
 * @warning Graph should be analysing.
 * @param[in] g Graph for changing.
 * @return List of connectivity components, sorted by size.
 */
std::vector<std::vector<int>> get_cc(const std::vector<std::vector<int>>& g);

#endif //GRAPH_ALGORITHMS_HPP
