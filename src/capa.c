#include <capa.h>

#include <color.h>
#include <pixel.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

capa_t combinar_capas(capa_t capa_superior, capa_t capa_inferior){
    capa_t nueva_capa;
    nueva_capa.imagen = malloc(capa_inferior.ancho*capa_inferior.altura*4);
    nueva_capa.ancho = capa_inferior.ancho;
    nueva_capa.altura = capa_inferior.altura;
    nueva_capa.x = 0;
    nueva_capa.y = 0;

    for (uint16_t x = 0; x < capa_inferior.ancho; x++) {
        for (uint16_t y = 0; y < capa_inferior.altura; y++) {
            poner_pixel(
                x,
                y,
                mezclar_rgba(capa_superior.imagen[(x+(y*capa_inferior.ancho))], capa_inferior.imagen[(x+(y*capa_inferior.ancho))]),
                nueva_capa
            );
        }
    }

    free(capa_inferior.imagen);
    free(capa_superior.imagen);

    return nueva_capa;
}

capa_t clonar_capa(capa_t capa) {
    capa_t nueva_capa;

    nueva_capa.imagen = malloc(capa.ancho*capa.altura*4);

    memcpy(nueva_capa.imagen,capa.imagen,capa.ancho*capa.altura*4);

    nueva_capa.ancho = capa.ancho;
    nueva_capa.altura = capa.altura;
    nueva_capa.x = capa.x;
    nueva_capa.y = capa.y;

    return nueva_capa;
}