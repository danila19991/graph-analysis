//
// Created by gusef on 24.04.2019.
//

#ifndef GRAPH_ALGORITHMS_HPP
#define GRAPH_ALGORITHMS_HPP

#include <vector>
#include <string>

/**
 * Reader graph from file.
 * @param[in] file_name Path to file for parsing
 * @return  Graph by the adjacency list.
 */
std::vector<std::vector<int>> input_graph(const std::string& file_name);

/**
 * Function for checking if current graph is indirected.
 * @param[in] g Graph for checking.
 * @return True if every edge have reverted.
 */
bool is_indirected(const std::vector<std::vector<int>>& g);

/**
 * Function for making current graph indirected.
 * @param[in] g Graph for changing.
 * @return Indirect graph.
 */
std::vector<std::vector<int>> make_indirected(const
                                              std::vector<std::vector<int>>& g);

#endif //GRAPH_ALGORITHMS_HPP
