###########################################################################
# FILE          : hexdump.py
# LAST REVISION : 2006-08-07
# SUBJECT       : Python implementation of a simple hex viewing utility.
# PROGRAMMER    : (C) Copyright 2006 by Peter C. Chapin
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
import sys
import command_line

# Process the command line.
raw_command_line = string.join(sys.argv)
command = command_line.CanonicalCommandLine({})
command.parse(raw_command_line)
arguments = command.get_arguments()

if len(arguments) != 2:
    print 'Usage: hexdump file.bin'
    sys.exit(1)

# Define which characters can be displayed in the text panel.
displayable = string.digits + string.letters + string.punctuation + ' '

try:

    # Prepare the input file.
    in_file = open(arguments[1], "rb")
    print 'Dump of file' + arguments[1] + ':'
    print ''
    file_offset = 0
    
    # Read 16 bytes at a time.
    while 1:
        data = in_file.read(16)
        if not data: break
        output = ("%08X " % file_offset) + "|"
        file_offset += len(data)
    
        # Compute the hex contents of this line.
        byte_counter = 0
        for byte in data:
            output += ("%02X " % ord(byte))
            byte_counter += 1
            if byte_counter == 8:
                output += "  "
        output += "| "
    
        # Compute the text panel corresponding to the hex bytes.
        for byte in data:
            if displayable.find(byte) == -1:
                output += "."
            else:
                output += byte
        print output
    
    in_file.close()
    
except IOError, e:
    print 'Error: ' + e.strerror
