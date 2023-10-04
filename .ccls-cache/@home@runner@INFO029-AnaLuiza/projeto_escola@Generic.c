#include "Extra.c"
#include "Student.h"
#include "Teacher.h"
#include <stdio.h>
#include <string.h>

int menu(char topic[]) {
  int option = -1, checkOption = 0;

  printf("<<<Opções>>>\n");
  printf("0 - sair\n");
  printf("1 - criar %s\n", topic);
  printf("2 - editar %s\n", topic);
  printf("3 - deletar %s\n", topic);
  printf("4 - buscar todos\n");
  printf("5 - Buscar %s por sexo\n", topic);
  printf("6 - Listar %s por data de nascimento\n", topic);
  printf("7 - Listar %s pelo nome\n", topic);
  printf("Digite sua opção: ");

  while (option < 0 || option > 7) {
    if (checkOption > 0) {
      printf("Opção inválida! Digite novamente.\n");
    }
    scanf("%d", &option);
    checkOption++;
  }

  return option;
}

int createPerson(char type[], int qtd, int days[]) {
  int regis, option = 0;

  while (option != 1) {
    printf("Digite a matrícula: \n");

    if (type[0] == 'S') {
      scanf("%d", &regis);
      getchar();
      studentsList[qtd].registration = regis;
    } else {
      scanf("%d", &regis);
      getchar();
      teachersList[qtd].registration = regis;
    }

    printf("Nome: \n");
    fgets(type[0] == 'S' ? studentsList[qtd].name : teachersList[qtd].name, 50, stdin);

    printf("Sexo: \n");
    if (type[0] == 'S') {
      scanf("%d", &studentsList[qtd].sex);
      getchar();
    } else {
      scanf("%d", &teachersList[qtd].sex);
      getchar();
    }

    printf("Data de nascimento \n");

    printf("Dia: ");
    if (type[0] == 'S') {
      scanf("%d", &studentsList[qtd].dateOfBirth[0]);
      getchar();
      days[qtd] = studentsList[qtd].dateOfBirth[0];
    } else {
      scanf("%d", &teachersList[qtd].dateOfBirth[0]);
      getchar();
      days[qtd] = teachersList[qtd].dateOfBirth[0];
    }

    printf("Mês: ");
    if (type[0] == 'S') {
      scanf("%d", &studentsList[qtd].dateOfBirth[1]);
      getchar();
      days[qtd] = days[qtd] + studentsList[qtd].dateOfBirth[1] * 100;
    } else {
      scanf("%d", &teachersList[qtd].dateOfBirth[1]);
      getchar();
      days[qtd] = days[qtd] + teachersList[qtd].dateOfBirth[1] * 100;
    }

    printf("Ano: ");
    if (type[0] == 'S') {
      scanf("%d", &studentsList[qtd].dateOfBirth[2]);
      getchar();
      days[qtd] = days[qtd] + studentsList[qtd].dateOfBirth[2] * 10000;
    } else {
      scanf("%d", &teachersList[qtd].dateOfBirth[2]);
      getchar();
      days[qtd] = days[qtd] + teachersList[qtd].dateOfBirth[2] * 10000;
    }

    if (type[0] == 'S') {
      studentsList[qtd].date = days[qtd];
      studentsList[qtd].status = 1;
    } else {
      teachersList[qtd].date = days[qtd];
      teachersList[qtd].status = 1;
    }

    printf("CPF: \n");
    fgets(type[0] == 'S' ? studentsList[qtd].cpf : teachersList[qtd].cpf, 15, stdin);

    printf("CADASTRADO COM SUCESSO!\n");
    printf("DESEJA CADASTRAR NOVAMENTE? (DIGITE 0 -> SIM | DIGITE 1-> NÃO)\n");

    while (option != 0 && option != 1) {
      scanf("%d", &option);
      if (option != 0 && option != 1)
        printf("Valor invalido, digite novamente!\n");
      if (option == 0)
        qtd++;
    }
  }

  return 0;
}

