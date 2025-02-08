#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>

#define DEBUG

#define PROMPT_WELCOME "\n\n\t**************** Bienvenido a la calculadora de figuras de la UTEZ *****************\n\n"
#define PROMPT_MENU "\nSelecciona una de las siguientes opciones: \n\n\t· 1: Cubo\n\t· 2: pirámide\n\t· 3: cilindro\n\t· 4: Mostrar historial\n\t· 5: Salir\n > "

#define ERR_INVALID "\n\n\tERROR: Usa un entero como respuesta\n"
#define ERR_INVALID_DOUBLE "\nERROR: Usa un entero o decimal como respuesta\n > "
#define ERR_OUTOF_BOUNDS "\n\n\tERROR: opción inválida\n"
#define ERR_NEG_VAL "\nERROR: Solo se permiten valores positivos\n > "
#define ERR_ZERO_VAL "\nERROR: El valor no puede ser cero\n > "
#define ERR_MALLOC "\nERROR: Malloc failed on pointer: %p"


#define PROMPT_CONTINUE "\n\n\t *** Presiona [ENTER] para continuar ***"
#define PROMPT_OP_ROW "\n\t%-10s %9gu² %9gu³"  
#define PROMPT_CELL_STR "\n\t%-10s"
#define PROMPT_CELL_G "%11gu"
#define PROMPT_CELL_G2 "%11gu²"
#define PROMPT_CELL_G3 "%11gu³"

#define PROMPT_RESULT PROMPT_OP_ROW PROMPT_CONTINUE
#define PROMPT_HEADER "\n\t%-10s %10s %10s"
#define PROMPT_HEADER_COMPLETE "\n\t%-12s%12s%12s%12s%12s%12s%12s%12s"
#define PROMPT_END "\n\n\t*****+****** Hasta luego *************"

#define ASK_WIDTH "\nIntroduce e ancho de: %s\n > "
#define ASK_HEIGHT "\nIntroduce el alto de: %s\n > "
#define ASK_RADIUS "\nIntroduce el radio de: %s\n > "
#define ASK_SIDE "\nIntroduce el valor del lado de la base de: %s\n > "

#define PROMPT_HISTORY "\n\n\t ******** Historial **********\n" PROMPT_HEADER_COMPLETE
#define PROMPT_HISTORY_EMPTY "\n\n\t ****** El historial está vacío *****"

#define CLBUFF() while(getchar() != '\n')

typedef enum __menu_option__{
	CUBE,
	PYRAMID,
	CYLINDER,
	HISTORY,
	EXIT
} MenuOp;
typedef enum __figure_names__{
	CUBE_N,
	PYRAMID_N,
	CYLINDER_N
} FigureName;

static const char *figure_names_strings[15] = {
	"CUBO",
	"PIRÁMIDE",
	"CILINDRO"
};

typedef struct __figure__{
	FigureName name;
	double side;
	double width;
	double length;
	double height;
	double radius;
	double surface;
	double volume;
} Figure;

typedef struct history_node{
	Figure *value;
	struct history_node* next;
} history_node;

history_node *history_head;


#define PI 3.1415926

MenuOp askUserMenu();
void clearConsole();
void calcFigure(Figure *figure);
Figure *getFigureMeasurements(MenuOp figure_type);
double getDouble();
void saveFigure(Figure *fig);
void showHistory();

int main(){
	MenuOp option;
	while((option = askUserMenu()) != EXIT){
		if(option == HISTORY){
			showHistory();
			continue;
		}
		Figure *figure = getFigureMeasurements(option);
		calcFigure(figure);
	}

	printf(PROMPT_END);

	return 0;
}

MenuOp askUserMenu(){
	int res;
	int err = 0;
	clearConsole();
	while(err != 1){
		printf(PROMPT_WELCOME);
		printf(PROMPT_MENU);
		err = scanf(" %d", &res);
		if(err !=1){
			clearConsole();
			printf(ERR_INVALID);
			CLBUFF();

			continue;
		}
		switch(res){
			case 1:return CUBE;
			       break;
			case 2: return PYRAMID;
				break;
			case 3: return CYLINDER;
				break;
			case 4: return HISTORY;
				break;
			case 5: return EXIT;
				break;
			default:
				clearConsole();
				printf(ERR_OUTOF_BOUNDS);
				err = 0;
				break;
		}
		CLBUFF(); 
	};
	return EXIT;
		
}

