#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
#include<stdlib.h>

#define DEBUG

#define PROMPT_WELCOM "\n\n\t**************** Bienvenido a la calculadora de figuras de la UTEZ *****************\n\n"
#define PROMPT_MENU "\nSelecciona una de las siguientes opciones: \n\n\t· 1: Cubo\n\t· 2: pirámide\n\t· 3: cilindro\n\t· 4: Salir\n > "
#define ERR_INVALID "\nERROR: Usa un entero como respuesta\n > "
#define ERR_INVALID_DOUBLE "\nERROR: Usa un entero o decimal comorespuesta:\n > "
#define ERR_OUTOF_BOUNDS "\nERROR: opción inválida"
#define PROMPT_RESULT "\n\tFigura\tárea\tvolúmen\n\t%s\t%lf\t%lf\n\n\t *** Presiona [ENTER] para continuar ***"
#define PROMPT_END "\n\n\t*****+****** Hasta luego *************"
#define ASK_WIDTH "\nIntroduce e ancho de%s\n > "
#define ASK_HEIGHT "\nIntroduce el alto de%s\n > "
#define ASK_RADIUS "\nIntroduce el radio de%s\n > "
#define ASK_SIDE "\nIntroduce el valor del lado del cuadrado\n > "

typedef enum __menu_option__{
	CUBE,
	PYRAMID,
	CYLINDER,
	EXIT
} MenuOp;

typedef struct __figure__{
	char name[10];
	double side;
	double width;
	double height;
	double radius;
	double area;
	double volume;
} Figure;

#define PI 3.1415926

MenuOp askUserMenu();
void clearConsole();
void calcFigure(MenuOp figure_type, Figure *figure);
Figure getFigureMeasures(MenuOp figure_type);
double getDouble();

int main(){
}

MenuOp askUserMenu(){
	int res;
	int err = 0;
	while(err != 1){
		clearConsole();
		printf(PROMPT_MENU);
		err = scanf(" %d", &res);
		if(err !=1){
			printf(ERR_INVALID);
			while(getchar() != '\n');
			continue;
		}
		switch(res){
			case 1:return CUBE;
			       break;
			case 2: return PYRAMID;
				break;
			case 3: return CYLINDER;
				break;
			case 4: return EXIT;
				break;
			default:
				printf(ERR_OUTOF_BOUNDS);
				err = 0;
				break;
		}
		while(getchar() != '\n');
	};
		
}

void clearConsole(){
	system("@cls||clear");
}

void calcFigure(MenuOp figure_type, Figure *figure){

};


Figure getFigureMeasures(MenuOp figure_type){
	int err = 0;
	double measure;
	Figure figure = (Figure) {};
	while(getchar() != '\n');
	while(err != 1){
		err = 1;
		switch(figure_type){
			case CUBE:
				printf(ASK_SIDE);
				figure.side = getDouble();		
				break;
			case PYRAMID:
				printf(ASK_WIDTH, " la pirámide");
				figure.width = getDouble();
				printf(ASK_HEIGHT, " la priámide");
				figure.height = getDouble();
				break;
			case CYLINDER:
				printf(ASK_RADIUS, "l cilindro");
				figure.radius = getDouble();
				printf(ASK_HEIGHT, "l cilindro");
				figure.height = getDouble();
				break;
			default:
				err = 0;
				printf(ERR_OUTOF_BOUNDS);
				break;
				
			
		}
	}
	return figure;
		
}

double getDouble(){
	double val;
	while(scanf(" %lf", &val) != 1){
		printf(ERR_INVALID);
		while(getchar() != '\n');
	};
	return val;
}
