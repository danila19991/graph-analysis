//
// Created by danila on 26.04.19.
//

#ifndef GRAPH_TEST_UTILS_H
#define GRAPH_TEST_UTILS_H

#include <string>
#include <vector>

template <typename T>
std::stringstream& operator<<(std::stringstream& stream,
        const std::vector<T>& list){
    for(auto it=list.cbegin(); it!=list.cend(); ++it){
        stream << (it==list.cbegin()) ? "{" : ", ";
        stream << *it;
    }
    stream << "}";
    return stream;
}

#endif //GRAPH_TEST_UTILS_H
