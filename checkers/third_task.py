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

    with open('../data/common_neighbors.csv') as f_in:

        r = csv.reader(f_in)

        names = next(r)

        dif = 0
        d = list(r)
        for i in range(len(g)):
            for j in range(len(g)):
                dif = max(dif, abs(int(d[i][j]) -
                                   len(list(nx.common_neighbors(g,
                                                                names[i],
                                                                names[j])))))
        print(dif)

    with open('../data/jaccard_metric.csv') as f_in:

        r = csv.reader(f_in)

        names = next(r)

        q = dict()

        for i, k in enumerate(names):
            q[k] = i

        dif = 0
        d = list(r)
        for x, y, v in nx.jaccard_coefficient(g):
            dif = max(dif, abs(float(d[q[x]][q[y]]) -v))
        print(dif)

    with open('../data/adamic_adar_metric.csv') as f_in:

        r = csv.reader(f_in)

        names = next(r)

        q = dict()

        for i, k in enumerate(names):
            q[k] = i

        dif = 0
        d = list(r)
        for x, y, v in nx.adamic_adar_index(g):
            dif = max(dif, abs(float(d[q[x]][q[y]]) -v))
        print(dif)

    with open('../data/preferential_attachment.csv') as f_in:

        r = csv.reader(f_in)

        names = next(r)

        q = dict()

        for i, k in enumerate(names):
            q[k] = i

        dif = 0
        d = list(r)
        for x, y, v in nx.preferential_attachment(g):
            dif = max(dif, abs(float(d[q[x]][q[y]]) -v))
        print(dif)


if __name__ == '__main__':
    check('../data/vk-friends.gexf')