void getAll(char type[1]) {
  int index = 0;

  for (index = 0; index < 50; index++) {
    if (type[0] == 'S' && Students[index].status == 1 ||
        type[0] == 'T' && Teachers[index].status == 1) {
      printf("Nome: %s\n",
             type[0] == 'S' ? Students[index].name : Teachers[index].name);

      printf("Sexo: %c\n",
             type[0] == 'S' ? Students[index].sex : Teachers[index].sex);

      printf("Matricula: %d\n", type[0] == 'S' ? Students[index].registration
                                               : Teachers[index].registration);

      printf("Data de Nascimento: %d/%d/%d\n",
             type[0] == 'S' ? Students[index].dateOfBirth[0]
                            : Teachers[index].dateOfBirth[0],
             type[0] == 'S' ? Students[index].dateOfBirth[1]
                            : Teachers[index].dateOfBirth[1],
             type[0] == 'S' ? Students[index].dateOfBirth[2]
                            : Teachers[index].dateOfBirth[2]);

      printf("CPF: %s\n",
             type[0] == 'S' ? Students[index].cpf : Teachers[index].cpf);

      if (type[0] == 'S' && Students[index].status == 1 ||
          type[0] == 'T' && Teachers[index].status == 1) {
        printf("Status: Ativo\n");
      } else
        printf("Status: Inativo\n");
    }
  }
  return;
}

void updatePerson(char type[1], int days[]) {
  int index, op, check = 0, i;

  while (check == 0) {
    int regis;
    printf("Digite a matricula: ");
    scanf("%d", &regis);

    for (i = 0; i < 50; i++) {
      if (type[0] == 'T' && Teachers[i].registration == regis &&
              Teachers[i].status == 1 ||
          type[0] == 'S' && Students[i].registration == regis &&
              Students[i].status == 1) {
        index = i;
        check = 1;
        break;
      } else
        check = 0;
    }
    
    if (check == 0)
      printf("Pessoa não encontrada, digite a matricula novamente!");
  }
  
  int stop = 0;
  while (stop == 0) {
    printf("Escolha uma caracteristica para editar\n");
    printf("1-> Matricula\n");
    printf("2-> Nome\n");
    printf("3-> CPF\n");
    printf("4-> Sexo\n");
    printf("5-> Data de Nascimento\n");
    printf("0-> Sair\n");
    
    scanf("%d", &op);

    switch (op) {
    case 1:
      printf("Digite a nova matricula: \n");
      scanf("%d", type[0] == 'S' ? &Students[index].registration
                                 : &Teachers[index].registration);
      printf("Matricula editada com sucesso: %d\n",
             type[0] == 'S' ? Students[index].registration
                            : Teachers[index].registration);
      break;
    case 2:
      fflush(stdin);
      printf("Digite o novo nome: \n");
      fgets(type[0] == 'S' ? Students[index].name : Teachers[index].name, 50,
            stdin);
      printf("Nome editado com sucesso: %s \n",
             type[0] == 'S' ? Students[index].name : Teachers[index].name);
      break;
    case 3:
      fflush(stdin);
      printf("Digite o novo CPF: \n");
      fgets(type[0] == 'S' ? Students[index].cpf : Teachers[index].cpf, 15,
            stdin);
      printf("CPF editado com sucesso! %s \n",
             type[0] == 'S' ? Students[index].cpf : Teachers[index].cpf);
      break;
    case 4:
      fflush(stdin);
      printf("Digite o novo sexo: \n");
      if (type[0] == 'S') {
        Students[index].sex = getchar();
      } else {
        Teachers[index].sex = getchar();
      }
      printf("Sexo editado com sucesso! %c \n",
             type[0] == 'S' ? Students[index].sex : Teachers[index].sex);
      break;
    case 5:
      printf("Digite a nova data de nascimento: \n");

      printf("Dia:\n ");
      scanf("%d", type[0] == 'S' ? &Students[index].dateOfBirth[0]
                                 : &Teachers[index].dateOfBirth[0]),
          days[index] = type[0] == 'S' ? Students[index].dateOfBirth[0]
                                       : Teachers[index].dateOfBirth[0];

      printf("Mês:\n ");
      scanf("%d", type[0] == 'S' ? &Students[index].dateOfBirth[1]
                                 : &Teachers[index].dateOfBirth[1]);
      if (type[0] == 'S') {
        days[index] = days[index] + Students[index].dateOfBirth[1] * 100;
      } else {
        days[index] = days[index] + Teachers[index].dateOfBirth[1] * 100;
      }

      printf("Ano:\n ");
      scanf("%d", type[0] == 'S' ? &Students[index].dateOfBirth[2]
                                 : &Teachers[index].dateOfBirth[2]);
      getchar();
      if (type[0] == 'S') {
        days[index] = days[index] + Students[index].dateOfBirth[2] * 10000;
      } else {
        days[index] = days[index] + Teachers[index].dateOfBirth[2] * 10000;
      }

      printf("Data de Nascimento editada com sucesso: %d/%d/%d\n",
             type[0] == 'S' ? Students[index].dateOfBirth[0]
                            : Teachers[index].dateOfBirth[0],
             type[0] == 'S' ? Students[index].dateOfBirth[1]
                            : Teachers[index].dateOfBirth[1],
             type[0] == 'S' ? Students[index].dateOfBirth[2]
                            : Teachers[index].dateOfBirth[2]);
      break;
    case 0:
      stop = 1;
      break;
    }
  }
}

