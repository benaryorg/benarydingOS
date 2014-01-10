#!/usr/bin/env python2
# -*- coding: utf-8 -*-

import os
import sys
import argparse
import traceback

# replace everything in files with these file extensions (without the .)
file_extensions = ['c']
# ignore the following directories and files:
ignore_dirs = ['.git', 'build']
ignore_files = [sys.argv[0], '.gitignore']

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Replaces one string with one other in all files'
                                                +'in a directory with the following extension: %s' 
                                                % (str(file_extensions)))
    
#    parser.add_argument('--text', type=str, help='The string to look for', required=True)
#    parser.add_argument('--replace', type=str, help='The string to replace `text\' with', required=True)
    parser.add_argument('--dir', dest='directory', default='.', help='directory to replace in')
    
    args = parser.parse_args()
#    str1 = args.text
#    str2 = args.replace
    str1=sys.argv[1]
    str2=sys.argv[2]
    directory = args.directory
    
    file_list = []
    
    # generate file list
    for root, dirs, files in os.walk(directory):
        # ignore directories
        for srid in ignore_dirs:
            if srid in dirs:
                dirs.remove(srid)
        
        # ignore files
        for selif in ignore_files:
            if selif in files:
                files.remove(selif)
        for f in files:
            file_extension = f.rsplit('.', 1)
            if len(file_extension) == 2:
                if file_extension[1] in file_extensions:
                    file_list.append(os.path.join(root, f))
    
    for current_file in file_list:
        print 'Writing %s ...' % current_file
        content = []
        try:
            with open(current_file, 'rb') as f:
                content = [s.replace(str1, str2) for s in f.readlines()]
        except:
            traceback.print_exc()
        
        try:
            with open(current_file, 'wb') as f:
                for c in content:
                    f.write(c)
                f.flush()
        except:
            traceback.print_exc()

# toplel modeline
# kate: indent-width 4; replace-tabs on
