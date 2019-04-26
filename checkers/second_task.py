import numpy as np
import matplotlib.pyplot as plt
import networkx as nx


def hist(file_name):
    with open(file_name) as f_in:
        n = int(f_in.readline())
        degree = np.zeros(n)
        for i in range(n):
            degree[i] = int(f_in.readline().split()[1])
    print(degree)
    print(np.average(degree))
    plt.hist(degree, 20)
    plt.show()


def get_interesting_graph(file_name):
    g = nx.read_gexf(file_name)
    ls = list(nx.weakly_connected_component_subgraphs(g))
    gr = ls[0]
    for i in range(1, len(ls)):
        if len(ls[i]) > len(gr):
            gr = ls[i]

    e = list(gr.in_edges())
    for i in e:
        if (i[1], i[0]) not in e:
            gr.add_edge(i[1], i[0])

    return gr


def get_params(file_name):
    g = get_interesting_graph(file_name)
    print(len(g))
    print(nx.radius(g))
    print(nx.diameter(g))
    print(nx.center(g))
    print(nx.periphery(g))
    print('------')
    path = nx.all_pairs_shortest_path(g)
    s = 0
    k = 0
    for l1, l in path:
        for l2, j in l.items():
            if l1 != l2:
                s = s + len(j) - 1
                k = k + 1
    print(s/k)


if __name__ == '__main__':
    #hist('../data/edges2.txt')
    get_params('../data/vk-friends.gexf')
