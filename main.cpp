#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Definición del nodo del árbol
struct Nodo {
    string valor;
    Nodo* izquierda;
    Nodo* derecha;
    Nodo(string v) : valor(v), izquierda(nullptr), derecha(nullptr) {}
};

// Función para insertar en el árbol binario
Nodo* insertar(Nodo* raiz, string valor) {
    if (!raiz) return new Nodo(valor);
    if (valor < raiz->valor)
        raiz->izquierda = insertar(raiz->izquierda, valor);
    else
        raiz->derecha = insertar(raiz->derecha, valor);
    return raiz;
}

// Recorrido inorden para mostrar el árbol ordenado
void inorden(Nodo* raiz) {
    if (!raiz) return;
    inorden(raiz->izquierda);
    cout << raiz->valor << " ";
    inorden(raiz->derecha);
}

// Función para imprimir el árbol en formato de estructura visual
void imprimirArbol(Nodo* raiz, int espacio = 0, int separacion = 6) {
    if (!raiz) return;
    espacio += separacion;
    imprimirArbol(raiz->derecha, espacio);
    cout << string(espacio, ' ') << raiz->valor << endl;
    imprimirArbol(raiz->izquierda, espacio);
}

int main() {
    vector<string> elementos;
    cout << "Ingrese 10 caracteres o numeros enteros separados por espacio: ";
    for (int i = 0; i < 10; i++) {
        string entrada;
        cin >> entrada;
        elementos.push_back(entrada);
    }

    // Crear árbol binario
    Nodo* raiz = nullptr;
    for (const auto& elem : elementos) {
        raiz = insertar(raiz, elem);
    }

    // Mostrar elementos en orden
    cout << "\nElementos ordenados: ";
    inorden(raiz);
    cout << "\n\nEstructura del arbol:\n";
    imprimirArbol(raiz);
    
    return 0;
}
