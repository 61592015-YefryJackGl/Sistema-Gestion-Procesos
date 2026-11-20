#include <iostream>
#include <string>

using namespace std;

struct NodoProceso {
    int id;
    string nombre;
    string prioridad;
    int memoriaMB;
    string estado;
    NodoProceso* siguiente;

   
    NodoProceso(int _id, string _nombre, string _prioridad, int _memoriaMB, string _estado) {
        id = _id;
        nombre = _nombre;
        prioridad = _prioridad;
        memoriaMB = _memoriaMB;
        estado = _estado;
        siguiente = NULL;
    }
};


NodoProceso* BuscarProceso(NodoProceso* cabeza, int codigo) {
    NodoProceso* actual = cabeza;
    while (actual != NULL && actual->id != codigo) {
        actual = actual->siguiente;
    }
    return actual; // Retorna el puntero si lo encuentra, o NULL si no existe
}

// Función para validar los datos del proceso antes de insertarlo
bool ValidarProceso(NodoProceso* cabeza, int codigo, string nombre, string prioridad, int memoriaMB) {
    if (codigo <= 0 || memoriaMB <= 0) {
        return false;
    }
    
    if (nombre.empty() || (prioridad != "Alta" && prioridad != "Media" && prioridad != "Baja")) {
        return false;
    }
    
    // Retorna true solo si el código no está repetido en la lista
    return BuscarProceso(cabeza, codigo) == NULL;
}


void RegistrarProceso(NodoProceso*& cabeza, int codigo, string nombre, string prioridad, int memoriaMB) {
    if (!ValidarProceso(cabeza, codigo, nombre, prioridad, memoriaMB)) {
        cout << "Error: Datos invalidos o ID repetido (" << codigo << ")." << endl;
        return;
    }

    NodoProceso* nodoNuevo = new NodoProceso(codigo, nombre, prioridad, memoriaMB, "Listo");

    if (cabeza == NULL) {
        cabeza = nodoNuevo;
    } else {
        NodoProceso* ultimo = cabeza;
        while (ultimo->siguiente != NULL) {
            ultimo = ultimo->siguiente;
        }
        ultimo->siguiente = nodoNuevo;
    }

    cout << "Proceso '" << nombre << "' registrado correctamente." << endl;
}


void MostrarProcesos(NodoProceso* cabeza) {
    cout << "\n--- LISTA DE PROCESOS ---" << endl;
    NodoProceso* actual = cabeza;
    if (actual == NULL) {
        cout << "La lista esta vacia." << endl;
        return;
    }
    while (actual != NULL) {
        cout << "ID: " << actual->id 
             << " | Nombre: " << actual->nombre 
             << " | Prioridad: " << actual->prioridad 
             << " | Memoria: " << actual->memoriaMB << " MB" 
             << " | Estado: " << actual->estado << endl;
        actual = actual->siguiente;
    }
    cout << "-------------------------\n" << endl;
}


int main() {
    NodoProceso* cabeza = NULL; // Inicializamos la lista vacía

    // Pruebas de registro
    RegistrarProceso(cabeza, 101, "Navegador", "Alta", 512);
    RegistrarProceso(cabeza, 102, "Editor de Texto", "Media", 128);
    RegistrarProceso(cabeza, 103, "Antivirus", "Baja", 256);
    
    // Prueba con ID repetido (debe dar error)
    RegistrarProceso(cabeza, 101, "Otro Proceso", "Alta", 100);
    
    // Prueba con prioridad inválida (debe dar error)
    RegistrarProceso(cabeza, 104, "Juego", "Urgente", 1024);

    // Mostrar resultados
    MostrarProcesos(cabeza);

    return 0;
}
