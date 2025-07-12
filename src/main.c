#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include <ppm.h>
#include <circulo.h>
#include <pixel.h>
#include <color.h>

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

    unsigned int* imagen = malloc(ancho*altura*4);
    // 0xff000000 alfa
    // 0x00ff0000 azul
    // 0x0000ff00 verde
    // 0x000000ff rojo
    if (!imagen) {
        puts("no se pudo asignar memoria");
        return 1;
    }

    for (unsigned int i = 0; i < ancho*altura; i++) {
        imagen[i] = 0xffffffff;
    }

    // tiene el ancho y la altura del nodo svg, ahora tiene que recorrer los nodos secundarios

    nodo = nodo->xmlChildrenNode;

    while (nodo) {
        if(!strcmp(nodo->name,"circle")) {
            const unsigned int radio = atoi(xmlGetProp(nodo, "r"));
            const unsigned int x = atoi(xmlGetProp(nodo, "cx"));
            const unsigned int y = atoi(xmlGetProp(nodo, "cy"));
            circulo(x,y,radio,combinar_colores(0xff0000ff,0xffffffff),ancho,altura,imagen);
        }
        nodo = nodo->next;
    }

    unsigned char* datos_ppm = convertir_imagen_rgba_a_datos_ppm(ancho, altura, imagen, false);
    escribir_ppm(argv[2], ancho, altura, datos_ppm);

    return 0;
}
