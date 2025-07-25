#pragma once

#include <capa.h>

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define COMANDO_MOVE 0 // M x y OR m dx dy
#define COMANDO_LINE 1 // L x y OR l dx dy
#define COMANDO_HORIZONTAL 2 // H x OR h dx
#define COMANDO_VERTICAL 3 // V y OR v dy
#define COMANDO_CLOSE 4 // Z OR z
#define COMANDO_CURVE 5 // C x1 y1 x2 y2 ex ey OR c dx1 dy1 dx2 dy2 dex dey
#define COMANDO_ARC 6// A rx ry x-rotate large-flag sweep-flag x y OR a ... dx dy

typedef struct punto_path_s {
    uint8_t tipo;
    bool relativo;
    bool large_arc; // arc
    bool sweep; // arc
    double x;
    double y;

    double xa; // curve
    double xb; // curve
    double ya; // curve
    double yb; // curve
    double rx; // arc
    double ry; // arc
} punto_path_t;


typedef struct path_s {
    size_t tamano;
    punto_path_t* arreglo;
} path_t;
