#include <cstdlib>
#include <cassert>


#define PNG_DEBUG 3

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)
#include <png.h>
#elif __APPLE__
#include <libpng/png.h>
#endif


#include "debug.h"
#include "error.h"

#pragma warning(disable : 4996)

// Lee un fichero .png situado en la ruta especificada en el primer par?etro, y guarda informaci? 
// variada en las variables pasadas como punteros.
//
// tamx: Tama? X en p?els
// tamy: Tama? Y en p?els

//TODO: Añadir constructor y destructor para limpiar en caso de error
void read_png_file(const char *file_name, int *tamx, int *tamy)
{
	
  assert(file_name && tamx && tamy);

  // open file and test for it being a png
  FILE* fp = fopen(file_name, "rb") ;
  
  if (!fp) 
    throw custom_error("[read_png_file] File is not recognized as a PNG file", file_name);

  char header[8]; // 8 is the maximum size that can be checked
  fread(header, 1, 8, fp);
  if(png_sig_cmp((png_bytep)header, 0, 8)) 
    throw custom_error("[read_png_file] File is not recognized as a PNG file", file_name);

  // initialize stuff 
  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr) 
    throw custom_error("[read_png_file] png_create_read_struct failed");

  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) 
    throw custom_error("[read_png_file] png_create_info_struct failed");

  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, 8);

  png_read_info(png_ptr, info_ptr);
  
  *tamx = png_get_image_width(png_ptr, info_ptr);
  *tamy = png_get_image_height(png_ptr, info_ptr);

  fclose(fp);
  png_destroy_info_struct(png_ptr, &info_ptr);
  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
  png_free(png_ptr, NULL);
 
}
