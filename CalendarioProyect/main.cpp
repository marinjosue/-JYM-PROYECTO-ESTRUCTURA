#include "Calendario.cpp"
#include<stdio.h>

int main(){
int anio=2023;
int mes=1;
int dia=2;
  // Cr;ea un objeto de la clase Calendario
  Calendario calendario(anio, mes, dia); // Introduce el a�o, mes y d�a actual

  // Llama al m�todo calendario para imprimir el calendario del a�o actual

  calendario.calendarioM(anio);
  //calendario.marcarDia(dia);

  return 0;

	system("pause");




}
