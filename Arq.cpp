#include <iostream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

void mostrarBits(const vector<bool>& bits){
    for (int i = bits.size() - 1; i >= 0; --i) {
        cout << bits[i];
    }
}

vector<bool> aBinario(int valor, int n) {
    vector<bool> bits(n, 0);
    if (valor < 0) valor = (1 << n) + valor;
    for (int i = 0; i < n; ++i) {
        bits[i] = (valor >> i) & 1;
    }
    return bits; 
}
int aEntero(const vector<bool>& bits){
    int n = bits.size();
    int resultado = 0;
    for (int i = 0; i < n; ++i) {
        if (bits[i]) {
            resultado |= (1 << i);   
        }
    }

    if (bits[n - 1]) {
        resultado -= (1 << n);
    }
    return resultado;
}

vector<bool> suma(const vector<bool>& a, const vector<bool>& b) {
    int n = a.size();
    vector<bool> resultado(n, 0);
    bool acarreo = 0;
    for (int i = 0; i < n; ++i) {
        bool sumaBit = a[i] ^ b[i] ^ acarreo;
        acarreo = (a[i] & b[i]) | (a[i] & acarreo) | (b[i] & acarreo);
        resultado[i] = sumaBit;
    }
    return resultado;
}

vector<bool> resta(const vector<bool>& a, const vector<bool>& b){
    int n = b.size();
    vector<bool> negB = b;
    for (int i = 0; i < n; ++i) {
        negB[i] = !negB[i];
    }
    vector<bool> uno(n, 0);
    uno[0] = 1;  
    negB = suma(negB, uno);
    return suma(a, negB); 
}
 
void desplazamiento(vector<bool>& A, vector<bool>& Q, bool& Q_1) { 
    bool msb_A = A.back();
    bool lsb_Q = Q[0];
    for (int i = 0; i < Q.size() - 1; ++i) {
        Q[i] = Q[i + 1];
    }
    Q[Q.size() - 1] = A[0];

    for (int i = 0; i < A.size() - 1; ++i) {   
        A[i] = A[i + 1];
    }
    A[A.size() - 1] = msb_A;
    Q_1 = lsb_Q;
}

void multiplicacionBooth(int multiplicando, int multiplicador, int n){ 
    vector<bool> M = aBinario(multiplicando, n); 
    vector<bool> Q = aBinario(multiplicador, n);
    vector<bool> A(n, 0);
    bool Q_1 = 0;

    cout << "\nValores iniciales:\n";
    cout<< "A: "; mostrarBits(A);  
    cout<< ", Q: "; mostrarBits(Q); 
    cout << ", M: "; mostrarBits(M); 
    cout << ", Q-1: " <<Q_1 << "\n";

    int contador = n;
    while (contador--) {
        int Q0 = Q[0];
        if (Q0 == 1 && Q_1 == 0) {
            A = resta(A, M);
            cout << "A = A - M -> ";
        } else if (Q0 == 0 && Q_1 == 1) {
            A = suma(A, M);
            cout << "A = A + M -> ";
        } else {
            cout << "No cambia A ->   ";
        }
        cout << "A: ";mostrarBits(A);
        cout<< ", Q: ";mostrarBits(Q);  
        cout << ", Q-1: " <<Q_1 << "\n"; 

        desplazamiento(A, Q, Q_1);

        cout << "Desp. A: "; mostrarBits(A);
        cout << ", Q: "; mostrarBits(Q);
        cout << ", Q-1: " << Q_1 << "\n";
    }

    vector<bool> resultado(2 * n);
    for (int i = 0; i < n; ++i) {
        resultado[i] = Q[i];
        resultado[i + n] = A[i];
    }

    cout << "\nResultado binario (A|Q): ";
    mostrarBits(resultado);
    int valor = aEntero(resultado);
    cout <<"\nResultado entero final: " << valor<< "\n";
}


int main(){
    int multiplicando, multiplicador, n;

    cout<< "Ingrese el número de bits (n): ";
    cin >> n;

    cout<< "Ingrese el multiplicando: ";
    cin >> multiplicando;

    cout << "Ingrese el multiplicador: ";
    cin >>multiplicador;

    multiplicacionBooth(multiplicando, multiplicador, n);

    return 0;
}
//g++ -o booth_dinamico Arq.cpp
