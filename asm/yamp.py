#!/usr/bin/env python

import argparse
import sys

subs = {}
commentblock = False

def remove_comments ( line ):
    global commentblock
    if (commentblock):
        tokens = line.split("*/", 1)
        if len(tokens)==1:
            return ''
        else:
            commentblock = False
            return remove_comments(tokens[1])
    else:
        tokens = line.split("//", 1)
        tokens = tokens[0].split("/*", 1)
        if len(tokens)==1:
            return tokens[0]
        else:
            commentblock=True
            return tokens[0]+remove_comments(tokens[1])


def process_line ( x ):
    line = x.rstrip('\n\r ')
    line = remove_comments(line)
    return line + '\n';

def process_file ( outfile, infile, filename ):
    line = 0
    outfile.write( '#line {0} "{1}"\n'.format(line + 1, filename) )
    for line in infile:
        outfile.write(process_line(line))


# main

parser = argparse.ArgumentParser(description='Yet Another Macro Preprocessor')
parser.add_argument('input', nargs='?', default='-', help='input filename')
parser.add_argument('output', nargs='?', default='-', help='output filename')

parser.add_argument('-D', metavar='macro[=defn]', action='append', help='predefine macro as defn if specified, or as 1 if not')
parser.add_argument('-I', metavar='dir', action='append', help='add a directory to be searched for #include files')
parser.add_argument('--include', metavar='file', action='append', help='process file as if "#include "file"" appeared as the first line of the primary source file.')

args = parser.parse_args()

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
        subs["__YAMP__"] = "1"
        process_file( outfile, infile, args.input )
    finally:
        outfile.close()
finally:
    infile.close()




