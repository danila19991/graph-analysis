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

    for elem in graph:
        print(elem.tag)
        if 'nodes' in elem.tag:
            for node in elem:
                t = node.attrib['id']
                d[t] = len(d)
                g[d[t]] = []
        if 'edges' in elem.tag:
            for node in elem:
                f = node.attrib['source']
                t = node.attrib['target']
                g[d[f]].append(d[t])

    with open('data/vertex_name.json','w') as f_out:
        f_out.write(json.dumps(d))
    print(json.dumps(d))
    with open('data/edges', 'w') as f_out:
        f_out.write(str(len(g))+'\n')
        for k, v in g.items():
            f_out.write(str(len(v)) + ' ' + ''.join([str(q)+' ' for q in v])+'\n')
            print(k, v)
