#pragma once

#include <stdint.h>

typedef struct capa_s {
    uint32_t* imagen;
    uint32_t ancho;
    uint32_t altura;
    uint32_t x;
    uint32_t y;
} capa_t;

capa_t combinar_capas(capa_t capa_superior, capa_t capa_inferior);
