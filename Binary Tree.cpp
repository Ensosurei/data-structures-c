#include<stdio.h>
#include<conio.h>
#include<malloc.h>
#include<windows.h>

struct Arbol{
	int valor;
	struct Arbol *Izq;
	struct Arbol *Der;
};

void Insertar (struct Arbol **, int); //**Signica que manejamos un almacenamiento distinto, pero sigue siendo un puntero
struct Arbol *Borrar (struct Arbol *Raiz, int clave);
void Mostrar (struct Arbol *, int);
struct Arbol *Buscar (struct Arbol *, int);
void Inorden (struct Arbol *);
void Preorden (struct Arbol *);
void Postorden (struct Arbol *);


main(){
	int op, num;
	struct Arbol *Raiz=NULL;
	do{
		system("cls");
		printf("1. Insertar\n");
		printf("2. Borrar\n");
		printf("3. Buscar\n");
		printf("4. Mostrar\n");
		printf("5. Inorden\n");
		printf("6. Postorden\n");
		printf("7. Preorden\n");
		printf("8. Salir\n");
		printf("Selecciona la opcion: ");
		scanf("%i",&op);
		switch(op){
			case 1:
				printf("\nNumero: ");
				scanf("%i",&num);
				Insertar(&Raiz,num); //esto es para poder pasar parametros a una funcion con **
				break;
			case 2:
				printf("Capture el numero a borrar: ");
				scanf("%i",&num);
				Borrar(Raiz,num);
				break;
			case 3:
				printf("Capture el numero a buscar: ");
				scanf("%i",&num);
				if(Buscar(Raiz,num)==NULL)
					printf("No se encontro");
				else
					printf("Se encontro");
				getch();		
				break;
			case 4:
				printf("Los nodos del Arbol son...\n");
				Mostrar(Raiz, 0);
				getch();
				break;
			case 5:
				Inorden(Raiz);
				getch();
				break;
			case 6:
				Postorden(Raiz);
				getch();
				break;
			case 7:
				Preorden(Raiz);
				getch();
				break;
		}
	}while(op!=8);
}

void Insertar(struct Arbol **Raiz,int n){
	if(*Raiz==NULL){
		*Raiz=(struct Arbol *)malloc(sizeof(struct Arbol));
		(*Raiz)->valor=n;
		(*Raiz)->Izq=NULL;
		(*Raiz)->Der=NULL;
	}
	else if(n < (*Raiz)->valor)
		Insertar(&(*Raiz)->Izq,n);
	else if(n > (*Raiz)->valor)	
		Insertar(&(*Raiz)->Der,n);
	else{
		printf("\nNumero Duplicado");
		getch();
	}	
}

void Mostrar(struct Arbol *Raiz, int n){
	int i;
	if(Raiz!=NULL){
		Mostrar(Raiz->Der,n+1);
		for(i=0; i < n; ++i) // ++i es para que lo haga despues de que el ciclo haya hecho sus cosas
			printf("   ");
		printf("%i\n",Raiz->valor);
		Mostrar(Raiz->Izq,n+1);
	}	
}

struct Arbol *Buscar (struct Arbol *Raiz, int n){
	if(Raiz==NULL)
		return NULL;
	else if(Raiz->valor==n)
		return Raiz;
	else if(n>Raiz->valor)
		return Buscar(Raiz->Der,n);
	else if(n<Raiz->valor)
		return Buscar(Raiz->Izq,n);	
}

void Preorden (struct Arbol *Raiz){
	if(Raiz!=NULL){
		printf("%i\n",Raiz->valor);
		Preorden(Raiz->Izq);
		Preorden(Raiz->Der);
	}
}

void Inorden (struct Arbol *Raiz){
	if(Raiz!=NULL){
		Inorden(Raiz->Izq);
		printf("%i\n",Raiz->valor);
		Inorden(Raiz->Der);
	}
}

void Postorden (struct Arbol *Raiz){
	if(Raiz!=NULL){
		Postorden(Raiz->Izq);
		Postorden(Raiz->Der);
		printf("%i\n",Raiz->valor);
	}
}

struct Arbol *Borrar(struct Arbol *Raiz, int clave) { 
	struct Arbol *p, *p2;
	if(!Raiz){
		printf("%i elemento no encontrado. \n", clave);
		getch();
		return Raiz;
	}
	if (Raiz->valor==clave) {
		if (Raiz->Izq==Raiz->Der) {
			free (Raiz);
			return NULL;
		}
		else if (Raiz->Izq==NULL){
			p=Raiz->Der;
			free (Raiz);
			return p;
		}
		else if(Raiz->Der==NULL) {
			p=Raiz -> Izq;
			free (Raiz);
			return p;
		}
		else{
			p2=Raiz->Der;
			p=Raiz->Der;
			while(p->Izq)
				p=Raiz->Der;
			while(p->Izq)
				p=p->Izq;
			p->Izq=Raiz->Izq;
			free (Raiz); 
			return p2;
		}
	}
	if (Raiz->valor < clave)
		Raiz->Der=Borrar(Raiz->Der, clave);
	else
		Raiz->Izq=Borrar(Raiz->Izq, clave);
	return Raiz;
}
