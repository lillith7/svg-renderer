#include <color.h>

unsigned int combinar_colores(const int colora, const int colorb) {
    unsigned int a = (((colora >> 24) & 0xff) + ((colorb >> 24) & 0xff)) / 2;
    unsigned int b = (((colora >> 16) & 0xff) + ((colorb >> 16) & 0xff)) / 2;
    unsigned int g = (((colora >> 8) & 0xff) + ((colorb >> 8) & 0xff)) / 2;
    unsigned int r = (((colora) & 0xff) + ((colorb) & 0xff)) / 2;

    unsigned int color = 0;
    color += a << 24;
    color += b << 16;
    color += g << 8;
    color += r;
    return color;
}
