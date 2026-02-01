#include <stdio.h>
#include <windows.h>
#include <malloc.h>
#include <conio.h>

struct alumnos{
	int mat;
	char nom[10];
	int edad;
	struct alumnos *sig;
};

typedef struct alumnos nodo;
typedef nodo *NODOPTR;

int valinum(int lon){
	char c;
	char numero[10];
	int x=0;
	x=0;
	do{
		c=getch();
		if(c>=48 && c<=57){
			printf("%c",c);
        	numero[x]=c;
        	x++;
    	}
    	else if(c==8 && x>0){
			x--;
        	printf("\b \b");
       }
	}while(c!=13 && x<lon);
	numero[x]='\0';
	return atoi(numero);
}

void valitext(int lon,char *pnom){
	int c=0, x=0;
    do{
		c=getch();
        if(c>=65 && c<=90 || c>=97 && c<=122 || c==32 || c==164 || c==165){
			printf("%c",c);
            *(pnom+x)=c;
            x++;
        }
        if(c==8 && x>0){
			x--;
		    printf("\b \b");
	        *(pnom+x)=' ';
        }
    }while(c!=13 && x<lon);
}

main(){
	int opc=0;
	NODOPTR nuevo=NULL;
	NODOPTR inicio=NULL;
	NODOPTR actual=NULL;
	
	do{
		system("cls");
		opc=0;
		printf("Menu\n[1] Agregar\n[2] Borrar\n[3] Consultar\n[4] Modificar\n[5] Salir\nEscoja una opcion: ");
		scanf("%i",&opc);
		switch(opc){
			case 1:
				system("cls");
				nuevo=(nodo *)malloc(sizeof(nodo));
				printf("Matricula: ");
				nuevo->mat=valinum(4); //se usa el -> en memoria dinamica
				fflush(stdin);
				printf("\nNombre: ");
				valitext(10,nuevo->nom);
				printf("\nEdad: ");
				nuevo->edad=valinum(2);
				nuevo->sig=NULL;
				if(inicio==NULL)
					inicio=nuevo;
				else{
					actual=inicio;
					while(actual->sig!=NULL){
						actual=actual->sig;
					}	
					actual->sig=nuevo;
				}
				break;
			case 2:
				break;
			case 3:
				actual=inicio;
				printf("Actual\tMatricula\tNombre\tEdad\tSiguiente\n");
				while(actual!=NULL){
					printf("%p\t%i\t%s\t%i\t%p\n",actual,actual->mat,actual->nom,actual->edad,actual->sig);
					actual=actual->sig;
				}
				getch(); //para que espere hasta que el usuario presione una tecla
				break;
			case 4:
				actual=inicio;
				int band=0;
				if(actual!=NULL){
					printf("Ingrese la matricula que desea buscar\n");
					int buscar=valinum(4);
					if(buscar==actual->mat)
						band=1;
					else{
						while(actual!=NULL){
							if(actual->mat==buscar){
								band=1;
								break;
							}else
								actual=actual->sig;
						}
					}	
					if(band==1){
						printf("Se encontro el alumno con la matricula %i\n",actual->mat);
						printf("Ingrese el nuevo nombre\n");
						scanf("%s",&actual->nom);
						printf("Ingrese la nueva edad\n");
						actual->edad=valinum(2);
						break;
					}else{
						printf("No se encontro la matricula ingresada\n");
						getch();
					}
				}
				//si buscas un alumno por matricula que te pida registrar de nuevo el nombre y la edad
				break;				
		}
	}while(opc!=5);
	actual=inicio;
	while(actual!=NULL){
		inicio=inicio->sig;
		free(actual);
		actual=inicio;
		printf("Se libero el espacio\n");
	}
	printf("Programa Finalizado...");
}

//agregar, borrar, consulta, modificacion, salir
