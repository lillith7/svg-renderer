#pragma once

#include <stdbool.h>
#include <stdint.h>
uint8_t* convertir_imagen_rgba_a_datos_ppm (uint32_t ancho, uint32_t altura, uint32_t* datos_rgba, bool fondo_ajedrezado);

bool escribir_ppm(const char* filename, uint32_t ancho, uint32_t altura, uint8_t* image_data);
