#include <ppm.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint8_t* convertir_imagen_rgba_a_datos_ppm (uint32_t ancho, uint32_t altura, uint32_t* datos_rgba, bool fondo_ajedrezado) {
    uint8_t* datos_ppm = malloc(ancho * altura * 3);

    for (uint32_t y = 0; y < altura; y++) {
        for (uint32_t x = 0; x < ancho; x++) {
            datos_ppm[((y * ancho) + x)*3] = (unsigned char)((datos_rgba[(y * ancho) + x]) & 0xFF);
            datos_ppm[(((y * ancho) + x)*3) + 1] = (unsigned char)((datos_rgba[(y * ancho) + x] >> 8) & 0xFF);
            datos_ppm[(((y * ancho) + x)*3) + 2] = (unsigned char)((datos_rgba[(y * ancho) + x] >> 16) & 0xFF);
        }
    }

    return datos_ppm;
}

// image_data es una lista de bytes de rgb que van entre 0 y 255. está ordenada de izquizerda a derecha y de arriba a abajo
bool escribir_ppm(const char* filename, uint32_t ancho, uint32_t altura, uint8_t* image_data) {
    FILE* archivo_ppm;
    archivo_ppm = fopen(filename, "wb");
    if (!archivo_ppm) {
        printf("no se pudo acceder al archivo %s\n", filename);
        return false;
    }
    fprintf(archivo_ppm, "P6\n");
    fprintf(archivo_ppm, "%d\n", ancho);
    fprintf(archivo_ppm, "%d\n", altura);
    fprintf(archivo_ppm, "255\n");
    fwrite(image_data, ancho*altura*3, 1, archivo_ppm);
    fclose(archivo_ppm);

    return true;
}
