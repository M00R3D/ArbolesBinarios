// Programa de operaciones con arboles binarios, por Alumno Job Moore Garay, IDS Estructura de Datos II

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
    int altura; // nuevo campo

    Nodo(string v) : valor(v), izquierda(nullptr), derecha(nullptr), altura(1) {}
};

// Funciones auxiliares para AVL
int altura(Nodo* nodo) {
    return nodo ? nodo->altura : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int obtenerBalance(Nodo* nodo) {
    return nodo ? altura(nodo->izquierda) - altura(nodo->derecha) : 0;
}

Nodo* rotarDerecha(Nodo* y) {
    Nodo* x = y->izquierda;
    Nodo* T2 = x->derecha;

    x->derecha = y;
    y->izquierda = T2;

    y->altura = max(altura(y->izquierda), altura(y->derecha)) + 1;
    x->altura = max(altura(x->izquierda), altura(x->derecha)) + 1;

    return x;
}

Nodo* rotarIzquierda(Nodo* x) {
    Nodo* y = x->derecha;
    Nodo* T2 = y->izquierda;

    y->izquierda = x;
    x->derecha = T2;

    x->altura = max(altura(x->izquierda), altura(x->derecha)) + 1;
    y->altura = max(altura(y->izquierda), altura(y->derecha)) + 1;

    return y;
}

// Funcion para insertar en el arbol binario (sin balanceo)
Nodo* insertar(Nodo* raiz, string valor) {
    if (!raiz) return new Nodo(valor);
    if (valor < raiz->valor)
        raiz->izquierda = insertar(raiz->izquierda, valor);
    else
        raiz->derecha = insertar(raiz->derecha, valor);
    return raiz;
}

// Insercion con balanceo AVL
Nodo* insertarAVL(Nodo* nodo, string valor) {
    if (!nodo) return new Nodo(valor);

    if (valor < nodo->valor)
        nodo->izquierda = insertarAVL(nodo->izquierda, valor);
    else if (valor > nodo->valor)
        nodo->derecha = insertarAVL(nodo->derecha, valor);
    else
        return nodo;

    nodo->altura = 1 + max(altura(nodo->izquierda), altura(nodo->derecha));

    int balance = obtenerBalance(nodo);

    if (balance > 1 && valor < nodo->izquierda->valor)
        return rotarDerecha(nodo);

    if (balance < -1 && valor > nodo->derecha->valor)
        return rotarIzquierda(nodo);

    if (balance > 1 && valor > nodo->izquierda->valor) {
        nodo->izquierda = rotarIzquierda(nodo->izquierda);
        return rotarDerecha(nodo);
    }

    if (balance < -1 && valor < nodo->derecha->valor) {
        nodo->derecha = rotarDerecha(nodo->derecha);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

// Reinsertar todos los nodos usando AVL
void recolectarNodos(Nodo* raiz, vector<string>& nodos) {
    if (!raiz) return;
    recolectarNodos(raiz->izquierda, nodos);
    nodos.push_back(raiz->valor);
    recolectarNodos(raiz->derecha, nodos);
}

Nodo* balancearAVL(Nodo* raiz) {
    vector<string> nodos;
    recolectarNodos(raiz, nodos);
    Nodo* nuevoArbol = nullptr;
    for (const string& val : nodos)
        nuevoArbol = insertarAVL(nuevoArbol, val);
    return nuevoArbol;
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

// Recorridos
void inorden(Nodo* raiz) {
    if (!raiz) return;
    inorden(raiz->izquierda);
    cout << raiz->valor << " ";
    inorden(raiz->derecha);
}

void preorden(Nodo* raiz) {
    if (!raiz) return;
    cout << raiz->valor << " ";
    preorden(raiz->izquierda);
    preorden(raiz->derecha);
}

void postorden(Nodo* raiz) {
    if (!raiz) return;
    postorden(raiz->izquierda);
    postorden(raiz->derecha);
    cout << raiz->valor << " ";
}

void imprimirArbol(Nodo* raiz, int espacio = 0, int separacion = 6, int nivel = 0) {
    if (!raiz) return;
    espacio += separacion;

    // Mostrar lado derecho
    imprimirArbol(raiz->derecha, espacio, separacion, nivel + 1);

    // Imprimir el nodo actual con nivel
    cout << string(espacio, ' ') << raiz->valor << " (Nivel " << nivel << ")" << endl;

    // Mostrar lado izquierdo
    imprimirArbol(raiz->izquierda, espacio, separacion, nivel + 1);
}

void imprimirPorNiveles(Nodo* raiz, int nivel = 0) {
    if (!raiz) return;
    cout << string(nivel * 3, ' ') << raiz->valor << " (Nivel " << nivel << ")" << endl;
    imprimirPorNiveles(raiz->izquierda, nivel + 1);
    imprimirPorNiveles(raiz->derecha, nivel + 1);
}

int main() {
    vector<string> elementos;
    Nodo* raiz = nullptr;
    cout << "Programa de operaciones con arboles binarios, por Alumno Job Moore Garay, IDS Estructura de Datos II\n" << endl;

    cout << "Ingrese 10 caracteres o numeros enteros separados por espacio: ";
    for (int i = 0; i < 10; i++) {
        string entrada;
        cin >> entrada;
        elementos.push_back(entrada);
    }

    for (const auto& elem : elementos) {
        raiz = insertar(raiz, elem);
    }

    int opcion;
    do {
        cout << "\nMenu:\n";
        cout << "0. Terminar el programa\n";
        cout << "1. Mostrar el arbol por niveles\n";
        cout << "2. Recorrido Preorden\n";
        cout << "3. Recorrido Inorden\n";
        cout << "4. Recorrido Postorden\n";
        cout << "5. Agregar un nodo\n";
        cout << "6. Eliminar un nodo\n";
        cout << "7. Balancear el arbol (AVL)\n";
        cout << "8. Mostrar arbol rotado (estructura visual)\n";
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
            case 7:
                raiz = balancearAVL(raiz);
                cout << "Arbol balanceado usando AVL.\n";
                break;
            case 8:
                cout << "\nEstructura visual del arbol rotado:\n";
                imprimirArbol(raiz);
                break;
            default:
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);

    return 0;
}
