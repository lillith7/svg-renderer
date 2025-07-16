#include <bitwise.h>

#include <stdint.h>

uint64_t poner_byte(uint64_t numero, uint8_t byte, uint8_t posicion) {
    return (numero & (~(0xff<<(posicion*8)))) | (uint64_t)(byte<<posicion*8);
}

uint8_t conseguir_byte(uint64_t numero, uint8_t posicion) {
    return (numero >> (posicion*8)) & 0xff;
}

