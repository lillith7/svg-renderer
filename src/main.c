#include <ppm.h>
#include <circulo.h>
#include <pixel.h>
#include <color.h>
#include <capa.h>
#include <multisample.h>
#include <contorno.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

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
        return 1;
    }

    if (strcmp(nodo->name,"svg")) {
        puts("el archivo no es un svg");
        return 1;
    }

    uint32_t ancho = atoi(xmlGetProp(nodo, "width"));
    uint32_t altura = atoi(xmlGetProp(nodo, "height"));

    printf("ancho: %d\naltura: %d\n", ancho, altura);
    
    // 0xff000000 alfa
    // 0x00ff0000 azul
    // 0x0000ff00 verde
    // 0x000000ff rojo

    // tiene el ancho y la altura del nodo svg, ahora tiene que recorrer los nodos secundarios

    nodo = nodo->xmlChildrenNode;

    // cada capa se combinará con el fondo después de dibujarla

    capa_t fondo;
    fondo.ancho = ancho;
    fondo.altura = altura;
    fondo.imagen = malloc(ancho*altura*sizeof(uint32_t));

    memset(fondo.imagen,0xff,ancho*altura*sizeof(uint32_t));

    while (nodo) {

        capa_t capa;
        capa.ancho = ancho;
        capa.altura = altura;
        capa.imagen = malloc(ancho*altura*sizeof(uint32_t));

        memset(capa.imagen,0x00,ancho*altura*sizeof(uint32_t));

        if(!strcmp(nodo->name,"circle")) {
            const double radio = atof(xmlGetProp(nodo, "r"));
            const int32_t x = atoi(xmlGetProp(nodo, "cx"));
            const int32_t y = atoi(xmlGetProp(nodo, "cy"));
            
            // si "stroke" está activado, dibujar el circulo sin multisampling y dibujar el contorno
            if (xmlGetProp(nodo,"stroke")) {
                dibujar_circulo(x,y,radio,parsar_cadena_de_color(xmlGetProp(nodo,"fill")),capa, false);

                capa = dibujar_contorno(capa,parsar_cadena_de_color(xmlGetProp(nodo,"stroke")),atof(xmlGetProp(nodo,"stroke-width")));
            } else {
                dibujar_circulo(x,y,radio,parsar_cadena_de_color(xmlGetProp(nodo,"fill")),capa, ACTIVAR_MULTISAMPLE);
            }
        }

        fondo = combinar_capas(capa, fondo);

        nodo = nodo->next;
    }

    uint8_t* datos_ppm = convertir_imagen_rgba_a_datos_ppm(fondo, false);
    
    if (escribir_ppm(argv[2], ancho, altura, datos_ppm)) {
        return 0; // el archivo fue escrito correctamente
    } else {
        return 1;
    }
}
