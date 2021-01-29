#!/usr/bin/env python

import argparse
import sys


def process_line ( x ):
    return x;


# main

parser = argparse.ArgumentParser(description='Yet Another Macro Preprocessor')
parser.add_argument('input', nargs='?', default='-', help='input filename')
parser.add_argument('output', nargs='?', default='-', help='output filename')

parser.add_argument('-D', metavar='macro[=defn]', action='append', help='predefine macro as defn if specified, or as 1 if not')
parser.add_argument('-I', metavar='dir', action='append', help='add a directory to be searched for #include files')
parser.add_argument('--include', metavar='file', action='append', help='process file as if "#include "file"" appeared as the first line of the primary source file.')

args = parser.parse_args()
#print(args)

if args.input=='-':
    infile = sys.stdin
else:
    infile = open(args.input, 'r')
try:
    if args.output=='-':
        outfile = sys.stdout
    else:
        outfile = open(args.output, 'w')
    try:
        for line in infile:
            outfile.write(process_line(line))
    finally:
        outfile.close()
finally:
    infile.close()



