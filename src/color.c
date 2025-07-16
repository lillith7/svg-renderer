#include <color.h>

#include <bitwise.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// color a está por encima del color b
uint32_t mezclar_rgba(uint32_t color_a, uint32_t color_b) {

    uint8_t a_a = conseguir_byte(color_a,3);
    uint8_t a_b = conseguir_byte(color_a,2);
    uint8_t a_g = conseguir_byte(color_a,1);
    uint8_t a_r = conseguir_byte(color_a,0);

    uint8_t b_a = conseguir_byte(color_b, 3);
    uint8_t b_b = conseguir_byte(color_b, 2);
    uint8_t b_g = conseguir_byte(color_b, 1);
    uint8_t b_r = conseguir_byte(color_b, 0);

    // normalizar el valor alfa
    float a_a_norm = a_a / 255.0f;
    float b_a_norm = b_a / 255.0f;

    float res_a_norm = a_a_norm + b_a_norm * (1.0f - a_a_norm);
    
    // evitar la división por cero
    if (res_a_norm < 1e-6) {
        return 0x00000000;
    }

    // mezclar correctamente los colores
    uint8_t out_r = (uint8_t)(((a_r * a_a_norm + b_r * b_a_norm * (1.0f - a_a_norm)) / res_a_norm) + 0.5f);
    uint8_t out_g = (uint8_t)(((a_g * a_a_norm + b_g * b_a_norm * (1.0f - a_a_norm)) / res_a_norm) + 0.5f);
    uint8_t out_b = (uint8_t)(((a_b * a_a_norm + b_b * b_a_norm * (1.0f - a_a_norm)) / res_a_norm) + 0.5f);
    
    // desnormalizar el valor alfa
    uint8_t out_a = (uint8_t)(res_a_norm * 255.0f + 0.5f);

    // recombinar el color
    return ((uint32_t)out_a << 24) | ((uint32_t)out_b << 16) | ((uint32_t)out_g << 8) | (uint32_t)out_r;

}

uint32_t parsar_cadena_de_color(char* cadena) {
    uint32_t color = 0xff000000;
    if(cadena[0] == '#') { // formato #39c568, #fa8, #37fba937, o #82ba (rrggbb, rgb, rrggbbaa, o rgba)

        if (strlen(cadena) == 4) { // formato #fa8 (#rgb)
            uint8_t cadena_actual[2] = {0,0};

            cadena_actual[0] = cadena[3]; // azul
            color = poner_byte(color,(strtol(cadena_actual,NULL,16)<<4)+strtol(cadena_actual,NULL,16),2);

            cadena_actual[0] = cadena[2]; // verde
            color = poner_byte(color,(strtol(cadena_actual,NULL,16)<<4)+strtol(cadena_actual,NULL,16),1);

            cadena_actual[0] = cadena[1]; // rojo
            color = poner_byte(color,(strtol(cadena_actual,NULL,16)<<4)+strtol(cadena_actual,NULL,16),0);

            return color;
        }

        if (strlen(cadena) == 5) { // formato #fa88 (#rgba)
            uint8_t cadena_actual[2] = {0,0};

            cadena_actual[0] = cadena[4]; // alfa
            color = poner_byte(color,(strtol(cadena_actual,NULL,16)<<4)+strtol(cadena_actual,NULL,16),3);

            cadena_actual[0] = cadena[3]; // azul
            color = poner_byte(color,(strtol(cadena_actual,NULL,16)<<4)+strtol(cadena_actual,NULL,16),2);

            cadena_actual[0] = cadena[2]; // verde
            color = poner_byte(color,(strtol(cadena_actual,NULL,16)<<4)+strtol(cadena_actual,NULL,16),1);

            cadena_actual[0] = cadena[1]; // rojo
            color = poner_byte(color,(strtol(cadena_actual,NULL,16)<<4)+strtol(cadena_actual,NULL,16),0);

            return color;
        }
    }
}
