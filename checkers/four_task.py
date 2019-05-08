import csv
import networkx as nx


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

    res = nx.Graph()

    for v in gr.nodes:
        res.add_node(v)
    for i in gr.in_edges():
        res.add_edge(i[1], i[0])

    return res


def check(file_name):
    g = get_interesting_graph(file_name)

    with open('../data/degree_centrality.csv') as f_in:

        r = csv.reader(f_in)

        names = next(r)

        q = dict()

        for i, k in enumerate(names):
            q[k] = i

        dif = 0
        d = next(r)
        for x, v in nx.degree_centrality(g).items():
            dif = max(dif, abs(float(d[q[x]]) - v))
            if abs(float(d[q[x]]) - v) > 0.1:
                print(x, d[q[x]], v)
        print(dif)

    with open('../data/closeness_centrality.csv') as f_in:

        r = csv.reader(f_in)

        names = next(r)

        q = dict()

        for i, k in enumerate(names):
            q[k] = i

        dif = 0
        d = next(r)
        for x, v in nx.closeness_centrality(g).items():
            dif = max(dif, abs(float(d[q[x]]) - v))
            if abs(float(d[q[x]]) - v) > 0.1:
                print(x, d[q[x]], v)
        print(dif)

    with open('../data/betweenness_centrality.csv') as f_in:

        r = csv.reader(f_in)

        names = next(r)

        q = dict()

        for i, k in enumerate(names):
            q[k] = i

        dif = 0
        d = next(r)
        for x, v in nx.betweenness_centrality(g).items():
            dif = max(dif, abs(float(d[q[x]]) - v))
            if abs(float(d[q[x]]) - v) > 0.1:
                print(x, d[q[x]], v)
        print(dif)

    with open('../data/eigenvector_centrality.csv') as f_in:

        r = csv.reader(f_in)

        names = next(r)

        q = dict()

        for i, k in enumerate(names):
            q[k] = i

        dif = 0
        d = next(r)
        for x, v in nx.eigenvector_centrality(g).items():
            dif = max(dif, abs(float(d[q[x]]) - v))
            if abs(float(d[q[x]]) - v) > 0.1:
                print(x, d[q[x]], v)
        print(dif)

    with open('../data/edge_betweenness.csv') as f_in:

        r = csv.reader(f_in)

        names = next(r)

        q = dict()

        for i, k in enumerate(names):
            q[k] = i

        dif = 0
        d = list(r)
        for x, v in nx.edge_betweenness_centrality(g).items():
            dif = max(dif, abs(float(d[q[x[0]]][q[x[1]]]) - v))
            if abs(float(d[q[x[0]]][q[x[1]]]) - v) > 0.01:
                print(x, d[q[x[0]]][q[x[1]]], v)
        print(dif)


if __name__ == '__main__':
    check('../data/vk-friends.gexf')
