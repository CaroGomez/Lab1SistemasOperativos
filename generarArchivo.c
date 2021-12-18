#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct nodo1{
  char pid[100];
  char nombre[100];
  struct nodo1 *sig;
}proceso;

proceso *Listaprocesos(proceso *lista){
  lista = NULL;
  return lista;
}

proceso *agregarproceso(proceso *lista, char *pid, char *nombre) {
  proceso *nuevoproceso, *aux;
  nuevoproceso = (proceso*)malloc(sizeof(proceso));
  strcpy(nuevoproceso->pid, pid);
  strcpy(nuevoproceso->nombre, nombre);
  if(lista == NULL) {
    lista = nuevoproceso;
  } else {
    aux = lista;
    while (aux->sig != NULL) {
      aux = aux->sig;
    }
    aux->sig = nuevoproceso;
  }
  return lista;
}

void concatena(char c, char *cadena){
  char cadenaTemporal[2];
  cadenaTemporal[0] = c;
  cadenaTemporal[1] = '\0';
  strcat(cadena, cadenaTemporal);
}

int main(int argc, char *argv[]) {
  proceso *lista = Listaprocesos(lista), *listaAux;
  char *processID;
  FILE *fptr;
  int c;
  bool finArchivo = false;
  char * secondToken = "";
  char * token = "";
  char nombreArchivoSalida[1000] = "psinfo-report-";
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
              lista = agregarproceso(listaAux, argv[i], secondToken);
              if (i == argc - 1){
                char *auxid = argv[i];
                strcat(nombreArchivoSalida, auxid);
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
    proceso *aux;
    aux = lista;
    while (aux != NULL) {
      fprintf(fptr,"Pid: %s\n", aux->pid);
      fprintf(fptr,"Nombre del proceso: %s\n", aux->nombre);
      fprintf(fptr,"....\n");
      aux = aux->sig;
    }

}
