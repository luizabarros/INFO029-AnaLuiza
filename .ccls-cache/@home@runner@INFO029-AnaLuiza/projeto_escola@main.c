#ifndef MAIN_C
#define MAIN_C
#include <stdio.h>
#include <string.h>
#include "Student.c"
//#include "Subject.h"
//#include "Teacher.h"
int mainMenu(); 

int main(){
  int option = -1;
  int logout = 0;
  
  while (!logout){
    option = mainMenu();
    switch(option) {
      case 0:{
        printf("Sistema encerrado.\n");
        logout = 1;
        break;
      }  
      case 1:{
        students();
        break;
      }
      case 2:{
        //teachers();
        break;
      } 
      case 3:{
        //menuSubject();
        break;
      }
      default:{
        printf("Opção inválida! Digite novamente.\n");
      }
        
    }  
  }

  return 0;
}

int mainMenu(){
  int option;
  printf("Bem vindo ao sistema!\n");
  printf("0 - sair\n");
  printf("1 - administrar alunos\n");
  printf("2 - administrar professores\n");
  printf("3 - administrar disciplinas\n");
  printf("Digite sua opção:\n");

  scanf("%d", &option);
  
  return option;
}

#endif