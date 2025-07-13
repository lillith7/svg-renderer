#pragma once

#include <stdint.h>

uint32_t promediar_colores(const uint32_t colora, const uint32_t colorb);

uint32_t promediar_colores_multiples(uint8_t numero, uint32_t* colores);

uint32_t mezclar_rgba(uint32_t color_a, uint32_t color_b);
