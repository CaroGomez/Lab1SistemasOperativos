#include <stdio.h>
#include <stdlib.h>
#include "psinfo.h"
#include "lista.h"

int main(int argc, char *argv[]) {
  if(argc == 1){
    printf("Ha ingresado muy pocos argumentos, revise por favor y vuelva a intentarlo");
  }
  if(argc > 2){
    if (strcmp(argv[1],"-l")==0){
      lista(argc, argv);
    }
  }else{
    printf("Argumentos inválidos\n", );
  }
  if (argc = 2){
    psinfo(argv);
  }

  return 0;
}
