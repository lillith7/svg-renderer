#include <circulo.h>

#include <distancia.h>
#include <pixel.h>
#include <multisample.h>
#include <color.h>
#include <capa.h>
#include <bitwise.h>

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

// color es un arreglo con tres elementos para r, g, y b que van de 0 a 255
// "ancho" y "altura" son el ancho y la altura de la imagen, no el circulo
void dibujar_circulo(int32_t x, int32_t y, double radio, uint32_t color, capa_t capa, bool usar_multisampling) {

    // establecer el cuadrado delimitador
    int32_t xmin = x-radio;
    if (xmin<0) {
        xmin = 0;
    }

    int32_t xmax = x+radio;
    if (xmax>capa.ancho) {
        xmax = capa.ancho;
    }

    int32_t ymin = y-radio;
    if (ymin<0) {
        ymin=0;
    }

    int32_t ymax = y+radio;
    if(ymax>capa.altura) {
        ymax=capa.altura;
    }

    if (!usar_multisampling) {
        // versión sin multisampling, usada con "stroke"
        for (uint32_t x_actual = xmin; x_actual < xmax; x_actual++){
            for (uint32_t y_actual = ymin; y_actual < ymax; y_actual++) {
                if (distancia(x, y, x_actual, y_actual) <= radio) {
                    poner_pixel(x_actual, y_actual, color, capa);
                }
            }
        }

    } else {
        
        for (uint32_t x_actual = xmin; x_actual < xmax; x_actual++){
            for (uint32_t y_actual = ymin; y_actual < ymax; y_actual++) {
                // el multisampling checa si 4 puntos separados están en el círculo
                double puntos = 4;

                for (uint8_t i = 0; i < 2; i++) {
                    for (uint8_t j = 0; j < 2; j++){ 
                        if (distancia(x, y, x_actual + i * 0.5 + 0.25, y_actual + j * 0.5 + 0.25) <= radio) {
                            puntos--;
                        }
                        
                    }
                }

                // 4 puntos significa que ninguno de los puntos fueron en el círculo
                if (puntos == 4) {
                    continue;
                }

                // mezclar el alfa según el número de puntos
                double valor_alfa = conseguir_byte(color,3)/255.0f;
                valor_alfa = valor_alfa * ((4 - puntos) / 4.0);

                double alfa_base = conseguir_byte(color,3)/255.0f;
                double cobertura = (4 - puntos) / 4.0;
                double alfa_final = alfa_base * cobertura;

                // desnormalizar el valor alfa y insertarlo
                uint32_t color_final = poner_byte(color,alfa_final*255.0f,3);
                poner_pixel(x_actual, y_actual, color_final, capa);

            }
        }
    }
    return;
}
