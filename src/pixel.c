#include <pixel.h>

void poner_pixel(const unsigned int x, const unsigned int y, const unsigned int ancho, const unsigned int color, unsigned int* imagen) {
    imagen[(x+(y*ancho))] = color;
}