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
            double puntos = 4;

            for (uint8_t i = 0; i < 2; i++) {
                for (uint8_t j = 0; j < 2; j++){ 
                    if (distancia(x, y, x_actual + i * 0.5 + 0.25, y_actual + j * 0.5 + 0.25) <= radio) {
                        puntos--;
                    }
                    
                }
            }

            if (puntos == 4) {
                continue;
            }

            double valor_alfa = ((color >> 24) & 0xFF)/255;
            // valor_alfa = reducir_alfa(valor_alfa, puntos, 4);
            valor_alfa = valor_alfa * ((4 - puntos) / 4.0);

            double alfa_base = ((color >> 24) & 0xFF) / 255.0;
            double cobertura = (4 - puntos) / 4.0;
            double alfa_final = alfa_base * cobertura;

            uint32_t color_final = (color & 0x00FFFFFF) | ((uint32_t)(alfa_final * 255.0) << 24);
            poner_pixel(x_actual, y_actual, ancho, color_final, imagen);



        }
    }

    return;

#endif
}
