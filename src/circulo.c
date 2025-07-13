#include <circulo.h>

#include <distancia.h>
#include <pixel.h>
#include <multisample.h>
#include <color.h>

#include <stdint.h>
#include <stdio.h>
#include <math.h>

// color es un arreglo con tres elementos para r, g, y b que van de 0 a 255
// "ancho" y "altura" son el ancho y la altura de la imagen, no el circulo
void circulo(int x, int y, unsigned int radio, unsigned int color, unsigned int ancho, unsigned int altura, unsigned int* imagen) {

    int xmin = x-radio;
    if (xmin<0) {
        xmin = 0;
    }

    int xmax = x+radio;
    if (xmax>ancho) {
        xmax = ancho;
    }

    int ymin = y-radio;
    if (ymin<0) {
        ymin=0;
    }

    int ymax = y+radio;
    if(ymax>altura) {
        ymax=altura;
    }

#ifndef ACTIVAR_MULTISAMPLE

    for (unsigned int x_actual = xmin; x_actual < xmax; x_actual++){
        for (unsigned int y_actual = ymin; y_actual < ymax; y_actual++) {
            if (distancia(x, y, x_actual, y_actual) <= radio) {
                poner_pixel(x_actual, y_actual, ancho, color, imagen);
            }
        }
    }

    return;

#endif
#ifdef ACTIVAR_MULTISAMPLE

    for (unsigned int x_actual = xmin; x_actual < xmax; x_actual++){
        for (unsigned int y_actual = ymin; y_actual < ymax; y_actual++) {
            uint32_t colores[4] = {0,0,0,0};

            for (uint8_t i = 0; i < 2; i++) {
                for (uint8_t j = 0; j < 2; j++){ 
                    if (distancia(x, y, x_actual+i, y_actual+j) <= radio) {
                        colores[i+j] = color;
                    }
                }
            }

            poner_pixel(x_actual, y_actual, ancho, promediar_colores_multiples(4,colores), imagen);


        }
    }

    return;

#endif
}
