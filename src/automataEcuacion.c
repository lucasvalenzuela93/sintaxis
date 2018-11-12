#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int columna (char c);
int automata(char* s);

int main(){

	char cadena[100];
	printf("Ingrese una ecuacion: ");
	scanf("%s", &cadena);
	printf("Resultado = %s", automata(cadena));
	return 0;

}


int columna(char c){						// pasa al sgte de la tabla de transicion
	if( isdigit(c) ) return 0;
	if( c == '+' || c == '-' ) return 1;
	if( c == '*' || c == '/' ) return 2;
	return 3;
}


int automata(char* s){
	static int tabla[5][3] = {
			{1,4,4},			// 0 estado inicial
			{1,2,3},			// 1 estado final (tambien leer otro digito)
			{1,4,4},			// 2 sumar/restar
			{1,4,4},			// 3 multiplicar/dividir
			{4,4,4}		 		// 4 estado de rechazo
	};

	int estado = 0;		//estado actual
	int i = 0;			//recorre la cadena
	char c = s[0];

	int resultado = 0;		//guarda el resultado de la operacion
	int expresion = 0;
	printf("chekpoint");

	/* Recorro tabla */

	while( s[i]!='\0'  && estado != 4) {

		estado = tabla[ estado ][ columna(c) ];
		i++;
		c = s[i];
	}
	printf("recorrio tabla");

	switch( estado ){			// analiza segun cada estado y realiza la accion
			case 0:
				return -1;
				break;
			case 1:
				expresion = expresion * 10 + ( c - '0' );
				printf("se acumulo");
				break;
			case 2:
				if( c=='+' ){

					resultado += expresion;
					printf("sumo");
				} else {
					resultado -= expresion;
					printf("resto");
				}
				break;
			case 3:
				if( c=='*' ){
					resultado = expresion * resultado;
					printf("mult");
				} else {
					resultado = expresion / resultado;
					printf("divido");
				}
				break;

			default:
				return -1;
	}

	if( c == '\0' ){
		return resultado;
	};

}
