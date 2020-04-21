#!/usr/bin/env python3

from os import path
from argparse import ArgumentParser
from pprint import pprint
import xml.etree.ElementTree as ET

COVERAGE = {}

# COVERAGE FORMAT:
#   [
#     "compoundname": {
#       "covered": <boolean>,
#       "coverage": <float>,
#       "location": [{"start": <line>, "end": <line>},...],
#       "nodes": [
#         ...
#       ]
#     },
#     ...
#   ]


def error(msg):
    print("[Error]: {}".format(msg))
    exit(1)


def load_xml(file):
    if not path.exists(file):
        error("Failed to open \"{}\" as XML file".format(file))
    return ET.parse(file)


def doc_extract_location(element):
    location = element.find('location')
    if location is None:
        return None
    return {
        'file':
        location.get('bodyfile')
        if location.get('bodyfile') else location.get('file'),
        'start':
        location.get('bodystart'),
        'end':
        location.get('bodyend')
    }


def is_documented(element):
    brief = element.find('briefdescription')
    detail = element.find('detaileddescription')
    return brief.text.strip() != '' or detail.text.strip() != '' or len(
        brief) > 0 or len(detail) > 0


def doc_compound(input_path, refid):
    xml = load_xml(path.join(input_path, refid + '.xml')).find('compounddef')
    return {
        'name': xml.find('compoundname').text,
        'covered': is_documented(xml),
        'location': doc_extract_location(xml)
    }


def doc_cov_struct(input_path, refid):
    return {}


def doc_cov_namespace(input_path, refid):
    return {}


def doc_cov_group(input_path, refid):
    return {}


def doc_coverage(input_path, output_path):
    if not path.exists(path.join(input_path, 'index.xml')):
        error("Input directory \"{}\" does not contain index.xml".format(
            input_path))
    index = load_xml(path.join(input_path, 'index.xml'))
    for compound in index.findall('compound'):
        kind = compound.get('kind')
        refid = compound.get('refid')
        COVERAGE[compound.get('refid')] = doc_compound(input_path, refid)

    pprint(COVERAGE)


def main():
    parser = ArgumentParser('coverage')
    parser.add_argument('--docs',
                        help='Generate documentation coverage report')

    parser.add_argument('output', help='Output directory')

    args = parser.parse_args()

    if args.docs is not None:
        doc_coverage(args.docs, args.output)


if __name__ == "__main__":
    main()
