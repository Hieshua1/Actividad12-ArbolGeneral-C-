
// Actividad12-ArbolGeneral-C++.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo* hijo;
    Nodo* hermano;
};
Nodo* CrearNodo(int valor) {
    Nodo* nuevoNodo = new Nodo;
    nuevoNodo->dato = valor;
    nuevoNodo->hijo = nullptr;
    nuevoNodo->hermano = nullptr;
    return nuevoNodo;
}

Nodo* AgregarHijo(Nodo* padre, int valor) {
    Nodo* nuevoNodo = CrearNodo(valor);
    if (padre->hijo == nullptr) {
        padre->hijo = nuevoNodo;
    }
    else {
        Nodo* actual = padre->hijo;
        while (actual->hermano != nullptr) {
            actual = actual->hermano;
        }
        actual->hermano = nuevoNodo;
    }
    return nuevoNodo;
}

void ConstruirArbol(Nodo* nodo) {
    int cantidadHijos;
    cout << "Cuantos Hijos tiene el nodo " << nodo->dato << "?";
    cin >> cantidadHijos;
    for (int i = 0; i < cantidadHijos; i++) {
        int valor;
        cout << "ingrese el valor del hijo " << i + 1 << " de " << nodo->dato << ": ";
        cin >> valor;
        Nodo* nuevo = AgregarHijo(nodo, valor);
        ConstruirArbol(nuevo);
    }
}

Nodo* BurcarNodo(Nodo* nodo, int valor) {
    if (nodo == nullptr) return nullptr;
    if (nodo->dato == valor) return nodo;
    Nodo* actual = nodo->hijo;
    while (actual != nullptr) {
        Nodo* encontrado = BurcarNodo(actual, valor);
        if (encontrado != nullptr) return encontrado;
        actual = actual->hermano;
    }
    return nullptr;
}

void MostrarHojas(Nodo* nodo, int& contador) {
    if (nodo == nullptr) return;
    if (nodo->hijo == nullptr) {
        cout << nodo->dato << " (Direccion: " << nodo << ")" << endl;
        contador++;
    }
    Nodo* actual = nodo->hijo;
    while (actual != nullptr) {
        MostrarHojas(actual, contador);
        actual = actual->hermano;
    }
}

void ImprimirArbol(Nodo* nodo, int nivel) {
    if (nodo == nullptr) return;
    for (int i = 0; i < nivel;i++) {
        cout << "   ";
    }
    cout << nodo->dato << " (Direccion: " << nodo << ")" << endl;
    Nodo* actual = nodo->hijo;
    while (actual != nullptr) {
        ImprimirArbol(actual, nivel+1);
        actual = actual->hermano;
    }
}

void BorrarArbol(Nodo* nodo, int& contador) {
    if (nodo == nullptr) return;
    Nodo* actual = nodo->hijo;
    while (actual != nullptr) {
        Nodo* siguiente = actual->hermano;
        BorrarArbol(actual, contador);
        actual = siguiente;
    }
    cout << "Eelemento borrado " << contador
        << " | Dato: " << nodo->dato
        << "  Direccion: " << nodo << endl;
    contador++;
    delete nodo;
}
int main()
{
    Nodo* raiz = nullptr;
    int opc;
    cout << "Actividad 12 - Arbol general \n" << endl;
    do {
        cout << "\n_____Menu Principal_____" << endl;
        cout << "1. Ingresar elementos_____" << endl;
        cout << "2. Mostrar hojas__________" << endl;
        cout << "3. Visualizar arbol_______" << endl;
        cout << "0. Salir__________________" << endl;
        cout << "==========================" << endl;
        cout << "ingrese una opcion: ";
        cin >> opc;
        switch (opc)
        {
        case 1: {
            if (raiz == nullptr) {
                int valorRaiz;
                cout << "Ingrese el valor de la raiz: ";
                cin >> valorRaiz;
                raiz = CrearNodo(valorRaiz);
            }
            else {
                int valorPadre;
                cout << "Ingrese el valor del nodo padre: ";
                cin >> valorPadre;
                Nodo* padre = BurcarNodo(raiz, valorPadre);
                if (padre == nullptr) {
                    cout << "El nodo " << valorPadre << " no existe en el arbol" << endl;
                }
                else {
                    int cantidad;
                    cout << "cuantos hijos nuevos tendra el nodo " << padre->dato << "? ";
                    cin >> cantidad;
                    for (int i = 0; i < cantidad;i++) {
                        int valor;
                        cout << "Ingrese el valor del hijo nuevo " << i + 1 << ": ";
                        cin >> valor;
                        Nodo* nuevo = AgregarHijo(padre, valor);
                        ConstruirArbol(nuevo);
                    }
                }
            }
            break;
        }
        case 2: {
            if (raiz == nullptr) {
                cout << "El arbol esta vacio" << endl;
                break;
            }
            int totalHojas = 0;
            cout << "hojas del arbol: " << endl;
            MostrarHojas(raiz, totalHojas);
            cout << "Total de hojas: " << totalHojas << endl;
            break;
        }
        case 3: {
            if (raiz == nullptr) {
                cout << "El arbol esta vacio" << endl;
                break;
            }
            cout << "Arbol (preorden):" << endl;
            ImprimirArbol(raiz, 0);
            break;
        }
        case 0: {
            cout << "Borrando arbol antes de salir:" << endl;
            int contador = 1;
            BorrarArbol(raiz, contador);
            raiz = nullptr;
            cout << "Total de elementos borrados: " << contador - 1 << endl;
            cout << "Saliendo del programa..." << endl;
            break;
        }
        default:
            cout << "Opcion no valida" << endl;
            break;
        }

    } while (opc != 0);
    return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
