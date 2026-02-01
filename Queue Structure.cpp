#include <stdio.h>
#include <windows.h>
#include <malloc.h>
#include <conio.h>
#include <string.h>

struct archivo{
	char nom[15];
	int tam;
	struct archivo *sig;
};

typedef struct archivo nodo;
typedef nodo *NODOPTR;

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
    *(pnom+x)='\0';
}


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

main(){
	int opc=0;
	char buscar[15];
	NODOPTR nuevo=NULL;
	NODOPTR actual=NULL;
	NODOPTR inicio=NULL;
	NODOPTR ant=NULL;
	do{
		system("cls");
		opc=0;
		printf("Menu\n[1] Agregar\n[2] Imprimir\n[3] Cancelar\n[4] Prioridad\n[5] Mostrar\n[6] Salir\nElige una opcion: ");
		opc=valinum(1);
		switch(opc){
			case 1:
				system("cls");
				nuevo=(nodo *)malloc(sizeof(nodo));
				printf("Nombre: ");
				valitext(15,nuevo->nom);
				printf("\nTama%co: ",164);
				nuevo->tam=valinum(4);
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
				system("cls");
				actual=inicio;
				inicio=inicio->sig;
				printf("\nSe ha impreso el archivo con nombre %s",actual->nom);
				free(actual);
				getch();
				break;	
			case 3:
				system("cls");
				actual=inicio;
				printf("Ingrese el nombre del archivo\n");
				valitext(15,buscar);
				while(actual!=NULL){
					if(strcmp(actual->nom,buscar)==0)
						break;
					else{
						ant=actual;
						actual=actual->sig;
					}
				}
				if(actual==NULL){
					printf("\nNo se encontro el archivo");
					getch();
				}
				else{
					printf("\nNombre %s\n Tama%co %i",actual->nom,164,actual->tam);
					printf("\nDesea cancelar el archivo?\n[1] Si\n[0] No\n");
					scanf("%i",&opc);
					if(opc==1){
						if(actual==inicio)
							inicio=inicio->sig;
						else
							ant->sig=actual->sig;
						free(actual);		
					}
				}	
				break;
			case 4:
				system("cls");
				actual=inicio;
				printf("Ingrese el nombre del archivo\n");
				valitext(15,buscar);
				while(actual!=NULL){
					if(strcmp(actual->nom,buscar)==0)
						break;
					else{
						ant=actual;
						actual=actual->sig;
					}	
				}
				if(actual==NULL)
					printf("\nNo se encontro el archivo");
				else{
					if(actual==inicio || actual==inicio->sig)
						printf("\nNo se le puede dar prioridad al primero o segundo de la cola");
					else{
						ant->sig=actual->sig;
						actual->sig=inicio->sig;
						inicio->sig=actual;
						printf("\nEl archivo %s ahora tiene la maxima prioridad",actual->nom);
					}
				}	
				getch();
				break;		
			case 5:
				system("cls");
				actual=inicio;
				while(actual!=NULL){
					printf("\nNombre: %s, Tama%co: %i, Direccion: %p\n",actual->nom,164,actual->tam,actual->sig);
					actual=actual->sig;
				}
				getch();
				break;	
			case 6:
				break;
			default:
				printf("\nIngrese una opcion valida");
				getch();
				break;			
		}
	}while(opc!=6);
	actual=inicio;
	while(actual!=NULL){
		inicio=inicio->sig;
		free(actual);
		actual=inicio;
		printf("\nSe libero el espacio\n");
	}
}
