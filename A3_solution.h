/* FILE: A3_solution.h
 * 
 * BRIEF: Contains specifications for the functions you must implement
 *        for Assignment 3.
 *
 * DATE: Oct 22, 2018
 */

/* FUNCTION: bmp_open
 * 
 * BRIEF:    Attempts to read the header information of bmp_filename to
 *           populate the file information variables. If successful,
 *           allocates sufficient heap memory to store the entire image 
 *           including both the header and the pixel data. Then reads
 *           the image from file into this memory.
 *
 * RETURN:   A pointer to the image data in memory. NULL if any failure.
 * 
 * PARAMS:   bmp_filename   [IN]  The path to the BMP file to be opened
 *           width          [OUT] The width of each image row
 *           height         [OUT] The height of each image column
 *           bits_per_pixel [OUT] The bits per pixel (BPP) of the image data
 *           row_padding    [OUT] Number of padding bytes that are placed at the end of 
 *                                each row to ensure the row size is a multiple of 4.
 *                                This is not stored in the bmp directly, but must be
 *                                computed by your code.
 *           data_size      [OUT] The number of bytes in img_data, includes header
 *           header_size    [OUT] The number of bytes just for the header 
 *                                (also known as "offset", in the image header)
 *           img_data       [OUT] Pointer to the image data on the heap.
 * 
 */ 
unsigned char* 
bmp_open(     char* bmp_filename,        unsigned int *width, 
              unsigned int *height,      unsigned int *bits_per_pixel, 
              unsigned int *padding,     unsigned int *data_size, 
              unsigned int *data_offset  );

/* FUNCTION: bmp_close
 *
 * BRIEF:    frees the memory that was allocated on the heap by any successful bmp_open
 * 
 * PARAMS:   img_data [IN/OUT] Pointer to the image data on heap. Must be free'd and 
 *                             set to NULL. It is up to the calling code to ensure the
 *                             address at *img_data is valid heap memory.
 */
void bmp_close( unsigned char **img_data );

/* FUNCTION: bmp_scale
 * 
 * BRIEF:    Resizes the 3D pixel_array with shape [height][width][num_colors]
 *           so that the new shape is [height*scale][width*scale][num_colors].
 *           See A2_provided_functions "bmp_read" for details on this format.
 *           You are allowed to allocate new heap memory for the scaled array.
 *           Set every pixel at [row][col] in the scaled image to the value at
 *           [row/scale][col/scale] in the old image.
 * 
 * RETURN:   A pointer to the scaled 3D pixel array. NULL if any error.
 * 
 * PARAMS:   pixel_array    [IN]     A 3D array holding all the pixels
 *           header_data    [IN]     A pointer to the buffer of raw header data. You must
 *                                   modify this as needed to reflect the new image size. 
 *           header_size    [IN]     The size of the header data in bytes.
 *           width          [IN/OUT] A pointer to an integer that holds the initial image 
 *                                   width. It must be modified by this function to the new width.
 *           height         [IN/OUT] A pointer to an integer that holds the initial image 
 *                                   height. It must be modified by this function to the new height.
 *           num_colors     [IN]     num_colors = BPP / 8
 *           scale          [IN]     The multiplier to be used for scaling the image size.
 *
 */ 
unsigned char***  
bmp_scale(   unsigned char*** pixel_array, unsigned char* header_data, unsigned int header_size,
             unsigned int* width, unsigned int* height, unsigned int num_colors,
             float scale );
              
/* FUNCTION: bmp_collage
 * 
 * BRIEF:    Opens the two input images and places the foreground "on top" of the background.
 *           Writes the result in the ouput image. Note that the background should "show through"
 *           wherever the alpha channel of the foreground is 0, but otherwise the foreground 
 *           pixels must always be visible.
 *           ASSUMPTION: Both images must have BPP=32 (so num_colors=4). The first "color" holds
 *                       the alpha value and second through fourth are the RGB values.
 *           ASSUMPTION: The scaled foreground image must be smaller than the background image
 *                       and the row and column offsets must be such that the foreground is entirely
 *                       contained within the background. This means the output is the same size
 *                       as the background image. 
 *           If either assumption is violated, you can print a sensible error and return NULL.
 *           Avoid Segmentation faults.
 * 
 * RETURN:   0 if successful
 *           -1 on any error, such as failure to open either image etc.
 * 
 * PARAMS:   background_image_filename     [IN] The image to be collaged on the bottom.
 *           foreground_image_filename     [IN] The image to be collaged on the top.
 *           output_collage_image_filename [IN] The output, always the same size as the background image.
 *           row_offset                    [IN] The row of the background image on which the top-left 
 *                                              corner of the foreground image should appear, 
 *                                              counting rows from the top (positive=downwards)
 *           col_offset                    [IN] The column of the background image on which the top-left 
 *                                              corner of the foreground image should appear, 
 *                                              counting columns from the left (positive=rightwards)
 *           scale                         [IN] The scaling factor that should be applied to the foreground image
 *                                              prior to overlaying it on the background image.
 */ 
int 
bmp_collage( char* background_image_filename,     char* foreground_image_filename, 
             char* output_collage_image_filename, int row_offset,                  
             int col_offset,                      float scale );
                    
