#!/usr/bin/env python

# Compile the flat file webpages into the WebPages.h file

import sys
import os
import string


# with open(filename, 'r') as f:
# src = f.read()
# src = minify(src, mangle=True, mangle_toplevel=False)

def buildWebPages():
    print "Building WebPages.h"

    hs = ""

    for filename in os.listdir("."):
        if filename[-4:] == '.css' or filename[-4:] == '.htm':
            print("  Parsing: "+filename)

            with open(filename, 'r') as f:
                src = f.read()

                # add minification

                hs += 'static const char '+ string.replace(filename, '.','') +'Page[] = R"~(\n'
                hs += src
                hs += ')~";\n\n'

    print "Saving WebPages.h"
    with open("../WebPages.h",'w') as f:
        f.write(hs)

    print "Done"


if __name__ == '__main__':
    buildWebPages()
