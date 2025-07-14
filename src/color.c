#include <color.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint32_t promediar_colores(const uint32_t colora, const uint32_t colorb) {
    uint32_t a = (((colora >> 24) & 0xff) + ((colorb >> 24) & 0xff)) / 2;
    uint32_t b = (((colora >> 16) & 0xff) + ((colorb >> 16) & 0xff)) / 2;
    uint32_t g = (((colora >> 8) & 0xff) + ((colorb >> 8) & 0xff)) / 2;
    uint32_t r = (((colora) & 0xff) + ((colorb) & 0xff)) / 2;

    uint32_t color = 0;
    color += a << 24;
    color += b << 16;
    color += g << 8;
    color += r;
    return color;
}

uint32_t promediar_colores_multiples(uint8_t numero, uint32_t* colores) {
    uint64_t a = 0;
    uint64_t b = 0;
    uint64_t g = 0;
    uint64_t r = 0;

    for (uint8_t i = 0; i < numero; i++) {
        a += (colores[i] >> 24) & 0xff;
        b += (colores[i] >> 16) & 0xff;
        g += (colores[i] >> 8) & 0xff;
        r += (colores[i]) & 0xff;
    }

    a /= numero;
    b /= numero;
    g /= numero;
    r /= numero;

    uint32_t color = 0;
    color += a << 24;
    color += b << 16;
    color += g << 8;
    color += r;

    return color;
}

// color a está por encima del color b
uint32_t mezclar_rgba(uint32_t color_a, uint32_t color_b) {
    uint8_t a_a = (color_a >> 24) & 0xFF;
    uint8_t a_b = (color_a >> 16) & 0xFF;
    uint8_t a_g = (color_a >> 8) & 0xFF;
    uint8_t a_r = color_a & 0xFF;

    uint8_t b_a = (color_b >> 24) & 0xFF;
    uint8_t b_b = (color_b >> 16) & 0xFF;
    uint8_t b_g = (color_b >> 8) & 0xFF;
    uint8_t b_r = color_b & 0xFF;

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
            color = (color & 0xFF00FFFF) | ((uint32_t)((strtol(cadena_actual,NULL,16)<<4)+strtol(cadena_actual,NULL,16)) << 16);

            cadena_actual[0] = cadena[2]; // verde
            color = (color & 0xFFFF00FF) | ((uint32_t)((strtol(cadena_actual,NULL,16)<<4)+strtol(cadena_actual,NULL,16)) << 8);

            cadena_actual[0] = cadena[1]; // rojo
            color = (color & 0xFFFFFF00) | ((uint32_t)((strtol(cadena_actual,NULL,16)<<4)+strtol(cadena_actual,NULL,16)));

            return color;
        }

        if (strlen(cadena) == 5) { // formato #fa88 (#rgba)
            uint8_t cadena_actual[2] = {0,0};

            cadena_actual[0] = cadena[3]; // azul
            color = (color & 0xFF00FFFF) | ((uint32_t)((strtol(cadena_actual,NULL,16)<<4)+strtol(cadena_actual,NULL,16)) << 16);

            cadena_actual[0] = cadena[2]; // verde
            color = (color & 0xFFFF00FF) | ((uint32_t)((strtol(cadena_actual,NULL,16)<<4)+strtol(cadena_actual,NULL,16)) << 8);

            cadena_actual[0] = cadena[1]; // rojo
            color = (color & 0xFFFFFF00) | ((uint32_t)((strtol(cadena_actual,NULL,16)<<4)+strtol(cadena_actual,NULL,16)));

            cadena_actual[0] = cadena[4]; // alfa
            color = (color & 0x00FFFFFF) | ((uint32_t)((strtol(cadena_actual,NULL,16)<<4)+strtol(cadena_actual,NULL,16)) << 24);

            return color;
        }
    }
}
