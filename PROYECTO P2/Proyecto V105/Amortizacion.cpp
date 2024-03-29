/*************************
 UFA - ESPE
 * Module:  CalculosCredito.cpp
 * Author:  Chiliquinga Yeshua, Marin Alquinga,Salcedo Micaela
 * Modified: domingo, 17 de diciembre de 2023
 * Purpose: Implementacion de clase Amortizacion
 *************************/
#include <iostream>
#include <fstream>
#include "Amortizacion.h"
#include "CalculosCredito.h"
#include "Fecha.h"
#include "ListaDoble.cpp"
#include "Extra.h"
#include "Nodo.cpp"
#include <iomanip>
#include <ctime>
#include "validaciones.h"

using namespace std;

Amortizacion::Amortizacion(){

}
Amortizacion::Amortizacion(Credito credito_usar){
    credito = credito_usar;
    cuotas_ord = new ListaDoble<int>();
    saldos_capital= new ListaDoble<double>();
    intereses= new ListaDoble<double>();
    pagos_capital= new ListaDoble<double>();
    valor_cuotas= new ListaDoble<double>();
    fechas_pago= new ListaDoble<Fecha>();
    llenar_tabla_amortizacion();
}

void Amortizacion::llenar_tabla_amortizacion(){
    CalculosCredito calculos(15);
    double v_cuotas = calculos.calcular_valor_cuotas(credito.get_n_cuotas_pagar(), credito.get_monto());
    int n_ord = 1;
    while(n_ord<=credito.get_n_cuotas_pagar()){
        cuotas_ord->insertar_cola(n_ord);
        valor_cuotas->insertar_cola(v_cuotas);
        n_ord++;
    }

    calculos.calcular_valor_intereses(credito.get_n_cuotas_pagar(), credito.get_monto(), v_cuotas, intereses);
    calculos.calcular_capitales_pagados(v_cuotas, pagos_capital, intereses->get_cabeza());
    calculos.calcular_saldos_restantes(credito.get_monto(), v_cuotas, saldos_capital, pagos_capital->get_cabeza());
    generar_fechas_pago();
}

void Amortizacion::generar_fechas_pago(){
    Fecha fecha_sacado = credito.get_fecha_realizado();
    int ncuotas = credito.get_n_cuotas_pagar();
    int meses_gracia = credito.get_meses_gracia();
    int intervalo_pagos_mes = credito.get_intervalo_pagos_mes();
    Fecha fecha_gen = fecha_sacado;
    fecha_gen.set_mes(fecha_gen.get_mes() + meses_gracia);
    int n_gen = 0;

    while(fecha_gen.es_finde() || fecha_gen.es_feriado()){
        fecha_gen.set_dia(fecha_gen.get_dia()+1);
    }
    fechas_pago->insertar_cola(fecha_gen);
    n_gen++;

    while(n_gen<ncuotas){
        fecha_gen.set_mes(fecha_gen.get_mes() + intervalo_pagos_mes);
        while(fecha_gen.es_finde() || fecha_gen.es_feriado()){
            fecha_gen.set_dia(fecha_gen.get_dia()+1);
        }
        fechas_pago->insertar_cola(fecha_gen);
        n_gen++;
    }
}


