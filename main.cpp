#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <queue>
#include <climits>
#include <algorithm>

class Enrutador {
public:
    Enrutador(char id) : id(id) {}

    void actualizarTablaDeEnrutamiento(const std::unordered_map<char, int>& nuevaTabla) {
        tablaDeEnrutamiento = nuevaTabla;
    }

    char getId() const {
        return id;
    }

    const std::unordered_map<char, int>& obtenerTablaDeEnrutamiento() const {
        return tablaDeEnrutamiento;
    }

private:
    char id;
    std::unordered_map<char, int> tablaDeEnrutamiento;
};

class Red {
public:
    void agregarEnrutador(Enrutador enrutador) {
        enrutador.getId() = enrutador;
    }

    void cargarDesdeArchivo(const std::string& nombreArchivo);

    int costoDeEnvio(char origen, char destino);

    std::vector<char> caminoOptimo(char origen, char destino);

private:
    std::unordered_map<char, Enrutador> enrutador;
};

void Red::cargarDesdeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        char origen, destino;
        int costo;
        while (archivo >> origen >> destino >> costo) {
            enrutador[origen].actualizarTablaDeEnrutamiento({{destino, costo}});
            enrutador[destino].actualizarTablaDeEnrutamiento({{origen, costo}});
        }
        archivo.close();
    } else {
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << std::endl;
    }
}

int Red::costoDeEnvio(char origen, char destino) {
    return enrutador[origen].obtenerTablaDeEnrutamiento().at(destino);
}

std::vector<char> Red::caminoOptimo(char origen, char destino) {
    // ...
}

int main() {
    Red red;
    // Agrega enrutadores
    Enrutador enrutadorA('A');
    Enrutador enrutadorB('B');
    Enrutador enrutadorC('C');
    Enrutador enrutadorD('D');

    red.agregarEnrutador(enrutadorA);
    red.agregarEnrutador(enrutadorB);
    red.agregarEnrutador(enrutadorC);
    red.agregarEnrutador(enrutadorD);

    // Cargar topología desde un archivo
    red.cargarDesdeArchivo("topologia.txt");
    // Ejemplo de cómo usar las funciones de la red
    char origen = 'A';
    char destino = 'D';

    int costo = red.costoDeEnvio(origen, destino);
    std::cout << "Costo de enviar un paquete desde " << origen << " hasta " << destino << ": " << costo << std::endl;

    std::vector<char> camino = red.caminoOptimo(origen, destino);
    std::cout << "Camino óptimo: ";
        for (char enrutador : camino) {
        std::cout << enrutador << " ";
    }
    std::cout << std::endl;

    return 0;
}
