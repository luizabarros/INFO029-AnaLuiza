#ifndef STUDENT_C
#define STUDENT_C
#include "Generic.c"
#include <stdio.h>
#include <string.h>

void students() {
  int option = -1, createdPerson = 0, qtd_std = 0, days[50];

  option = menu("alunos");

  switch (option) {
  case 0:
    printf("Sistema encerrado.\n");
    break;
  case 1:
    do {
      createdPerson = createPerson("S", qtd_std, days);
    } while (createdPerson == 1);
    qtd_std++;
    break;
  case 2:
    updatePerson("S", days);
    break;
  case 3:
    deletePerson("S");
    break;
  case 4:
    getAll("S");
    break;
  case 5:
    listPersonSex("S");
    break;
  case 6:
    listPersonDate("S", days);
    break;
  case 7:
    listPersonName("S");
    break;
  default:
    printf("Opção inválida! Digite novamente.\n");
    break;
  }
};

#endif