import networkx as nx

if __name__ == '__main__':
    g = nx.read_gexf('../data/vk-friends.gexf')

    print(g)

    wcc = nx.weakly_connected_components(g)
    scc = nx.strongly_connected_components(g)

    print(list(wcc))
    print(list(scc))
