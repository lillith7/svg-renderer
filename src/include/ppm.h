#pragma once

#include <capa.h>

#include <stdbool.h>
#include <stdint.h>

uint8_t* convertir_imagen_rgba_a_datos_ppm (capa_t capa, bool fondo_ajedrezado);

bool escribir_ppm(const char* filename, uint32_t ancho, uint32_t altura, uint8_t* image_data);
