#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "psinfo.h"

typedef struct nodo{
  char * PID;
  char *nombre;
  struct nodo *sig;
}process;

process *ListaProcesos(process *lista){
  lista = NULL;
  return lista;
}

process *agregarProceso(process *lista, char * pid, char * nombre) {
  process * nuevoProceso, *aux;
  nuevoProceso = (process*)malloc(sizeof(process));
  strcpy(nuevoProceso->PID, pid);
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

int main(int argc, char *argv[]) {
  process *lista = ListaProcesos(lista);

  char *processID;
  FILE *fptr;
  int c;
  bool finArchivo = false;
  char * secondToken = "";
  char linea[1000] = "";
  const char *s = "\r\n";
  char ruta[50] = "/proc/";
  if (strcmp(argv[1],"-l")==0){
    for(int i = 2; i<=argc; i++){
      strcpy(processID, argv[i]);
      strcat(ruta, argv[i]);
      strcat(ruta, "/status");
      fptr = fopen(ruta, "r");
      while (finArchivo == false){
        (c = getc(fptr));
        if(c != '\n'){
          concatenar(c, linea);
        }else{
          char * token = strtok(linea, ":");
          secondToken =strtok(NULL, s);
          while (token != NULL) {
            if(strcmp(token, "Name")==0){
              lista = agregarProceso(lista, argv[i], secondToken);
            }token = strtok(NULL, " ");
          }
        }
        memset(linea, 0, 1000);
      }
      if (c == EOF) {
        finArchivo = true;
      }
    }
    fclose(fptr);
  }
  process *aux;
  aux = lista;
  while (aux != NULL) {
    printf("%s\n", aux->PID);
    printf("%s\n", aux->nombre);
    aux = aux->sig;
  }
  return 0;
}
