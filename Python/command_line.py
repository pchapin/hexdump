###########################################################################
# FILE          : command_line.py
# LAST REVISION : 2006-08-07
# SUBJECT       : Command line parsing classes.
# PROGRAMMER    : (C) Copyright 2006 by Peter C. Chapin
#
# This module provides simplistic command line processing. Many variations
# on this theme are possible. This module allows one to derive new option
# processing classes from a common base. Thus a program could have different
# types of command line processors active to support a variety of command
# line syntaxes.
#
# Please send comments or bug reports to
#
#      Peter C. Chapin
#      Electrical and Computer Engineering Technology
#      Vermont Technical College
#      Randolph Center, VT 05061
#      pchapin@ecet.vtc.edu
###########################################################################

import string

# Base class provides a skeleton.
class CommandLine:
    def __init__(self, default_options):
        self.options = default_options
        self.arguments = []
        
    def parse(self, line):
        raise "Not Implemented"
    
    def get_options(self):
        return self.options
    
    def get_arguments(self):
        return self.arguments
    
# Command line is verbose. One option at a time. Option arguments follow '='
class CanonicalCommandLine(CommandLine):
    def parse(self, line):
        words = string.split(line)
        for word in (words):
            if word[0] != '-':
                self.arguments.append(word)
            else:
                components = string.split(word, '=', 1)
                if len(components) == 1:
                    self.options[components[0][1:]] = ''
                else:
                    self.options[components[0][1:]] = components[1]

##############
# Test Fixture
##############

def test():
    cl = CanonicalCommandLine({ 'opt1':'default1', 'opt2':'default2' })
    cl.parse("-opt1=override1 -opt3=new_value3 arg1 -opt4 arg2")
    print 'options = ', cl.get_options()
    print 'arguments = ', cl.get_arguments()
    
if __name__ == "__main__":
    test()

    