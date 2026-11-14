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

struct NodoCola {
    int codigo;
    string prioridad;
    NodoCola* siguiente;

    NodoCola(int _codigo, string _prioridad) {
        codigo = _codigo;
        prioridad = _prioridad;
        siguiente = NULL;
    }
};



NodoProceso* BuscarProceso(NodoProceso* cabeza, int codigo) {
    NodoProceso* actual = cabeza;
    while (actual != NULL && actual->id != codigo) {
        actual = actual->siguiente;
    }
    return actual;
}

bool ValidarProceso(NodoProceso* cabeza, int codigo, string nombre, string prioridad, int memoriaMB) {
    if (codigo <= 0 || memoriaMB <= 0) {
        return false;
    }
    if (nombre.empty() || (prioridad != "Alta" && prioridad != "Media" && prioridad != "Baja")) {
        return false;
    }
    return BuscarProceso(cabeza, codigo) == NULL;
}

void RegistrarProceso(NodoProceso*& cabeza, int codigo, string nombre, string prioridad, int memoriaMB) {
    if (!ValidarProceso(cabeza, codigo, nombre, prioridad, memoriaMB)) {
        cout << "Datos invalidos o ID repetido (" << codigo << ")." << endl;
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

    cout << "Proceso '" << nombre << "' registrado." << endl;
}


int PesoPrioridad(string prioridad) {
    if (prioridad == "Alta") return 1;
    if (prioridad == "Media") return 2;
    if (prioridad == "Baja") return 3;
    return 4;
}

NodoCola* BuscarProcesoCola(NodoCola* frente, int codigo) {
    NodoCola* actual = frente;
    while (actual != NULL && actual->codigo != codigo) {
        actual = actual->siguiente;
    }
    return actual;
}

void InsertarCola(NodoCola*& frente, NodoCola* nodoCola) {
    int pesoNuevo = PesoPrioridad(nodoCola->prioridad);
    NodoCola* previo = NULL;
    NodoCola* actual = frente;

    while (actual != NULL && PesoPrioridad(actual->prioridad) <= pesoNuevo) {
        previo = actual;
        actual = actual->siguiente;
    }

    if (previo == NULL) {
        nodoCola->siguiente = frente;
        frente = nodoCola;
    } else {
        previo->siguiente = nodoCola;
        nodoCola->siguiente = actual;
    }
}

void EncolarProceso(NodoProceso* cabeza, NodoCola*& frente, int codigo) {
    NodoProceso* proceso = BuscarProceso(cabeza, codigo);

    if (proceso == NULL) {
        cout << "Proceso no registrado (ID: " << codigo << ")." << endl;
        return;
    }

    if (BuscarProcesoCola(frente, codigo) != NULL) {
        cout << "Proceso ya encolado (ID: " << codigo << ")." << endl;
        return;
    }

    NodoCola* nodoCola = new NodoCola(codigo, proceso->prioridad);
    InsertarCola(frente, nodoCola);

    proceso->estado = "En espera";
    cout << "Proceso " << codigo << " (" << proceso->prioridad << ") encolado." << endl;
}



void MostrarCola(NodoCola* frente) {
    cout << "\n--- COLA DE PRIORIDAD (Orden de atencion) ---" << endl;
    NodoCola* actual = frente;
    if (actual == NULL) {
        cout << "La cola esta vacia." << endl;
        return;
    }
    while (actual != NULL) {
        cout << "[ID: " << actual->codigo << " | Prioridad: " << actual->prioridad << "] -> ";
        actual = actual->siguiente;
    }
    cout << "NULL\n---------------------------------------------\n" << endl;
}



int main() {
    NodoProceso* cabeza = NULL; 
    NodoCola* frente = NULL;    

    
    RegistrarProceso(cabeza, 101, "Respaldo", "Baja", 256);
    RegistrarProceso(cabeza, 102, "Navegador", "Media", 512);
    RegistrarProceso(cabeza, 103, "Sistema Critico", "Alta", 128);
    RegistrarProceso(cabeza, 104, "Antivirus", "Alta", 300);

    cout << endl;

    EncolarProceso(cabeza, frente, 101); 
    EncolarProceso(cabeza, frente, 102); 
    EncolarProceso(cabeza, frente, 103);  
    EncolarProceso(cabeza, frente, 104); 

    EncolarProceso(cabeza, frente, 103); 
    EncolarProceso(cabeza, frente, 999);

    MostrarCola(frente);

    return 0;
}