void Amortizacion::imprimir(){
     int n_mostrados = 0;
    int n_mostrar = credito.get_n_cuotas_pagar();
    Nodo<int>* ord = cuotas_ord->get_cabeza();
    Nodo<double>* saldo_cap = saldos_capital->get_cabeza();
    Nodo<double>* interes = intereses->get_cabeza();
    Nodo<double>* capital_pag = pagos_capital->get_cabeza();
    Nodo<double>* valor_cuota = valor_cuotas->get_cabeza();
    Nodo<Fecha>* aux_fecha_pagar = fechas_pago->get_cabeza();
    Fecha fecha_pagar;
    int ancho_ord = 10, ancho_vcuota = 12, ancho_capital = 12, ancho_interes = 10, ancho_saldo = 15, ancho_fecha = 14;

    std::cout<< '|'<<std::setw(ancho_ord)<<"No."<< '|'<<std::setw(ancho_vcuota)<<"CUOTA FIJA";
    std::cout<<'|'<<std::setw(ancho_capital)<<"PAGO CAPITAL"<<'|'<<std::setw(ancho_interes)<<"INTERES";
    std::cout<<'|'<<std::setw(ancho_saldo)<<"SALDO CAPITAL"<<'|'<<std::setw(ancho_fecha)<<"FECHA DE PAGO"<<'|';
    printf("\n");
    printf("\n");
    while(n_mostrados < n_mostrar){
        fecha_pagar = aux_fecha_pagar->get_valor();
        std::cout<< '|'<<std::setw(ancho_ord)<<ord->get_valor()<<'|'<<std::setw(ancho_vcuota)<<valor_cuota->get_valor();
        std::cout<<'|'<<std::setw(ancho_capital)<<capital_pag->get_valor()<<'|'<<std::setw(ancho_interes)<<interes->get_valor();
        std::cout<<'|'<<std::setw(ancho_saldo)<<saldo_cap->get_valor()<<'|'<<std::setw(ancho_fecha)<<fecha_pagar.to_string()<<'|';
        printf("\n");

        ord = ord->get_siguiente();
        saldo_cap = saldo_cap->get_siguiente();
        interes = interes->get_siguiente();
        capital_pag = capital_pag->get_siguiente();
        valor_cuota = valor_cuota->get_siguiente();
        aux_fecha_pagar = aux_fecha_pagar->get_siguiente();
        n_mostrados++;
    }
}

std::string obtenerFechaHoraActual() {
    time_t tiempoActual = time(nullptr);
    tm* tmActual = localtime(&tiempoActual);

    std::string fechaHora = std::to_string(tmActual->tm_mday) + "/" +
                            std::to_string(tmActual->tm_mon + 1) + "/" +
                            std::to_string(tmActual->tm_year + 1900) + " a las " +
                            std::to_string(tmActual->tm_hour) + ":" +
                            std::to_string(tmActual->tm_min) + ":" +
                            std::to_string(tmActual->tm_sec);
    return fechaHora;
}

