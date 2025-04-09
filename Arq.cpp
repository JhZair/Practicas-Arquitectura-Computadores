#include <iostream>
#include <bitset>
#include <cmath>
using namespace std;

const int bits = 4;

bitset<bits> aBinario(int valor) {
    if (valor < 0) {
        valor = (1 << bits) + valor;
    }
    return bitset<bits>(valor);
}

int aEntero(const bitset<bits>& b) {
    if (b[bits - 1] == 1) {
        return -((~b).to_ulong() + 1);
    } else {
        return b.to_ulong();
    }
}

bitset<bits> suma(const bitset<bits>& a, const bitset<bits>& b) {
    int resultado = aEntero(a) + aEntero(b);
    return aBinario(resultado);
}

bitset<bits> resta(const bitset<bits>& a, const bitset<bits>& b) {
    int resultado = aEntero(a) - aEntero(b);
    return aBinario(resultado);
}

