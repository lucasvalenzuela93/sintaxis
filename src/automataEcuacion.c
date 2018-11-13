#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int columna (char c);
int automata(char* s);
int operacion(int,int,char);

int main(){

char cadena[100];
printf("Ingrese una ecuacion: ");
scanf("%s", &cadena);
printf("Resultado = %i\n", automata(cadena));
return 0;
}

int columna(char c){	// pasa al sgte de la tabla de transicion
if( isdigit(c) ) return 0;
if( c == '+' || c == '-' ) return 1;
if( c == '*' || c == '/' ) return 2;
return 3;
}

int automata(char* s){
static int tabla[5][3] = {
{1,4,4},	// 0 estado inicial
{1,2,3},	// 1 estado final (tambien leer otro digito)
{1,4,4},	// 2 sumar/restar
{1,4,4},	// 3 multiplicar/dividir
{4,4,4}	// 4 estado de rechazo
};

int estado = 0;		//estado actual
int i = 0;			//recorre la cadena
char c;

int resultado = 0;		//guarda el resultado de la operacion
int expresion = 0;
int signo = 1;
char op = '+';

/* Recorro tabla */

while( s[i]!='\0'  && estado != 4) {


	c = s[i];
	estado = tabla[ estado ][ columna(c) ];
	i++;

	switch( estado ){			// analiza segun cada estado y realiza la accion
		case 0:
			return -1;
			break;
		case 1:
			expresion = expresion * 10 + ( c - '0' );
			break;
		case 2:
			resultado = operacion(resultado, expresion, op);
			op = c;
			expresion = 0;
			break;
		case 3:
			resultado = operacion(resultado, expresion, op);
			op = c;
			expresion = 0;
			break;

		default:
			return -1;
		}
}
resultado = operacion(resultado, expresion, op);
return resultado;
}

int operacion(int resultado, int expresion, char op){
if(op == '+')
return resultado + expresion;

if(op == '-')
	return resultado - expresion;

if(op == '*'){
	return resultado * expresion;
}

if(op == '/')
	return resultado / expresion;
}
