#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
#include<stdlib.h>

#define PROMPT_WELCOM "\n\n\t**************** Bienvenido a la calculadora de figuras de la UTEZ *****************\n\n"
#define PROMPT_MENU "\nSelecciona una de las siguientes opciones: \n\n\t· 1: Cubo\n\t· 2: pirámide\n\t· 3: cilindro\n\t· 4: Salir\n > "
#define PROMPT_INVALID "\nERROR: Usa un caractér como respuesta"
#define PROMPT_OUTOF_BOUNDS "\nERROR: Respuesta inválida"
#define PROMPT_RESULT "\n\tFigura\tárea\tvolúmen\n\t%s\t%lf\t%lf\n"
#define PROMPT_END "\n\n\t*****+****** Hasta luego *************"

typedef enum __menu_option__{
	CUBE,
	PYRAMID,
	CYLINDER,
	EXIT
} MenuOp;

typedef struct __figure__{
	char name[10];
	double area;
	double volume;
} Figure;
#define PI 3.1415926

MenuOp askUserMenu();
void clearConsole();
Figure calcFigure();

int main(){
}

MenuOp askUserMenu(){
}

void clearConsole(){
}

