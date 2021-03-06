import argparse
import sys
import xml.etree.cElementTree as ET
import json


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-f', '--file', default='vk-friends', type=str,
                        help='gexf file for parsing')
    namespace = parser.parse_args(sys.argv[1:])
    file_name = 'data/' + namespace.file + '.gexf'

    tree = None
    try:
        tree = ET.ElementTree(file=file_name)
    except FileNotFoundError:
        print('no such file')
        exit(-1)

    root = tree.getroot()

    graph = root[0]

    d = {}
    g = {}
    names = {}

    for elem in graph:
        if 'nodes' in elem.tag:
            for node in elem:
                t = node.attrib['id']
                d[t] = len(d)
                names[d[t]] = t
                g[d[t]] = []
        if 'edges' in elem.tag:
            for node in elem:
                f = node.attrib['source']
                t = node.attrib['target']
                g[d[f]].append(d[t])

    with open('data/edges.txt', 'w') as f_out:
        f_out.write(str(len(g))+'\n')
        for k, v in g.items():
            f_out.write(str(names[k]) + ' ' + str(len(v)) + ' ' +
                        ''.join([str(names[q])+' ' for q in v])+'\n')
            print(k, v)
