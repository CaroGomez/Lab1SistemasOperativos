#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct nodo1{
  char pid[100];
  char nombre[100];
  struct nodo1 *sig;
}proceso1;

proceso1 *Listaproceso1s(proceso1 *lista){
  lista = NULL;
  return lista;
}

proceso1 *agregarproceso1(proceso1 *lista, char *pid, char *nombre) {
  proceso1 *nuevoproceso1, *aux;
  nuevoproceso1 = (proceso1*)malloc(sizeof(proceso1));
  strcpy(nuevoproceso1->pid, pid);
  strcpy(nuevoproceso1->nombre, nombre);
  if(lista == NULL) {
    lista = nuevoproceso1;
  } else {
    aux = lista;
    while (aux->sig != NULL) {
      aux = aux->sig;
    }
    aux->sig = nuevoproceso1;
  }
  return lista;
}

void concatena2(char c, char *cadena){
  char cadenaTemporal[2];
  cadenaTemporal[0] = c;
  cadenaTemporal[1] = '\0';
  strcat(cadena, cadenaTemporal);
}

void generarArchivo(int argc, char *argv[]) {
  printf("inicio");
  proceso1 *lista = Listaproceso1s(lista), *listaAux;
  char *processID;
  FILE *fptr;
  int c;
  bool finArchivo = false;
  char * secondToken = "";
  char * token = "";
  char * nombreArchivoSalida = "psinfo-report-";
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
          concatena2(c, linea);
        }else{
          token = strtok(linea, ":");
          secondToken =strtok(NULL, s);
          while (token != NULL){
            if(strcmp(token, "Name")==0){
              listaAux = lista;
              lista = agregarproceso1(listaAux, argv[i], secondToken);
              if (i == argc - 1){
                strcat(nombreArchivoSalida, argv[i]);
              } else {
                strcat(nombreArchivoSalida, argv[i]);
                strcat(nombreArchivoSalida, "-");
              }
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

    fptr = fopen(nombreArchivoSalida, "w");
    fprintf(fptr,"-- Información recolectada!!!\n");
    proceso1 *aux;
    aux = lista;
    while (aux != NULL) {
      fprintf(fptr,"Pid: %s\n", aux->pid);
      fprintf(fptr,"Nombre del proceso1: %s\n", aux->nombre);
      fprintf(fptr,"....\n");
      aux = aux->sig;
    }

}
