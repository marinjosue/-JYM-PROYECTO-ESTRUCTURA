/***********************************************************************
 * Module:  Persona.cpp
 * Author:  Usuario
 * Modified: domingo, 7 de enero de 2024 0:07:18
 * Purpose: Implementation of the class Persona
 ***********************************************************************/

#include "Persona.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "validaciones.h"
#include "ListaDoble.h"
#include "Nodo.h"



////////////////////////////////////////////////////////////////////////
// Name:       Persona::Persona()
// Purpose:    Implementation of Persona::Persona()
// Return:
////////////////////////////////////////////////////////////////////////

Persona::Persona()
{
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::~Persona()
// Purpose:    Implementation of Persona::~Persona()
// Return:
////////////////////////////////////////////////////////////////////////

Persona::~Persona()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::getNombre()
// Purpose:    Implementation of Persona::getNombre()
// Return:     std::string
////////////////////////////////////////////////////////////////////////

std::string Persona::getNombre(void)
{
   return Nombre;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::setNombre(std::string newNombre)
// Purpose:    Implementation of Persona::setNombre()
// Parameters:
// - newNombre
// Return:     void
////////////////////////////////////////////////////////////////////////

void Persona::setNombre(std::string newNombre)
{
   Nombre = newNombre;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::getApellido()
// Purpose:    Implementation of Persona::getApellido()
// Return:     std::string
////////////////////////////////////////////////////////////////////////

std::string Persona::getApellido(void)
{
   return Apellido;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::setApellido(std::string newApellido)
// Purpose:    Implementation of Persona::setApellido()
// Parameters:
// - newApellido
// Return:     void
////////////////////////////////////////////////////////////////////////

void Persona::setApellido(std::string newApellido)
{
   Apellido = newApellido;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::getCedula()
// Purpose:    Implementation of Persona::getCedula()
// Return:     std::string
////////////////////////////////////////////////////////////////////////

std::string Persona::getCedula(void)
{
   return Cedula;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::setCedula(std::string newCedula)
// Purpose:    Implementation of Persona::setCedula()
// Parameters:
// - newCedula
// Return:     void
////////////////////////////////////////////////////////////////////////

void Persona::setCedula(std::string newCedula)
{
   Cedula = newCedula;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::getId()
// Purpose:    Implementation of Persona::getId()
// Return:     std::string
////////////////////////////////////////////////////////////////////////

std::string Persona::getId(void)
{
   return Id;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::setId(std::string newId)
// Purpose:    Implementation of Persona::setId()
// Parameters:
// - newId
// Return:     void
////////////////////////////////////////////////////////////////////////

void Persona::setId(std::string newId)
{
   Id = newId;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::Persona(const Persona& oldPersona)
// Purpose:    Implementation of Persona::Persona()
// Parameters:
// - oldPersona
// Return:
////////////////////////////////////////////////////////////////////////

Persona::Persona(std::string Nombre, std::string Apellido, std::string Cedula, std::string Id)
{

    this->Nombre = Nombre;
    this->Apellido = Apellido;
    this->Cedula = Cedula;
    this->Id = Id;
}


/**
 * @brief Ingresa una nueva persona y la guarda en un archivo de texto.
 */
 Persona Persona::ingresarPersona() {
 std::string newCedula, newNombre, newApellido, newId;
  do {
    newCedula = ingresar_numeros_como_string("cedula");

    if (validarCedula(newCedula)) {
      break;
    } else {
      cout << "La c�dula ingresada es inv�lida. Vuelva a intentarlo." << endl;
    }
  } while (true);
    //newNombre= ingresar_alfabetico_con_un_espacio("Nombre: ");
    newNombre= mayusculas_primeras(ingresar_alfabetico_con_un_espacio("Nombres: "));
    newApellido= mayusculas_primeras(ingresar_alfabetico_con_un_espacio("Apellidos: "));


    std::cout << "Su ID es: ";
    std::cin >> newId;


    // Crear y retornar un objeto Persona con los valores ingresados
    return Persona(newCedula, newNombre, newApellido, newId);



}

// datos= cedula + " "+ nombre+" " + apellido+" " + "\n";



/*
 std::ofstream archivo("personas.txt", std::ios::app);
    if (archivo.is_open()) {
        archivo << cedula << " ";
        archivo << nombre << " ";
        archivo << apellido << " ";
        archivo << id << "\n";
        archivo.close();
        std::cout << "Persona registrada exitosamente en el archivo personas.txt\n";
    } else {
        std::cerr << "No se pudo abrir el archivo personas.txt para escribir\n";
    }*/
