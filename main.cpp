#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

// Definición del nodo del árbol
struct Nodo {
    string valor;
    Nodo* izquierda;
    Nodo* derecha;
    Nodo(string v) : valor(v), izquierda(nullptr), derecha(nullptr) {}
};

// Función para insertar en el árbol binario (permitiendo duplicados)
Nodo* insertar(Nodo* raiz, const string& valor) {
    if (!raiz) return new Nodo(valor);
    if (valor < raiz->valor)
        raiz->izquierda = insertar(raiz->izquierda, valor);
    else // Si el valor es igual o mayor, lo insertamos en la derecha
        raiz->derecha = insertar(raiz->derecha, valor);
    return raiz;
}

// Recorrido BFS para imprimir el árbol por niveles con padres
void imprimirArbolPorNiveles(Nodo* raiz) {
    if (!raiz) return;

    queue<pair<Nodo*, pair<Nodo*, int>>> q;  // Nodo, (Padre, Nivel)
    q.push({raiz, {nullptr, 0}});             // Comenzamos desde la raíz con nivel 0

    int nivelActual = 0;                     // Variable para saber en qué nivel estamos

    // Realizamos el recorrido por niveles (BFS)
    while (!q.empty()) {
        Nodo* nodo = q.front().first;
        Nodo* padre = q.front().second.first;
        int nivel = q.front().second.second;
        q.pop();

        // Imprimir el nodo con su nivel y su padre
        if (nivel != nivelActual) {
            cout << endl;  // Saltamos una línea al cambiar de nivel
            nivelActual = nivel;
        }

        // Imprimimos el valor del nodo, su nivel y el valor de su nodo padre
        if (padre) {
            cout << setw(3) << nodo->valor << " (Nivel " << nivel << ", Padre: " << padre->valor << ") ";
        } else {
            cout << setw(3) << nodo->valor << " (Nivel " << nivel << ", Padre: N/A) ";
        }

        // Agregar los nodos hijos a la cola
        if (nodo->izquierda) q.push({nodo->izquierda, {nodo, nivel + 1}});
        if (nodo->derecha) q.push({nodo->derecha, {nodo, nivel + 1}});
    }
    cout << endl;
}

// Recorrido Preorden (Raíz -> Izquierda -> Derecha)
void preorden(Nodo* raiz) {
    if (raiz) {
        cout << raiz->valor << " ";
        preorden(raiz->izquierda);
        preorden(raiz->derecha);
    }
}

// Recorrido Inorden (Izquierda -> Raíz -> Derecha)
void inorden(Nodo* raiz) {
    if (raiz) {
        inorden(raiz->izquierda);
        cout << raiz->valor << " ";
        inorden(raiz->derecha);
    }
}

// Recorrido Postorden (Izquierda -> Derecha -> Raíz)
void postorden(Nodo* raiz) {
    if (raiz) {
        postorden(raiz->izquierda);
        postorden(raiz->derecha);
        cout << raiz->valor << " ";
    }
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
    for (const auto& elem : elementos) {
        cout << elem << " ";
    }
    cout << "\n\nEstructura del arbol por niveles:\n";
    imprimirArbolPorNiveles(raiz);

    // Limpiar el buffer de entrada
    cin.ignore();  // Esto asegura que no haya residuos de salto de línea en el buffer

    // Opción para ver el árbol con diferentes recorridos
    int opcion;
    cout << "\nSelecciona el tipo de recorrido para visualizar el arbol:\n";
    cout << "1. Preorden\n";
    cout << "2. Inorden\n";
    cout << "3. Postorden\n";
    cout << "Elige una opcion (1-3): ";
    
    // Ahora esperamos la opción para el recorrido
    cin >> opcion;

    // Imprimir el recorrido seleccionado
    cout << "\nResultado del recorrido: ";
    switch (opcion) {
        case 1:
            preorden(raiz);
            break;
        case 2:
            inorden(raiz);
            break;
        case 3:
            postorden(raiz);
            break;
        default:
            cout << "Opcion no valida.\n";
            break;
    }
    cout << endl;

    return 0;
}
