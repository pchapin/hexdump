(***************************************************************************
FILE          : hexdump.ml
LAST REVISION : 2008-02-16
SUBJECT       : Program to display the contents of a file in hex.
PROGRAMMER    : (C) Copyright 2006 by Peter C. Chapin

TODO:
 + Should print out an error message if invoked with no arguments.
 + Implement some more command line options?

Please send comments or bug reports to

     Peter C. Chapin
     Electrical and Computer Engineering Technology
     Vermont Technical College
     Randolph Center, VT 05061
     Peter.Chapin@vtc.vsc.edu
****************************************************************************)

(** Formats a buffer for display as a string of ASCII characters (imperative style).
    @param buffer The buffer to format.
    @param count The number of interesting characters in the buffer.
    @return a string with non-ASCII characters from the buffer replaced with dots and trailing
    junk characters from the buffer replaced with spaces. *)
let ascii_format buffer count =
    let formatter ch = 
        let code = Char.code ch in
            if code < 0x20 || code >= 0x7F then '.' else ch in

    let work_buffer = String.copy buffer in
        begin
            for index = 0 to count - 1 do
                work_buffer.[index] <- formatter work_buffer.[index]
            done;
            String.fill work_buffer count ((String.length work_buffer) - count) ' ';
            work_buffer
        end;;


(** Formats a string as a sequence of hex values (functional style).
    @param buffer The string to be formatted.
    @param count The number of interesting characters in the buffer.
    @return a string consisting of the hex representations of the characters in the buffer.
    The string is padded out with spaces to account for the junk characters in the buffer.
*)
let hex_format buffer count =
    let rec process_buffer buffer ch_number =
        let size = String.length buffer in
        if size = 0 then "" else
            let head = buffer.[0] in
            let tail = String.sub buffer 1 (size - 1) in
            let extra = if ch_number = 8 then " " else "" in
                if ch_number <= count then
                    (Printf.sprintf "%02X " (Char.code head)) ^ extra ^ process_buffer tail (ch_number + 1)
                else
                    "   " ^ extra ^ process_buffer tail (ch_number + 1)
    in
        process_buffer buffer 1;;


(** Processes a file, outputting its contents in hex to the standard output device. 
    @param file_name The name of the file to process.
*)
let process_file file_name = 
    let ifile  = open_in_bin file_name in
    let buffer = String.create 16 in
    let count  = ref (-1) in
    let offset = ref 0 in
        begin
            while (count := input ifile buffer 0 16; !count) <> 0 do
                Printf.printf "%08X  " !offset;
                print_string (hex_format buffer !count);
                print_string "|";
                print_string (ascii_format buffer !count);
                print_string "|\n";
                offset := !offset + !count
            done;
            close_in ifile
        end;;

Arg.parse [("-f", Arg.String(process_file), "Specifies file to display")]
  process_file "Displays contents of file in hex"