void Amortizacion::guardarTabla(const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    // Obtener la fecha y hora actual utilizando la nueva función
    std::string fechaHoraGeneracion = obtenerFechaHoraActual();

    // Imprimir la fecha y hora de generación de la tabla
    archivo << "Tabla generada el " << fechaHoraGeneracion << "\n\n";

    int n_mostrados = 0;
    int n_mostrar = credito.get_n_cuotas_pagar();
    Nodo<int>* ord = cuotas_ord->get_cabeza();
    Nodo<double>* saldo_cap = saldos_capital->get_cabeza();
    Nodo<double>* interes = intereses->get_cabeza();
    Nodo<double>* capital_pag = pagos_capital->get_cabeza();
    Nodo<double>* valor_cuota = valor_cuotas->get_cabeza();
    Nodo<Fecha>* aux_fecha_pagar = fechas_pago->get_cabeza();
    Fecha fecha_pagar;


    archivo << "N    VALOR CUOTA   CAPITAL     INTERES      SALDO      FECHA\n";

    while (n_mostrados < n_mostrar) {
        fecha_pagar = aux_fecha_pagar->get_valor();
        archivo << ord->get_valor() << "\t|\t" << std::fixed << std::setprecision(2) << valor_cuota->get_valor();
        archivo << "\t|\t" << std::fixed << std::setprecision(2) << capital_pag->get_valor() << "\t|\t" << std::fixed << std::setprecision(2) << interes->get_valor();
        archivo << "\t|\t" << std::fixed << std::setprecision(2) << saldo_cap->get_valor() << "\t|\t";
        archivo << fecha_pagar.to_string() << "\n";

        ord = ord->get_siguiente();
        saldo_cap = saldo_cap->get_siguiente();
        interes = interes->get_siguiente();
        capital_pag = capital_pag->get_siguiente();
        valor_cuota = valor_cuota->get_siguiente();
        aux_fecha_pagar = aux_fecha_pagar->get_siguiente();

        n_mostrados++;
    }

    archivo.close();

    cout<<"\nLA TABLA DE CREDITOS SE GUARDO EN EL ARCHIVO '"<<nombreArchivo<<"'.\n\n'";
    createBackupRegistro();

}
void Amortizacion::ingresar_datos_credito() {
    validaciones valida;
    system("cls");
    Fecha sacado;
    Persona nuevaPersona;
    double monto = 0, tasa_interes = 0;
    int ncuotas = 0;

    std::string cedula;
    do {
        cedula = valida.ingresar_numeros_como_string("\nIngrese el numero de cedula: ");

        if (valida.validarCedula(cedula)) {
            if (nuevaPersona.verificarCedula(cedula)) {
                cout << "\nLa cedula ingresada existe" << endl;
            }
        } else {
            cout << "\nLa cedula ingresada es invalida. Vuelva a intentarlo." << endl;
        }
    }while (true);

    // Resto de la l�gica para ingresar los datos del cr�dito
    while (monto <= 999 || monto > 99999999.99) {
        monto = valida.ingresar_reales("\nIngrese el monto del credito");

        if (monto <= 999 || monto > 99999999.99) {
            printf("\nEl monto debe ser mayor a 999 y menor a 100M");
        } else {
            printf("                                                           ");
        }
    }
    while (ncuotas <= 0 || ncuotas > 500) {
        ncuotas = valida.ingresar_enteros("\nIngrese el numero de cuotas a pagar del credito");

        if (ncuotas <= 0 || ncuotas > 500) {
            printf("El numero de cuotas debe ser mayor a 0 y menor a 500");
        } else {
            printf("                                                           ");
        }
    }
    while (tasa_interes <= 0 || tasa_interes > 99.99) {
        tasa_interes = valida.ingresar_reales("\nIngrese la tasa de interes del credito");

        if (tasa_interes <= 0 || tasa_interes > 99.99) {
            printf("La tasa de interes debe ser mayor a 0 y menor a 100%");
        } else {
            printf("                                                           ");
        }
    }
    Credito credito(ncuotas, monto, sacado, tasa_interes);
    Amortizacion tabla(credito);
    printf("\n");
    imprimir();
    printf("\nTABLA GUARDADA CORRECTAMENTE");
    guardarTabla("tabla_amortizacion.txt");
    printf("\n");
    system("pause");
}

Credito Amortizacion::get_credito(){
    return credito;
}

ListaDoble<int>* Amortizacion::get_cuotas_ord(){
    return cuotas_ord;
}

ListaDoble<double>* Amortizacion::get_saldos_capital(){
    return saldos_capital;
}

ListaDoble<double>* Amortizacion::get_intereses(){
    return intereses;
}

ListaDoble<double>* Amortizacion::get_pagos_capital(){
    return pagos_capital;
}

ListaDoble<double>* Amortizacion::get_valor_cuotas(){
    return valor_cuotas;
}

ListaDoble<Fecha>* Amortizacion::get_fechas_pago(){
    return fechas_pago;
}

void Amortizacion::set_credito(Credito nuevo_credito){
    credito = nuevo_credito;
}

void Amortizacion::set_cuotas_ord(ListaDoble<int>* nuevo_cuotas_ord){
    cuotas_ord = nuevo_cuotas_ord;
}

void Amortizacion::set_saldos_capital(ListaDoble<double>* nuevo_saldos_capital){
    saldos_capital = nuevo_saldos_capital;
}

void Amortizacion::set_intereses(ListaDoble<double>* nuevo_intereses){
    intereses = nuevo_intereses;
}

void Amortizacion::set_pagos_capital(ListaDoble<double>* nuevo_pagos_capital){
    pagos_capital = nuevo_pagos_capital;
}

void Amortizacion::set_valor_cuotas(ListaDoble<double>* nuevo_valor_cuotas){
    valor_cuotas = nuevo_valor_cuotas;
}

void Amortizacion::set_fechas_pago(ListaDoble<Fecha>* nuevo_fechas_pago){
    fechas_pago = nuevo_fechas_pago;
}
