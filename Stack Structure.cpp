#include <stdio.h>
#include <malloc.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

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

struct libros{
	char nom[15];
	char aut[15];
	int npag;
	struct libros *sig;
};

typedef struct libros pila;
typedef pila *NODOPTR;

main(){
	int opc=0;
	char buscar[15];
	NODOPTR inicio=NULL; 
	NODOPTR iniciopa=NULL;
	NODOPTR actual=NULL;
	NODOPTR actualpa=NULL;
	NODOPTR nuevo=NULL;
	NODOPTR ant=NULL;
	do{
		system("cls");
		printf("Menu\n[1] Agregar\n[2] Eliminar\n[3] Consultar\n[4] Modificar\n[5] Salir\nElige una opcion: ");
		opc=valinum(1);
		switch(opc){
			case 1:
				system("cls");
				nuevo=(pila *)malloc(sizeof(pila));
				printf("Nombre: ");
				valitext(15,nuevo->nom);
				printf("\nAutor: ");
				valitext(15,nuevo->aut);
				printf("\nNumero de paginas: ");
				nuevo->npag=valinum(2);
				nuevo->sig=inicio;
				inicio=nuevo;
				break;
			case 2:
				system("cls");
				actual=inicio;
				printf("Ingrese el nombre del libro: ");
				valitext(15,buscar);
				while(actual!=NULL){
					if(strcmp(actual->nom,buscar)==0)
						break;
					else{
						if(iniciopa==NULL){
							iniciopa=inicio;
							actual=actual->sig;
							inicio=actual;
							iniciopa->sig=NULL;
						}
						else{
							actualpa=actual;
							actual=actual->sig;
							inicio=actual;
							actualpa->sig=iniciopa;
							iniciopa=actualpa;	
						}
					}	
				}
				if(actual==NULL){
					printf("\nNo se encontro el libro");
					getch();
				}
				else{
					printf("\nNombre: %s, Autor: %s, Numero de pagina: %i\n",actual->nom,actual->aut,actual->npag);
					printf("Desea Eliminarlo?\n[1] Si\n[0] No\nElija una opcion: ");
					opc=valinum(1);
					if(opc==1){
						inicio=inicio->sig;
						free(actual);
					}
				}	
				while(actualpa!=NULL){
					if(inicio==NULL){
						inicio=iniciopa;
						actualpa=actualpa->sig;
						iniciopa=actualpa;
						inicio->sig=NULL;
					}
					else{
						actual=actualpa;
						actualpa=actualpa->sig;
						iniciopa=actualpa;
						actual->sig=inicio;
						inicio=actual;	
					}
				}
				break;
			case 3:
				system("cls");
				actual=inicio;
				while(actual!=NULL){
					printf("\nNombre: %s, Autor: %s, Numero de pagina: %i\n",actual->nom,actual->aut,actual->npag);
					if(iniciopa==NULL){
						iniciopa=inicio;
						actual=actual->sig;
						inicio=actual;
						iniciopa->sig=NULL;
					}
					else{
						actualpa=actual;
						actual=actual->sig;
						inicio=actual;
						actualpa->sig=iniciopa;
						iniciopa=actualpa;	
					}
				}
				while(actualpa!=NULL){
					if(inicio==NULL){
						inicio=iniciopa;
						actualpa=actualpa->sig;
						iniciopa=actualpa;
						inicio->sig=NULL;
					}
					else{
						actual=actualpa;
						actualpa=actualpa->sig;
						iniciopa=actualpa;
						actual->sig=inicio;
						inicio=actual;	
					}
				}
				getch();
				break;
			case 4:
				system("cls");
				actual=inicio;
				printf("Ingrese el nombre del libro: ");
				valitext(15,buscar);
				while(actual!=NULL){
					if(strcmp(actual->nom,buscar)==0)
						break;
					else{
						if(iniciopa==NULL){
							iniciopa=inicio;
							actual=actual->sig;
							inicio=actual;
							iniciopa->sig=NULL;
						}
						else{
							actualpa=actual;
							actual=actual->sig;
							inicio=actual;
							actualpa->sig=iniciopa;
							iniciopa=actualpa;	
						}
					}	
				}
				if(actual==NULL){
					printf("\nNo se encontro el libro");
					getch();
				}
				else{
					printf("\nNombre: %s, Autor: %s, Numero de pagina: %i\n",actual->nom,actual->aut,actual->npag);
					printf("Desea modificarlo?\n[1] Si\n[0] No\nElija una opcion: ");
					opc=valinum(1);
					if(opc==1){
						printf("\nNuevo nombre: ");
						valitext(15,actual->nom);
						printf("\nNuevo autor: ");
						valitext(15,actual->aut);
						printf("\nNuevo numero de paginas: ");
						actual->npag=valinum(2);
						printf("\nSe realizado la modificacion");
						getch();
					}
				}	
				while(actualpa!=NULL){
					if(inicio==NULL){
						inicio=iniciopa;
						actualpa=actualpa->sig;
						iniciopa=actualpa;
						inicio->sig=NULL;
					}
					else{
						actual=actualpa;
						actualpa=actualpa->sig;
						iniciopa=actualpa;
						actual->sig=inicio;
						inicio=actual;	
					}
				}
				break;
			case 5:
				break;
			default:
				printf("\nIngrese una opcion valida");
				getch();
				break;					
		}
	}while(opc!=5);
	actual=inicio;
	while(actual!=NULL){
		inicio=inicio->sig;
		free(actual);
		actual=inicio;
		printf("\nSe libero el espacio\n");
	}
}
