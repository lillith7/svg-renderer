#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include <ppm.h>
#include <circulo.h>
#include <pixel.h>
#include <color.h>
#include <capa.h>

int main(int argc, char** argv) {

    if (argc < 3) {
        puts("Uso: image inputFile.svg outputFile.ppm");
        return 1;
    }

    // cargar el archivo svg y obtener su ancho y altura

    LIBXML_TEST_VERSION


    xmlDocPtr svg;
    xmlNodePtr nodo;
    svg = xmlParseFile(argv[1]);
    if (svg == NULL) {
        puts("no se pudo parsar el archivo svg");
        return 1;
    }

    nodo = xmlDocGetRootElement(svg);

    if (!nodo) {
        puts("el archivo está vacio");
        return 0;
    }

    if (strcmp(nodo->name,"svg")) {
        puts("el archivo no es un svg");
        return 0;
    }

    unsigned int ancho = atoi(xmlGetProp(nodo, "width"));
    unsigned int altura = atoi(xmlGetProp(nodo, "height"));

    printf("ancho: %d\naltura: %d\n", ancho, altura);
    
    // 0xff000000 alfa
    // 0x00ff0000 azul
    // 0x0000ff00 verde
    // 0x000000ff rojo

    // tiene el ancho y la altura del nodo svg, ahora tiene que recorrer los nodos secundarios

    nodo = nodo->xmlChildrenNode;

    capa_t fondo;
    fondo.ancho = ancho;
    fondo.altura = altura;
    fondo.imagen = malloc(ancho*altura*4);

    for (uint32_t i = 0; i < ancho*altura; i++) {
        fondo.imagen[i] = 0xffffffff;
    }

    while (nodo) {

        capa_t capa;
        capa.ancho = ancho;
        capa.altura = altura;
        capa.imagen = malloc(ancho*altura*4);

        for (uint32_t i = 0; i < ancho*altura; i++) {
            capa.imagen[i] = 0x00000000;
        }

        if(!strcmp(nodo->name,"circle")) {
            const unsigned int radio = atoi(xmlGetProp(nodo, "r"));
            const unsigned int x = atoi(xmlGetProp(nodo, "cx"));
            const unsigned int y = atoi(xmlGetProp(nodo, "cy"));
            circulo(x,y,radio,parsar_cadena_de_color(xmlGetProp(nodo,"fill")),ancho,altura,capa.imagen);
        }

        fondo = combinar_capas(capa, fondo);

        nodo = nodo->next;
    }

    unsigned char* datos_ppm = convertir_imagen_rgba_a_datos_ppm(ancho, altura, fondo.imagen, false);
    escribir_ppm(argv[2], ancho, altura, datos_ppm);



    // capa_t bg;
    // bg.ancho = 500;
    // bg.altura = 500;
    // bg.imagen = malloc(500*500*4);

    // for (uint32_t i = 0; i < 500*500; i++) {
    //     bg.imagen[i] = 0xffffffff;
    // }

    // capa_t capa_a;
    // capa_a.ancho = 500;
    // capa_a.altura = 500;
    // capa_a.imagen = malloc(500*500*4);

    // circulo(0,0,400,0xff00ff00,500,500,capa_a.imagen);

    // capa_a = combinar_capas(capa_a, bg);

    // capa_t capa_b;
    // capa_b.ancho = 500;
    // capa_b.altura = 500;
    // capa_b.imagen = malloc(500*500*4);

    // circulo(250,250,100,0x6f0000ff,500,500,capa_b.imagen);

    // capa_t nueva_capa = combinar_capas(capa_b, capa_a);

    // unsigned char* datos_ppm = convertir_imagen_rgba_a_datos_ppm(500, 500, nueva_capa.imagen, false);
    // escribir_ppm(argv[2], 500, 500, datos_ppm);



    return 0;
}
