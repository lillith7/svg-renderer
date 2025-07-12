#include <distancia.h>

#include <math.h>

// calcular la distancia entre 2 puntos (original x, original y y destino x, destino y)
double distancia(const double xo, const double yo, const double xd, const double yd) {
    return sqrt(pow(xo - xd, 2) + pow(yo - yd, 2));
}
