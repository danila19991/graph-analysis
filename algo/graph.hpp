//
// Created by danila on 26.04.19.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_HPP

#include <vector>
#include <unordered_map>

/**
 * Class with graph structure.
 */
class graph {
    std::unordered_map<int, int> from_name_to_id;

    std::vector<int> from_id_to_name;

public:

    std::vector<std::vector<int>> edges;

    graph(std::vector<std::vector<int>> _edges,
            std::vector<int> from_id_to_name);

    graph(std::vector<std::vector<int>>  _edges,
          std::vector<int>  _from_id_to_name,
          std::unordered_map<int, int>  _from_name_to_id);

    int get_id(int name);

    int get_name(int id);

    static graph input_graph(const std::string& name);
};


#endif //GRAPH_GRAPH_H
