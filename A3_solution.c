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
    // REPLACE EVERYTHING FROM HERE

  unsigned char *img_data=NULL;
  FILE *bmpfile = fopen(bmp_filename,"rb");

  if( bmpfile == NULL ){
  	printf( "%s\n","unable to open the file %s.");
  	return NULL;
  }

  char b,m;
  fread(&b,1,1,bmpfile);
  fread(&m,1,1,bmpfile);

  //Read the overall file size
  unsigned int overallFileSize;
  
  fread( &overallFileSize, 1, sizeof(unsigned int), bmpfile );

  //Rewind file pointer to the beginning and read the entire contents.
  rewind(bmpfile);
  
  img_data=(unsigned char*)malloc(overallFileSize);

  if (fread(img_data, 1, overallFileSize, bmpfile) != overallFileSize)
  {
    printf(" unable to read the requested %d bytes.\n", overallFileSize);
  	return NULL;
  }

  
  //img_data=imageData;

  //Read the image info into variables 
  *width = *((unsigned int*)(img_data +18));
  
  *height = *((unsigned int*)(img_data+22));
  *bits_per_pixel = *((unsigned short*)(img_data+28));

  unsigned int numcolor = *bits_per_pixel/8;

  *padding = (4-(*width*numcolor%4))%4;
  *data_offset =*((unsigned int*)(img_data+10));
  *data_size= *((unsigned int*)(img_data+2));

  fclose(bmpfile);
    // TO HERE!  

  return img_data;  
}

void 
bmp_close( unsigned char **img_data )
{
  // REPLACE EVERYTHING FROM HERE
  free(*img_data);
  *img_data = NULL;
  
    // TO HERE!  
}

unsigned char***  
bmp_scale( unsigned char*** pixel_array, unsigned char* header_data, unsigned int header_size,
           unsigned int* width, unsigned int* height, unsigned int num_colors,
           float scale )
{
  unsigned char*** new_pixel_array = NULL; 
  // REPLACE EVERYTHING FROM HERE

  //Vincent Huang
  // 260761859
  
  unsigned int *newHeight;
  unsigned int *newWidth;

  newHeight = (unsigned int*)(header_data+22);
  newWidth = (unsigned int*)(header_data+18);

  *height=(unsigned int)(*height* scale);
  *width = (unsigned int)(*width* scale);

  *newHeight = *height;
  *newWidth = *width;

  unsigned int *filesize = (unsigned int *) (header_data + 2);
  *filesize = (unsigned int)((*filesize - header_size) * scale) + header_size;

  new_pixel_array = (unsigned char***)malloc(sizeof(unsigned char**)*(*height));
  if(new_pixel_array == NULL){
    printf("unable to malloc");
    exit(1);
  }
  for ( unsigned int i=0; i<*height; i++){
    new_pixel_array[i] = (unsigned char**)malloc(sizeof(unsigned char*)*(*width));
    for ( unsigned int j=0; j<*width; j++){
      new_pixel_array[i][j] = (unsigned char*)malloc(sizeof(unsigned char)*(num_colors));
    }
  }


  for ( unsigned int i=0; i<*height; i++){
    for ( unsigned int j=0; j<*width; j++){
      
        new_pixel_array[i][j] = pixel_array[(unsigned int)((i)/scale)][(unsigned int)(j/scale)];


      
    }
  }


  // TO HERE! 
  return new_pixel_array;
}    


int 
bmp_collage( char* background_image_filename,     char* foreground_image_filename, 
             char* output_collage_image_filename, int row_offset,                  
             int col_offset,                      float scale )
{
  //scale the foreground image and store the metadata

  unsigned char * header_data;
  unsigned int header_size, width, height, num_colors;
  unsigned char *** pixel_array = NULL;

  pixel_array = bmp_to_3D_array(foreground_image_filename, &header_data, &header_size,&width, &height, &num_colors);

  
  if( pixel_array == NULL ){
    printf( "Error: bmp_to_3D_array failed for file %s.\n", foreground_image_filename );
    return -1;
  }

  if(scale>1){
    return -1;
  }

  

  unsigned char*** scaled_pixel_array = bmp_scale( pixel_array, header_data, header_size,
                                                   &width, &height, num_colors,  scale   );



                         
  if( scaled_pixel_array == NULL ){
    printf( "Error: Call to bmp_scale failed!\n" );
    return -1;
  }        

  //store the metadata of the background image

  unsigned char * header_datab;
  unsigned int header_sizeb, widthb, heightb, num_colorsb;
  unsigned char *** pixel_arrayb = NULL;



  pixel_arrayb = bmp_to_3D_array(background_image_filename, &header_datab, &header_sizeb,&widthb, &heightb, &num_colorsb);

  if(num_colors*8!=32 || num_colorsb*8!=32){
    puts("num of colors incorrect.");
    return -1;
  }

  if( pixel_arrayb == NULL ){
    printf( "Error: bmp_to_3D_array failed for file %s.\n", background_image_filename);
    return -1;
  }

  unsigned char ***output;
  output = (unsigned char***)malloc(sizeof(unsigned char**)*(heightb));

  if(output == NULL){
    printf("unable to malloc");
    exit(1);
  }

  for ( unsigned int i=0; i<heightb; i++){
    output[i] = (unsigned char**)malloc(sizeof(unsigned char*)*(widthb));
    for ( unsigned int j=0; j<widthb; j++){
      output[i][j] = (unsigned char*)malloc(sizeof(unsigned char)*(num_colors));
    }
  }





  for(int row=0; row<height;row++){
    for(int col = 0; col<width;col++){
      if(scaled_pixel_array[row][col][0]!=0){
             pixel_arrayb[row+row_offset][col+col_offset]=scaled_pixel_array[row][col];

      }
    }
  }



  int m=bmp_from_3D_array(output_collage_image_filename,header_datab,header_sizeb,pixel_arrayb,widthb,heightb,num_colorsb);
  if(m==-1){
    return -1;
  }


  
  return 0;
}              

