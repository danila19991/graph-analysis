//
// Created by danila on 26.04.19.
//

#ifndef GRAPH_GRAPH_HPP
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

    int get_id(int name) const;

    int get_name(int id) const;

    bool is_indirected() const;

    graph make_indirected() const;

    void normalise();

    std::vector<std::pair<int, int>> get_edge_list() const;

    std::vector<std::vector<int>> get_edge_mat() const;

    graph revert() const;

    static graph input_graph(const std::string& name);

    friend bool operator == (const graph&l, const graph& r);
};


#endif //GRAPH_GRAPH_HPP
