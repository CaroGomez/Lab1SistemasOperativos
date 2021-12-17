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

int main(int argc, char const *argv[]) {
  if(argc == 1){
    printf("por favor ingrese el PID del proceso \n");
  }
  if(argc > 2){
    printf("Se ingresaron muchos argumentos\n");
  }
  int c;
  char linea[1000] = "";
  char auxiliarLinea[1000] = "";
  char name[100] = "", state[100] = "", vmExe[100] = "", vmData[100] = "", vmstk[100] = "", vcs[100] = "", nvcs[100] = "";
  FILE *fptr;
  bool finArchivo = false, variableEncontrada = false;
  char ruta[50] = "/proc/";
  strcat(ruta, argv[1]);
  strcat(ruta, "/status");
  fptr = fopen(ruta, "r");
  while (finArchivo == false){
    (c = getc(fptr));
    if(c != '\n'){
      concatenar(c, linea);
    }else{
      strcpy(auxiliarLinea, linea);
      char * token = strtok(linea, ":");
      while (token != NULL) {
        if(strcmp(token, "Name")==0){
          strcpy(name, auxiliarLinea);
        }
        if(strcmp(token, "State")==0){
          strcpy(state, auxiliarLinea);
        }
        if(strcmp(token, "VmExe")==0){
          strcpy(vmExe, auxiliarLinea);
        }
        if(strcmp(token, "VmData")==0){
          strcpy(vmData, auxiliarLinea);
        }
        if(strcmp(token, "VmStk")==0){
          strcpy(vmstk, auxiliarLinea);
        }
        if(strcmp(token, "voluntary_ctxt_switches")==0){
          strcpy(vcs, auxiliarLinea);
        }
        if(strcmp(token, "nonvoluntary_ctxt_switches")==0){
          strcpy(nvcs, auxiliarLinea);
        }
        token = strtok(NULL, " ");
      }
      memset(linea, 0, 1000);
    }
    if (c == EOF) {
      finArchivo = true;
    }
  }
  printf("%s\n", name );
  printf("%s\n", state );
  if(strcmp(vmExe, "")==0){
    printf("El proceso no tiene VmExe\n");
  }else{printf("%s\n", vmExe);}
  if(strcmp(vmExe, "")==0){
    printf("El proceso no tiene VmData\n");
  }else{printf("%s\n", vmData );}
  if(strcmp(vmExe, "")==0){
    printf("El proceso no tiene VmStk\n");
  }else{printf("%s\n", vmstk );}

  printf("%s\n", vcs );
  printf("%s\n", nvcs );
  return 0;
}
