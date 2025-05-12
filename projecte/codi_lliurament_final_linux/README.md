# MP 2024-25

Port a Linux del código para la entrega final del proyecto.

# Instalación de dependencias

## Ubuntu/Debian

`sudo apt install build-essential cmake libsdl2-dev libsdl2-ttf-dev libsdl2-mixer-dev libsdl2-image-dev libsdl2-gfx-dev libpng-dev libfreetype-dev`

## Fedora

`sudo dnf install gcc gcc-c++ make cmake libsdl2-devel libsdl2-ttf-devel libsdl2-mixer-devel libsdl2-image-devel libsdl2-gfx-devel libpng-devel libfreetype-devel`

# Compilación

(Desde la carpeta que contiene este README)

`make`

# Ejecución

(Desde la carpeta que contiene este README)

`bash ./run.sh`

(O, desde la carpeta '1. Resources')

`../build/codi_lliurament_final`

**Importante**: Si no se ejecuta de alguna de estas dos maneras, las imágenes podrían no mostrarse adecuadamente.

# Debugging

Con gdb: `cd '1. Resources' && gdb ../build/codi_lliurament_final`

Con tu IDE: necesitarás configurar el directorio de trabajo actual a `1. Resources` para que las imágenes se
muestren correctamente.