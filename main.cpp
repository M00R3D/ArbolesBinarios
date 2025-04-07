#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Definicion del nodo del arbol
struct Nodo {
    string valor;
    Nodo* izquierda;
    Nodo* derecha;
    Nodo(string v) : valor(v), izquierda(nullptr), derecha(nullptr) {}
};

// Funcion para insertar en el arbol binario
Nodo* insertar(Nodo* raiz, string valor) {
    if (!raiz) return new Nodo(valor);
    if (valor < raiz->valor)
        raiz->izquierda = insertar(raiz->izquierda, valor);
    else
        raiz->derecha = insertar(raiz->derecha, valor);
    return raiz;
}

// Funcion para buscar y eliminar un nodo en el arbol
Nodo* eliminar(Nodo* raiz, string valor) {
    if (!raiz) return raiz;
    
    if (valor < raiz->valor)
        raiz->izquierda = eliminar(raiz->izquierda, valor);
    else if (valor > raiz->valor)
        raiz->derecha = eliminar(raiz->derecha, valor);
    else {
        if (!raiz->izquierda) {
            Nodo* temp = raiz->derecha;
            delete raiz;
            return temp;
        }
        else if (!raiz->derecha) {
            Nodo* temp = raiz->izquierda;
            delete raiz;
            return temp;
        }
        
        Nodo* temp = raiz->derecha;
        while (temp && temp->izquierda)
            temp = temp->izquierda;
        
        raiz->valor = temp->valor;
        raiz->derecha = eliminar(raiz->derecha, temp->valor);
    }
    return raiz;
}

// Recorrido inorden para mostrar el arbol ordenado
void inorden(Nodo* raiz) {
    if (!raiz) return;
    inorden(raiz->izquierda);
    cout << raiz->valor << " ";
    inorden(raiz->derecha);
}

// Recorrido preorden para mostrar el arbol
void preorden(Nodo* raiz) {
    if (!raiz) return;
    cout << raiz->valor << " ";
    preorden(raiz->izquierda);
    preorden(raiz->derecha);
}

// Recorrido postorden para mostrar el arbol
void postorden(Nodo* raiz) {
    if (!raiz) return;
    postorden(raiz->izquierda);
    postorden(raiz->derecha);
    cout << raiz->valor << " ";
}

// Funcion para imprimir el arbol en formato de estructura visual
void imprimirArbol(Nodo* raiz, int espacio = 0, int separacion = 6) {
    if (!raiz) return;
    espacio += separacion;
    imprimirArbol(raiz->derecha, espacio);
    cout << string(espacio, ' ') << raiz->valor << endl;
    imprimirArbol(raiz->izquierda, espacio);
}

// Funcion para imprimir los niveles del arbol
void imprimirPorNiveles(Nodo* raiz, int nivel = 0) {
    if (!raiz) return;
    cout << string(nivel * 3, ' ') << raiz->valor << " (Nivel " << nivel << ")" << endl;
    imprimirPorNiveles(raiz->izquierda, nivel + 1);
    imprimirPorNiveles(raiz->derecha, nivel + 1);
}

int main() {
    vector<string> elementos;
    Nodo* raiz = nullptr;

    // Ingreso de elementos
    cout << "Ingrese 10 caracteres o numeros enteros separados por espacio: ";
    for (int i = 0; i < 10; i++) {
        string entrada;
        cin >> entrada;
        elementos.push_back(entrada);
    }

    // Crear arbol binario
    for (const auto& elem : elementos) {
        raiz = insertar(raiz, elem);
    }

    int opcion;
    do {
        // Menú de opciones
        cout << "\nMenu:\n";
        cout << "0. Terminar el programa\n";
        cout << "1. Mostrar el arbol por niveles\n";
        cout << "2. Recorrido Preorden\n";
        cout << "3. Recorrido Inorden\n";
        cout << "4. Recorrido Postorden\n";
        cout << "5. Agregar un nodo\n";
        cout << "6. Eliminar un nodo\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 0:
                cout << "Programa terminado.\n";
                break;
            case 1:
                cout << "\nEstructura del arbol por niveles:\n";
                imprimirPorNiveles(raiz);
                break;
            case 2:
                cout << "\nRecorrido PreOrden: ";
                preorden(raiz);
                cout << endl;
                break;
            case 3:
                cout << "\nRecorrido InOrden: ";
                inorden(raiz);
                cout << endl;
                break;
            case 4:
                cout << "\nRecorrido PostOrden: ";
                postorden(raiz);
                cout << endl;
                break;
            case 5: {
                string valor;
                cout << "Ingrese el valor del nodo a agregar: ";
                cin >> valor;
                raiz = insertar(raiz, valor);
                cout << "Nodo agregado con exito.\n";
                break;
            }
            case 6: {
                string valor;
                cout << "Ingrese el valor del nodo a eliminar: ";
                cin >> valor;
                raiz = eliminar(raiz, valor);
                cout << "Nodo eliminado con exito (si existia).\n";
                break;
            }
            default:
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);

    return 0;
}
