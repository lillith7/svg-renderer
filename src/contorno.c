#include <contorno.h>

#include <capa.h>
#include <circulo.h>
#include <multisample.h>

#include <stdint.h>
#include <stdlib.h>

// REESCRIBIR ESTE CÓDIGO PRONTO, ES COMPLETAMENTE HORRIBLE
capa_t dibujar_contorno(capa_t capa, uint32_t color, double ancho) {
    capa_t capa_actual;
    capa_actual.x = capa.x;
    capa_actual.y = capa.y;
    capa_actual.imagen = malloc(capa.altura*capa.ancho*4);
    capa_actual.altura = capa.altura;
    capa_actual.ancho = capa.ancho;


    for(uint32_t x = 1; x < capa.ancho-1; x++) {
        for(uint32_t y = 1; y < capa.altura-1; y++) {
            if(capa.imagen[x+(y*capa.ancho)]) {
                if(
                    !(capa.imagen[(x+1)+(y*capa.ancho)]) || 
                    !(capa.imagen[(x-1)+(y*capa.ancho)]) || 
                    !(capa.imagen[x+((y+1)*capa.ancho)]) || 
                    !(capa.imagen[x+((y-1)*capa.ancho)])) {
                        dibujar_circulo(x,y,ancho,color,capa_actual,true);
                    }
            }
        }
    }

    return combinar_capas(capa_actual,capa);
}
