#pragma once

#include <stdbool.h>

unsigned char* convertir_imagen_rgba_a_datos_ppm (const unsigned int ancho, const unsigned int altura, const unsigned int* datos_rgba, bool fondo_ajedrezado);
bool escribir_ppm(const char* filename, const unsigned int ancho, const unsigned int altura, const unsigned char* image_data);