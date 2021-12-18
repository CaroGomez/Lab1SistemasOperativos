#include <stdio.h>
#include <stdlib.h>
#include "psinfo.h"
#include "lista.h"
#include "generarArchivo.h"

int main(int argc, char *argv[]) {
  if(argc == 1){
    printf("Ha ingresado muy pocos argumentos, revise por favor y vuelva a intentarlo");
  }else if(argc > 2){;
    if (strcmp(argv[1],"-l")==0){
      lista(argc, argv);
    }
    else if (strcmp(argv[1],"-r")==0){
      generarArchivo(argc, argv);
    }else{
      printf("El parámetro ingresado no es correcto\n");
    }
  }else if (argc = 2){
    psinfo(argv);
  }else{
    printf("Argumentos inválidos\n");
  }
  return 0;
}
