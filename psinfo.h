#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void concatenar(char c, char *cadena){
  char cadenaTemporal[2];
  cadenaTemporal[0] = c;
  cadenaTemporal[1] = '\0';
  strcat(cadena, cadenaTemporal);
}

void psinfo(char *argv[]){
  int c;
  char linea[1000] = "";
  const char s[4] = "\r\n";
  char * secondToken = "";
  char name[100] = "", state[100] = "", vmSize[100] = "", vmExe[100] = "", vmData[100] = "", vmstk[100] = "", vcs[100] = "", nvcs[100] = "";

  bool finArchivo = false;
  char ruta[50] = "/proc/";
  strcat(ruta, argv[1]);
  strcat(ruta, "/status");
  FILE *fptr = fopen(ruta, "r");
  while (finArchivo == false){
    (c = getc(fptr));
    if(c != '\n'){
      concatenar(c, linea);
    }else{
      char * token = strtok(linea, ":");
      secondToken =strtok(NULL, s);
      while (token != NULL) {
        if(strcmp(token, "Name")==0){
          strcpy(name, secondToken);
        }
        if(strcmp(token, "State")==0){
          strcpy(state, secondToken);
        }
        if(strcmp(token, "VmSize")==0){
          strcpy(vmSize, secondToken);
        }
        if(strcmp(token, "VmExe")==0){
          strcpy(vmExe, secondToken);
        }
        if(strcmp(token, "VmData")==0){
          strcpy(vmData, secondToken);
        }
        if(strcmp(token, "VmStk")==0){
          strcpy(vmstk, secondToken);
        }
        if(strcmp(token, "voluntary_ctxt_switches")==0){
          strcpy(vcs, secondToken);
        }
        if(strcmp(token, "nonvoluntary_ctxt_switches")==0){
          strcpy(nvcs, secondToken);
        }
        token = strtok(NULL, " ");
      }
      memset(linea, 0, 1000);
    }
    if (c == EOF) {
      finArchivo = true;
      memset(linea, 0, 1000);
    }
  }
  fclose(fptr);
  fflush(stdin);
  memset(linea, 0, 1000);
  memset(ruta, 0, 50);
  strcat(ruta, "/proc/");
  finArchivo = false;
  secondToken = "";

  printf("Nombre del proceso: %s\n", name );
  printf("Estado: %s\n", state );
  if(strcmp(vmSize, "")==0){
    printf("Este proceso no tiene imagen de memoria \n");
  }else{printf("Tamaño total de la imagen de memoria: %s\n", vmSize);}
  if(strcmp(vmExe, "")==0){
    printf("El proceso no tiene VmExe\n");
  }else{printf("\t Tamaño de la memoria en la región TEXT: %s\n", vmExe);}
  if(strcmp(vmExe, "")==0){
    printf("El proceso no tiene VmData\n");
  }else{printf("\t Tamaño de la memoria en la región DATA: %s\n", vmData );}
  if(strcmp(vmExe, "")==0){
    printf("El proceso no tiene VmStk\n");
  }else{printf("\t Tamaño de la memoria en la región STACK: %s\n", vmstk );}

  printf("Número de cambios de conexto realizados (voluntarios - no voluntarios) %s - %s\n", vcs, nvcs);

}
