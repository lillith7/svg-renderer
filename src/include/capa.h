#pragma once

#include <stdint.h>

typedef struct capa_s {
    uint32_t* imagen;
    uint16_t ancho;
    uint16_t altura;
    uint16_t x;
    uint16_t y;
} capa_t;

capa_t combinar_capas(capa_t capa_superior, capa_t capa_inferior);