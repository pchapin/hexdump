/****************************************************************************
FILE        : hexdump.c
LAST REVISED: 2013-06-13
SUBJECT     : Simple program to display the contents of a file in HEX.

Please send comments or bug reports to

     Peter C. Chapin
     Vermont Technical College
     Williston, VT 05495
     PChapin@vtc.vsc.edu
****************************************************************************/

#include <stdio.h>
#include <ctype.h>

/*==========================================*/
/*           Function Definitions           */
/*==========================================*/

void dump( FILE *input_file, char *file_name )
{
    unsigned char buffer[16]; // Holds 16 bytes from the file.
    int  count;               // Number of bytes actually read in last attempt.
    long offset;              // Offset of first byte in last buffer full.
    int  i;

    printf( "Dump of %s\n\n", file_name );
    offset = 0;

    while( ( count = fread( buffer, 1, 16, input_file ) ) > 0 ) {

        // Display the offset for the start of the line, and advance it. 
        printf( "%08lX ", offset );
        offset += count;

        // Print hex bytes and fill buffer with printable characters.
        for( i = 0; i < 16; i++ ) {
            if( i < count ) {
                printf( " %02X", buffer[i] );
                if( !isprint( buffer[i] ) )
                    buffer[i] = '.';
            }
            else {
                fputs( "   ", stdout );
                buffer[i] = ' ';
            }
            if( i == 7 ) putchar( ' ' );   // Put a space between major sections.
        }

        // Print text bytes from the adjusted buffer.
        printf( " |%16.16s|\n", buffer );
    }
}

/*==================================*/
/*           Main Program           */
/*==================================*/

int main( int argc, char *argv[] )
{
    FILE *input_file;
    int   i;

    // Print header to stderr. Won't mess up a redirected output.
    fprintf( stderr, "hexdump (June 13, 2013)\n" );

    // Print usage message if appropriate.
    if( argc == 1 ) {
      fprintf( stderr, "\nUSAGE: hexdump filename [filename...]\n"
                         "       Displays contents of specified files in hex.\n" );
      return 0;
    }

    // For each file on the command line... (note: wildcards not handled).
    for( i = 1; i < argc; i++ )

        // Try to open it. If successful, dump the sucker.
        if( ( input_file = fopen( argv[i], "rb" ) ) == NULL )
            fprintf( stderr,"\nError: Can't open %s for input.", argv[i] );
        else {
            dump( input_file , argv[i] );
            fclose( input_file );
        }
    
    return 0;
}
