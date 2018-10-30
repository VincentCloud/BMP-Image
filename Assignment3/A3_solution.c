/* FILE: A3_solutions.c is where you will code your answers for Assignment 3.
 * 
 * Each of the functions below can be considered a start for you. They have 
 * the correct specification and are set up correctly with the header file to
 * be run by the tester programs.  
 *
 * You should leave all of the code as is, especially making sure not to change
 * any return types, function name, or argument lists, as this will break
 * the automated testing. 
 *
 * Your code should only go within the sections surrounded by
 * comments like "REPLACE EVERTHING FROM HERE... TO HERE.
 *
 * The assignment document and the header A3_solutions.h should help
 * to find out how to complete and test the functions. Good luck!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "A3_provided_functions.h"

unsigned char*
bmp_open( char* bmp_filename,        unsigned int *width, 
          unsigned int *height,      unsigned int *bits_per_pixel, 
          unsigned int *padding,     unsigned int *data_size, 
          unsigned int *data_offset                                  )
{
  unsigned char *img_data=NULL;
  FILE *bmpfile = fopen(bmp_filename,"rb");

  if( bmpfile == NULL ){
  	printf( "unable to open the file %s.\n");
  	return -1;
  }

  //Read the overall file size
  unsigned int overallFileSize;
  fread(&overallFileSize, 1, sizeof(unsigned int), bmpfile );

  //Rewind file pointer to the beginning and read the entire contents.
  rewind(bmpfile);

  char imageData[overallFileSize];
  if(fread( imageData, 1, overallFileSize, bmpfile ) != overallFileSize ){
  	printf(" unable to read the requested %d bytes.\n", overallFileSize );
  	return -1;
  }


  //Read the image info into variables 
  *width = (unsigned int*)(imageData +18);
  *height = (unsigned int*)(imageData+22);
  *bits_per_pixel = (unsigned int*)(imageData+28);


  



  return img_data;  
}

void 
bmp_close( unsigned char **img_data )
{
  // REPLACE EVERYTHING FROM HERE
  printf( "UNIMPLEMENTED FUNCTION: bmp_close has not yet been coded. Please complete before submitting!\n");
  // TO HERE!  
}

unsigned char***  
bmp_scale( unsigned char*** pixel_array, unsigned char* header_data, unsigned int header_size,
           unsigned int* width, unsigned int* height, unsigned int num_colors,
           float scale )
{
  unsigned char*** new_pixel_array = NULL; 
  // REPLACE EVERYTHING FROM HERE
  printf( "UNIMPLEMENTED FUNCTION: bmp_scale has not yet been coded. Please complete before submitting!\n");
  // TO HERE! 
  return new_pixel_array;
}         

int 
bmp_collage( char* background_image_filename,     char* foreground_image_filename, 
             char* output_collage_image_filename, int row_offset,                  
             int col_offset,                      float scale )
{
  // REPLACE EVERYTHING FROM HERE
  printf( "UNIMPLEMENTED FUNCTION: bmp_collage has not yet been coded. Please complete before submitting!\n");
  // TO HERE! 
  return 0;
}              