void clearConsole(){
	system("@cls||clear");
}

void calcFigure(Figure *figure){
	printf(PROMPT_HEADER, "Figura", "Superficie", "Volúmen");
	CLBUFF();
	switch(figure->name){
		case CUBE_N:
			figure->surface = pow(figure->side, 2)*6;
			figure->volume = pow(figure->side,3);
			printf(PROMPT_RESULT, figure_names_strings[figure->name], figure->surface, figure->volume);
			getchar();
			break;
		case PYRAMID_N: 
			double base = pow(figure->side, 2);
			double half_side = (figure->side) / 2;
			double slant_squared = pow(figure->height, 2) + pow(half_side,2);
			double slant = sqrt(slant_squared);
			figure->surface = base + ((figure->side) * slant * 2);
			figure->volume = ((figure->height) * base) / 3;
			printf(PROMPT_RESULT, figure_names_strings[figure->name], figure->surface, figure->volume);
			getchar();
			break;
		case CYLINDER_N:
			double top_bottom_surface = 2 * PI * pow(figure->radius, 2);
			double lateral_surface = 2 * PI * (figure->radius) * (figure->height);
			figure->surface = top_bottom_surface + lateral_surface;
			figure->volume = PI * pow(figure->radius, 2) * (figure->height);
			printf(PROMPT_RESULT, figure_names_strings[figure->name], figure->surface, figure->volume);
			getchar();
			break;
		default:
			break;
	}
	saveFigure(figure);
};


Figure *getFigureMeasurements(MenuOp figure_type){
	int err = 0;
	Figure *figure = (Figure*) malloc(sizeof(Figure));
	CLBUFF();
	while(err != 1){
		err = 1;
		switch(figure_type){
			case CUBE:
				figure->name = CUBE_N;
				printf(ASK_SIDE, figure_names_strings[figure->name]);
				figure->side = getDouble();		
				break;
			case PYRAMID:
				figure->name = PYRAMID_N;
				printf(ASK_SIDE, figure_names_strings[figure->name]);
				figure->side = getDouble();
				printf(ASK_HEIGHT, figure_names_strings[figure->name]);
				figure->height = getDouble();
				break;
			case CYLINDER:
				figure->name = CYLINDER_N;
				printf(ASK_RADIUS, figure_names_strings[figure->name]);
				figure->radius = getDouble();
				printf(ASK_HEIGHT, figure_names_strings[figure->name]);
				figure->height = getDouble();
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
	int err;
	while((err = scanf(" %lf", &val)) != 1 || val <= 0){
		if(err != 1){
			printf(ERR_INVALID_DOUBLE);
		} else if(val == 0){
			printf(ERR_ZERO_VAL);
		} else{
			printf(ERR_NEG_VAL);
			
		}
		CLBUFF();
	};
	return val;
}


void showHistory(){
	CLBUFF();
	history_node *current = history_head;
	if(current == NULL){
		printf(PROMPT_HISTORY_EMPTY);
	} else {
		printf(PROMPT_HISTORY, "Figura", "Lado", "Ancho", "Largo", "Altura", "Radio", "Superficie", "Volúmen");
		
		while(current != NULL){
			double *values[] = {&(current->value->side), &(current->value->width), &(current->value->length), &(current->value->height),&(current->value->radius), &(current->value->surface), &(current->value->volume)};
			printf(PROMPT_CELL_STR, figure_names_strings[current->value->name]);

			for(int i = 0; i < 7; i++){
				switch(i){
					case 5:
						printf(PROMPT_CELL_G2,*values[i]);
						break;
					case 6:
						printf(PROMPT_CELL_G3, *values[i]);
						break;
					default:
						if(values[i] == NULL || (*values[i]) == 0){
							printf("%12s", "-");
						} else {
							printf(PROMPT_CELL_G, *values[i]);
						}
						break;
				}

			}

			current = current->next;
		}
	}
	printf(PROMPT_CONTINUE);
	getchar();
}

void saveFigure(Figure *fig){
	history_node *current = history_head;
	while(current != NULL && current->next != NULL){
		current = current->next;
	}
	history_node* ptr = (history_node*) malloc(sizeof(history_node));
	if(ptr != NULL){
		if(current== NULL){
			history_head = ptr;
			history_head->value = fig;
			return;
		}
		current->next = ptr;
		current->next->value = fig; 
	} else {
		printf(ERR_MALLOC, ptr);
	}
}

