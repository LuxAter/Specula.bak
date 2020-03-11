#!/usr/bin/env python3
from argparse import ArgumentParser
import uuid
from pprint import pprint

EDGES = {}
CLUSTERS = {'nodes': [], 'clusters': {}, 'name': ''}
NODES = {}


def get_cluster(path, clusters=CLUSTERS):
    if len(path) == 0:
        return clusters
    else:
        if path[0] in clusters['clusters']:
            return get_cluster(path[1:], clusters['clusters'][path[0]])
        else:
            clusters['clusters'][path[0]] = {
                'name': path[0],
                'nodes': [],
                'clusters': {}
            }
            return get_cluster(path[1:], clusters['clusters'][path[0]])


def parse():
    lines = []
    with open("status.dot", "r") as src_file:
        lines = src_file.readlines()
    current_cluster = []
    for line in lines:
        line = line.strip()
        if line.startswith('digraph') or line == '}':
            continue
        elif line.startswith('node') or line.startswith('splines'):
            continue
        elif line.startswith('subgraph'):
            current_cluster.append(line.split(' ')[1])
        elif line == "};":
            current_cluster.pop()
        elif not line.startswith("//") and "->" in line:
            print("A >> {}".format(line))
            src = line.split('->')[0].strip()
            dest = line.split('->')[1].split('[')[0].strip(' ;')
            style = line.partition("style")[2].split(',')[0].strip(
                '=];') if 'style' in line else None
            color = line.partition("color")[2].split(',')[0].strip(
                '=];') if 'color' in line else None
            if src not in EDGES:
                EDGES[src] = {}
            EDGES[src][dest] = [style, color]
        elif not line.startswith('//') and not "->" in line and len(line) > 1:
            key = line.split('[')[0].strip(';')
            val = line.partition('color')[2].strip(
                '=];') if 'color' in line else None
            get_cluster(current_cluster)['nodes'].append(key)
            NODES[key] = val
    pprint(NODES)


def write_clusters(clusters, nodes):
    lines = []
    if clusters['name'] != '':
        lines.append("subgraph {} {{\n".format(clusters['name']))
    for sub_cluster in clusters['clusters'].values():
        lines += write_clusters(sub_cluster, nodes)
    for node in clusters['nodes']:
        lines.append("{}{};\n".format(
            node, "[style=bold,color={}]".format(nodes[node])
            if nodes[node] is not None else ""))
    if clusters['name'] != '':
        lines.append("};\n")
    return lines


def save(clusters, edges, nodes, file):
    lines = ["digraph G{\n", "node[shape=box];\n", "splines=ortho;\n"]
    lines += write_clusters(clusters, nodes)
    for src, edgs in edges.items():
        for dest, style in edgs.items():
            style_str = ""
            if style[0] is not None:
                style_str += ",style={}".format(style[0])
            if style[1] is not None:
                style_str += ",color={}".format(style[1])
            style_str = '[' + style_str.strip(
                ',') + ']' if style_str != '' else ''
            lines += "{} -> {}{};\n".format(src, dest, style_str)
    with open(file, "w") as out_file:
        lines.append("}")
        out_file.writelines(lines)


def find_roots():
    roots = set()
    for src in EDGES.keys():
        roots.add(src)
    for edges in EDGES.values():
        for dest in edges.keys():
            if dest in roots:
                roots.remove(dest)
        roots.add(src)
    return sorted(list(roots))


def find_parents(node):
    parents = set()
    for src, vals in EDGES.items():
        if node in vals.keys():
            parents.add(src)
    return sorted(list(parents))


def find_children(node):
    return sorted(list(EDGES[node].keys()))


def all_parents_done(node):
    parents = find_parents(node)
    if all([NODES[x] == 'green' for x in parents]):
        return True
    return False


def main():
    parser = ArgumentParser('gen')
    parser.add_argument('-c',
                        '--complete',
                        type=str,
                        nargs='?',
                        help="Node to mark as completed")
    parser.add_argument('--deps',
                        type=str,
                        help="Generate tree for dependencies of node")
    parser.add_argument('--edges',
                        choices=['all', 'solid', 'dotted', 'dashed'],
                        default='all',
                        help='Types of edges to include in output')
    parser.add_argument('--exclude',
                        action='store_true',
                        help='exclude all not included nodes')

    args = parser.parse_args()
    parse()

    if args.complete is not None:
        if args.complete in NODES:
            NODES[args.complete] = 'green'
            for edge in EDGES[args.complete]:
                EDGES[args.complete][edge][1] = 'blue'
            for nd in NODES:
                if NODES[nd] != 'green' and all_parents_done(nd):
                    NODES[nd] = 'blue'
            for src in EDGES:
                for dest in EDGES[src]:
                    if NODES[src] == 'green' and NODES[dest] == 'green':
                        EDGES[src][dest][1] = 'green'
        save(CLUSTERS, EDGES, NODES, "status.dot")


if __name__ == "__main__":
    main()
