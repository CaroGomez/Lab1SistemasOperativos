#include <stdio.h>
#include <stdlib.h>
#include "psinfo.h"

int main(int argc, char const *argv[]) {
  if(argc == 1){
    printf("por favor ingrese el PID del proceso \n");
  }
  if(argc > 2){
    printf("Se ingresaron muchos argumentos\n");
  }
  
  psinfo(argv);
  return 0;
}