void deletePerson(char type[1]) {
  int option = 2;

  while (option != 0) {
    int index = 0, not_found = 1, regis;

    printf("Digite a matricula da pessoa que deseja deletar:\n");
    scanf("%d", &regis);

    for (index = 0; index < 50; index++) {
      if (type[0] == 'T' && Teachers[index].registration == regis &&
              Teachers[index].status == 1 ||
          type[0] == 'S' && Students[index].registration == regis &&
              Students[index].status == 1) {
        if (type[0] == 'S') {
          Students[index].status = 0;
        } else {
          Teachers[index].status = 0;
        }

        not_found = 0;
        printf("Pessoa deletada com sucesso!\n");
        break;
      }
    }

    if (not_found == 1) {
      printf("Matricula não encontrada, digite um valor válido!\n");
      continue;
    } else {
      printf("Digite 0 para sair. Digite 1 para deletar novamente.\n");
      while (option != 0 && option != 1) {
        scanf("%d", &option);
        if (option == 1)
          break;
      }
    }
  }
  return;
}

void listPersonSex(char type[1]) {
  int option = 2;

  while (option != 1) {
    getchar();
    char sex;

    printf("Escolha o sexo(LETRA MAIUSCULA):\n ");
    printf("Masculino -> M | Feminino -> F");
    scanf("%c", &sex);

    if (sex != 'M' && sex != 'F') {
      printf("Digite corretamente!");
      continue;

    } else {
      int i;

      for (i = 0; i < 50; i++) {

        if (type[0] == 'T' && Teachers[i].sex == sex &&
                Teachers[i].status == 1 ||
            type[0] == 'S' && Students[i].sex == sex &&
                Students[i].status == 1) {
          printf("Nome: %s\n",
                 type[0] == 'S' ? Students[i].name : Teachers[i].name);
          printf("Sexo: %c\n",
                 type[0] == 'S' ? Students[i].sex : Teachers[i].sex);
          printf("Matricula: %d\n", type[0] == 'S' ? Students[i].registration
                                                   : Teachers[i].registration);
          printf("Data de Nascimento: %d/%d/%d\n",
                 type[0] == 'S' ? Students[i].dateOfBirth[0]
                                : Teachers[i].dateOfBirth[0],
                 type[0] == 'S' ? Students[i].dateOfBirth[1]
                                : Teachers[i].dateOfBirth[1],
                 type[0] == 'S' ? Students[i].dateOfBirth[2]
                                : Teachers[i].dateOfBirth[2]);
          printf("CPF: %s\n",
                 type[0] == 'S' ? Students[i].cpf : Teachers[i].cpf);
        }
      }
    }

    while (option != 1) {
      printf("Listar novamente? 0 -> SIM | 1 -> NÃO :\n");
      scanf("%d", &option);
      if (option != 1 && option != 0) {
        printf("Digite um valor válido!\n");
        continue;
      } else if (option == 0)
        break;
    }
  }
}

void listPersonDate(char type[1], int days[]) {
  int i, j, valor;

  for (i = 1; i < 50; i++) {
    valor = days[i];
    j = i - 1;

    while (j >= 0 && days[j] > valor) {
      days[j + 1] = days[j];
      j--;
    }
    days[j + 1] = valor;
  }

  int x;
  int z;
  printf("\n>>>LISTADOS POR DATA DE NASCIMENTO<<<\n");
  for (x = 0; x < 50; x++) {
    for (z = 0; z < 50; z++) {
      if (type[0] == 'S' && Students[z].date == days[x] ||
          type[0] == 'T' && Teachers[z].date == days[x])
        printf("%s\n", type[0] == 'S' ? Students[z].name : Teachers[z].name);
    }
  }
}

int compareStrings(const void *a, const void *b) {
  return strcmp(*(const char **)a, *(const char **)b);
}

void listPersonName(char type[1]) {
  char *names[50];
  int i;
  for (i = 0; i < LEN_TEACHER; i++) {
    names[i] = type[0] == 'S' ? Students[i].name : Teachers[i].name;
  }

  int numNames = LEN_TEACHER;

  qsort(names, numNames, sizeof(char *), compareStrings);

  printf("\n<<<ORDEM ALFABÉTICA >>>:\n");
  for (int i = 0; i < numNames; i++) {
    if (names[i] != NULL)
      printf("%s\n", names[i]);
  }
}