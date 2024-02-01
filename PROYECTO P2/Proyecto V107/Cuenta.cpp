#include "Cuenta.h"
#include "validaciones.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

Cuenta::Cuenta(){
}

std::string Cuenta::getCuenta(void)const
{
   return cuenta;
}
void Cuenta::setCuenta(std::string newCuenta)
{
   cuenta = newCuenta;
}

Cuenta::Cuenta(std::string cuenta)
    :  cuenta(cuenta) {
         int contadorId=0;
    // Actualizar el contadorId si es necesario
    int idValor = std::stoi(cuenta.substr(1));
    if (idValor > contadorId) {
        contadorId = idValor;
    }
}
Cuenta Cuenta::crear_cuenta() {
    validaciones valida;
    Persona nuevaPersona;
    std::string cedulaIngresada;

    // Solicitar la c�dula al usuario
    do {
        cedulaIngresada = valida.ingresar_numeros_como_string("\nIngrese el numero de cedula: ");

        if (valida.validarCedula(cedulaIngresada)) {
            std::ifstream archivo("Personas.txt");
            std::string linea;

            if (archivo.is_open()) {
                // Leer cada l�nea del archivo
                while (std::getline(archivo, linea)) {
                    std::istringstream iss(linea);
                    std::string cedulaArchivo, nombreCompleto, id;

                    // Leer los componentes de la l�nea
                    iss >> cedulaArchivo >> nombreCompleto;  // Leer la c�dula y el nombre completo
                    std::string apellido, nombre;
                    while (iss >> nombre >> apellido) {
                        // Concatenar el nombre y el apellido en uno solo
                        nombreCompleto += " " + apellido;
                    }

                    // Encontrar el �ndice del �ltimo espacio (posici�n del ID)
                    size_t pos = nombreCompleto.rfind(" ");

                    // Extraer el ID desde la posici�n del �ltimo espacio
                    if (pos != std::string::npos && pos < nombreCompleto.length() - 1) {
                        id = nombreCompleto.substr(pos + 1);
                        nombreCompleto.erase(pos);
                    }

                    // Comparar la c�dula ingresada con la c�dula en la l�nea actual
                    if (cedulaArchivo == cedulaIngresada) {
                        Cuenta nuevaCuenta;
                        std::string newCuenta = nuevaCuenta.generar_cuenta_automatica();
                        std::cout << "\nSu cuenta es: " << newCuenta << std::endl;
                        nuevaCuenta.setCuenta(newCuenta);
                        std::cout << "\nDatos encontrados:\n";
                        std::cout << "Cedula: " << cedulaArchivo << "\n";
                        std::cout << "Nombre completo: " << nombreCompleto << "\n";
                        std::cout << "ID: " << id << "\n";

                        // Guardar los datos en el archivo nuevo (puedes cambiar el nombre del archivo seg�n tus necesidades)
                        nuevaCuenta.guardarTabla("USUARIOS.txt", cedulaArchivo, nombreCompleto, id, nuevaCuenta);

                        archivo.close();
                        return nuevaCuenta;
                    }
                }
                archivo.close();
                std::cout << "\nLa cedula ingresada no existe en el archivo. Vuelva a intentarlo." << std::endl;
            } else {
                std::cerr << "No se pudo abrir el archivo Personas.txt\n";
            }
        } else {
            std::cout << "\nLa cedula ingresada es invalida. Vuelva a intentarlo." << std::endl;
        }
    } while (true);
}

void Cuenta::guardarTabla(const std::string& archivo, const std::string& cedula, const std::string& nombreCompleto, const std::string& id, const Cuenta& cuenta) {
    std::ofstream outFile(archivo, std::ios::app);

    if (outFile.is_open()) {
        outFile << cedula << " "
                << nombreCompleto << " "
                << id << "\n"
                << cuenta.getCuenta() << "\n";

        outFile.close();
        std::cout << "Datos guardados en " << archivo << std::endl;

        // Imprimir informaci�n encontrada
        std::cout << "Datos encontrados:\n";
        std::cout << "Cedula: " << cedula << "\n";
        std::cout << "Nombre completo: " << nombreCompleto << "\n";
        std::cout << "ID: " << id << "\n";
        std::cout << "N�mero de cuenta: " << cuenta.getCuenta() << "\n";

        // L�nea en blanco opcional
        std::cout << std::endl;
    } else {
        std::cerr << "No se pudo abrir el archivo " << archivo << std::endl;
    }
}

void Cuenta::mostrarRegistroCuenta(){
    validaciones valida;
    string line;
    string lectura;

    lectura = valida.leerArchivoTxtCuenta();
    stringstream input_stringstream(lectura);
    cout << "N�Cuenta" << endl;
    cout << "===========================================================================" << endl;
    while (getline(input_stringstream, line, '\n'))
    {
        cout << line << endl;
    }
    cout << "===========================================================================" << endl;
}

int Cuenta::contadorId = 0;
std::string  Cuenta::generar_cuenta_automatica(){
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(6) << ++contadorId;
    return oss.str();
}

