#pragma once

//! Lee un fichero .png situado en la ruta especificada en el primer par?etro, y guarda informaci? variada en las variables
//! pasadas como punteros.
//!
//! tamx: Tama? X en p?els
//! tamy: Tama? Y en p?els
void read_png_file(const char *file_name, int *tamx, int *tamy) ;
