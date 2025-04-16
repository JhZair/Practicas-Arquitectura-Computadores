#include <iostream>
#include <bitset>
#include <cmath>
#include <cstdint>
using namespace std;

const int BITS = 32;
const int SESGO = 127;

union FloatBits {
    float valor;
    uint32_t binario;
}; 


void imprimirBits(const string& etiqueta,float valor) {
    FloatBits fb; 
    fb.valor = valor;
    cout<< etiqueta <<": " << bitset<BITS>(fb.binario)<< " ( " << valor << ")\n";  
}

void descomponer(float valor,int& signo,int& exponente, uint32_t& mantisa) { 
    FloatBits fb;
    fb.valor = valor;
    signo =(fb.binario >> 31) & 1;
    exponente =(fb.binario >> 23) & 0xFF;
    mantisa = fb.binario & 0x7FFFFF;     
    if (exponente != 0) { 
        mantisa |= (1 << 23); 
    }
}

float armarFloat(int signo,int exponente, uint32_t mantisa) {
    if (mantisa & (1 <<24)) { 
        mantisa >>=1;  
        exponente++;   
    }
    mantisa &=0x7FFFFF;
    uint32_t resultadoBinario =(signo <<31) | ((exponente & 0xFF) << 23) | mantisa;
    FloatBits fb;        
    fb.binario = resultadoBinario;
    return fb.valor;    
}


float dividir(float dividendo, float divisor) {
    imprimirBits("Dividendo",dividendo);
    imprimirBits("Divisor ", divisor);               

    if (dividendo == 0.0f) return 0.0f;
    if (divisor == 0.0f) return INFINITY;
    int signoA, exponenteA;
    int signoB, exponenteB;
    uint32_t mantisaA,mantisaB;

    descomponer(dividendo, signoA, exponenteA,mantisaA);
    descomponer(divisor,signoB, exponenteB, mantisaB);

    int signoResultado = signoA ^ signoB;
    int exponenteResultado = exponenteA - exponenteB+SESGO;
    if (exponenteResultado >= 255) {      
        cout << "Overflow\n";
        return INFINITY;
    }
    if (exponenteResultado<= 0) {
        cout << "Underflow\n";
        return 0.0f;
    }
    float mantisaResultadoFloat = static_cast<float>(mantisaA) / mantisaB;
    uint32_t mantisaResultado = static_cast<uint32_t>(mantisaResultadoFloat * (1 << 23));
    while ((mantisaResultado & (1<< 23)) == 0 && mantisaResultado != 0) {
        mantisaResultado <<= 1;
        exponenteResultado--;  
    }
    float resultado = armarFloat(signoResultado, exponenteResultado, mantisaResultado);
    imprimirBits("Resultado ", resultado);     
   
    return resultado; 
}

int main() {
    float dividendo, divisor;
    cout << "Ingresa el dividendo: ";
    cin >> dividendo;
    cout << "Ingresa el divisor: ";
    cin >> divisor;
    float resultado = dividir(dividendo, divisor);
    cout << "Resultado del algoritmo: "<< resultado << endl;
    cout << "Resultado con operador de c++: " << (dividendo/divisor) << endl;

    return 0;
}

//g++ -o arq2 Arq2.cpp
