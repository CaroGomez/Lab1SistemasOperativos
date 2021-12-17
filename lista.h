#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct nodo{
  char pid[100];
  char nombre[100];
  struct nodo *sig;
}proceso;

proceso *ListaProcesos(proceso *lista){
  lista = NULL;
  return lista;
}

proceso *agregarProceso(proceso *lista, char *pid, char *nombre) {
  proceso *nuevoProceso, *aux;
  nuevoProceso = (proceso*)malloc(sizeof(proceso));
  strcpy(nuevoProceso->pid, pid);
  strcpy(nuevoProceso->nombre, nombre);
  if(lista == NULL) {
    lista = nuevoProceso;
  } else {
    aux = lista;
    while (aux->sig != NULL) {
      aux = aux->sig;
    }
    aux->sig = nuevoProceso;
  }
  return lista;
}

void concatena(char c, char *cadena){
  char cadenaTemporal[2];
  cadenaTemporal[0] = c;
  cadenaTemporal[1] = '\0';
  strcat(cadena, cadenaTemporal);
}

void lista(int argc, char *argv[]) {
  proceso *lista = ListaProcesos(lista), *listaAux;
  char *processID;
  FILE *fptr;
  int c;
  bool finArchivo = false;
  char * secondToken = "";
  char * token = "";
  char linea[1000] = "";
  const char *s = "\r\n";
  char ruta[50] = "/proc/";
    for(int i = 2; i<argc; i++){
      strcat(ruta, argv[i]);
      strcat(ruta, "/status");
      fptr = fopen(ruta, "r");
      while (finArchivo == false){
        (c = getc(fptr));
        if(c != '\n'){
          concatena(c, linea);
        }else{
          token = strtok(linea, ":");
          secondToken =strtok(NULL, s);
          while (token != NULL){
            if(strcmp(token, "Name")==0){
              listaAux = lista;
              lista = agregarProceso(listaAux, argv[i], secondToken);
            }
            token = strtok(NULL, ":");
          }
          memset(linea, 0, 1000);
        }

        if (c == EOF) {
         finArchivo = true;
         memset(linea, 0, 1000);
       }
      }
      fclose(fptr);
      memset(linea, 0, 1000);
      memset(ruta, 0, 50);
      strcat(ruta, "/proc/");
      finArchivo = false;
      secondToken = "";
      token = "";
    }

printf("-- Información recolectada!!!\n");
  proceso *aux;
  aux = lista;
  while (aux != NULL) {
    printf("Pid: %s\n", aux->pid);
    printf("Nombre del proceso: %s\n", aux->nombre);
    printf("....\n");
    aux = aux->sig;
  }
}
