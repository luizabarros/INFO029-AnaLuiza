#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN_TEACHER 50
#define LEN_STUDENTS 50
#define Len_dis 50
#define LEN_PERSON 50

int qtd_std = 0;
int qtd_tc = 0;

typedef struct Person {
  int registration;
  char name[50];
  char sex;
  int dateOfBirth[3];
  char cpf[15];
  int status;
  int date;
} Person;

typedef struct Teacher {
  int registration;
  char name[50];
  char sex;
  int dateOfBirth[3];
  char cpf[15];
  int status;
  int date;
} Teacher;

typedef struct Disciplina {
  char nome[50];
  int codigo;
  int Active;
  char semestre[7];
  Teacher teacher;
  Person student[LEN_STUDENTS];
} Disciplina;

int days[LEN_TEACHER];
Teacher teachersList[LEN_TEACHER];
Person studentsList[LEN_STUDENTS];

int MenuDis() {

  int opcao = -1;

  printf("\n\n#### Modulo de Disciplinas ####\n\n");

  printf("0 - Voltar para o menu geral\n");
  printf("1 - Adicionar Disciplina\n");
  printf("2 - Excluir Disciplina\n");
  printf("3 - Editar Disciplina\n");
  printf("4 - Listar Disciplinas\n");
  printf("5 - Adicionar Alunos a Disciplina\n");
  printf("6 - Detalhar Disciplina\n");
  printf("7 - Listar Disciplinas com mais de 40 alunos\n");
  printf("8 - Listar Disciplinas sem alunos matriculados\n");
  printf("=> ");
  scanf("%d", &opcao);

  return opcao;
}

int compareStrings(const void *a, const void *b) {
  return strcmp(*(const char **)a, *(const char **)b);
}

void getDataStudent(Disciplina *A, int dis, int *qtd_std, int std) {

  strcpy(A[dis].student[qtd_std[dis]].cpf, studentsList[std].cpf);
  strcpy(A[dis].student[qtd_std[dis]].name, studentsList[std].name);
  strcpy(A[dis].student[qtd_std[dis]].sex, studentsList[std].sex);
  A[dis].student[qtd_std[dis]].dateOfBirth[0] =
      studentsList[std].dateOfBirth[0];
  A[dis].student[qtd_std[dis]].dateOfBirth[1] =
      studentsList[std].dateOfBirth[1];
  A[dis].student[qtd_std[dis]].dateOfBirth[2] =
      studentsList[std].dateOfBirth[2];
}

int AdicionarAluno(Disciplina *A, Person *B, int qtd, int *qtd_std) {
  int cod, back, exist_dis, exist_alu, i;
  back = exist_dis = exist_alu = 0;
  printf("Digite o codigo da disciplina: ");
  scanf("%d", &cod);
  for (i = 0; i < qtd; i++) {
    if (A[i].codigo == cod) {
      exist_dis = 1;
      while (!back) {
        printf("\nDisciplina: %s\n\n", A[i].nome);
        printf("0 - Voltar\n");
        printf("1 - Confirmar\n");
        printf("=> ");
        scanf("%d", &cod);
        switch (cod) {
        case 0:
          back = 1;
          break;
        case 1:
          printf("Digite a matricula do aluno: ");
          scanf("%d", &cod);
          for (int j = 0; j < LEN_STUDENTS; j++) {
            if (B[j].registration == cod) {
              exist_alu = 1;
              A[i].student[qtd_std[i]];
              getDataStudent(A, i, qtd_std, j);
              qtd_std[i]++;
            }
          }
          if (!exist_alu) {
            printf("\nmatricula nao encontrada!\n");
          }
          break;
        default:
          printf("Opcao invalida!\n");
          break;
        }
      }
    }
  }
  if (!exist_dis) {
    printf("\nCodigo da disciplina nao foi encontrado!\n");
  }
}

int VereficarCod(Disciplina *A, int qtd, int codigo) {
  int Usado = 0;
  for (int i = 0; i < qtd; i++) {
    if (A[i].codigo == codigo) {
      Usado = 1;
    }
  }
  if (!Usado) {
    return 1;
  }
  return 0;
}

void Add_subject(Disciplina *A, int qtd) {
  printf("\n#### Adicionar Disciplina ####\n");
  getchar();
  int cod = -1;
  int op = 0;
  printf("\nDigite o nome da disciplina: ");
  fgets(A[qtd].nome, 49, stdin);
  int fim = strlen(A[qtd].nome);
  if (A[qtd].nome[fim - 1] == '\n')
    A[qtd].nome[fim - 1] = '\0';
  while (!op) {
    printf("Digite o codigo da disciplina: ");
    scanf("%d", &cod);
    op = VereficarCod(A, qtd, cod);
    if (op) {
      A[qtd].codigo = cod;
    } else {
      printf("\nCodigo da disciplina ja foi ultilizado!\n\n");
    }
  }
  getchar();
  printf("Digite o semestre da disciplina(AaAa-P): ");
  fgets(A[qtd].semestre, 7, stdin);
  fim = strlen(A[qtd].semestre);
  if (A[qtd].semestre[fim - 1] == '\n')
    A[qtd].semestre[fim - 1] = '\0';

  printf("digite a matricula do professor: ");
  scanf("%d", &A[qtd].teacher.registration);
  int exist = getDataTeacher(A, qtd);
  if (!exist) {
    printf("\nProfessor não encontrado, adicione em *Editar Disciplina* mais "
           "tarde!\n\n");
  }
  A[qtd].Active = 1;
  printf("\nDisciplina Cadastrada com Sucesso!\n");
}

void Remove_subject(Disciplina *A, int qtd) {
  int codigo, i, aux = 0;
  printf("\n#### Remover Disciplina ####\n\n");
  getchar();
  printf("Digite o codigo da disciplina: ");
  scanf("%d", &codigo);
  getchar();
  for (i = 0; i < qtd; i++) {
    if (A[i].codigo == codigo && A[i].Active) {
      A[i].Active = 0;
      printf("\nDisciplina Removida com Sucesso!");
      aux = 1;
      break;
    }
  }
  if (!aux)
    printf("\nCodigo digitado nao existe!");
}

void Edit_subject(Disciplina *A, int qtd) {
  int codigo, i, vet = -1;
  printf("\n#### Editar Disciplina ####\n\n");
  getchar();
  printf("Digite o codigo da disciplina que deseja editar: ");
  scanf("%d", &codigo);
  getchar();
  for (i = 0; i < qtd; i++) {
    if (A[i].codigo == codigo) {
      vet = i;
      break;
    }
  }
  if (A[vet].Active && vet != -1) {
    int op, fim, cod, back = 0;
    int codOp = 0;
    while (!back) {

      printf("\nDisciplina - %s\n\n", A[i].nome);
      printf("O que deseja editar?\n");
      printf("O - Voltar\n");
      printf("1 - Nome\n");
      printf("2 - Codigo\n");
      printf("3 - Semestre\n");
      printf("4 - Professor\n");
      scanf("%d", &op);
      getchar();
      switch (op) {
      case 0:
        back = 1;
        break;
      case 1:
        printf("Digite o novo nome da disciplina: ");
        fgets(A[vet].nome, 49, stdin);
        fim = strlen(A[vet].nome);
        if (A[i].nome[fim - 1] == '\n')
          A[i].nome[fim - 1] = '\0';
        printf("\nDisciplina editada com Sucesso!");
        back = 1;
        break;
      case 2:
        while (!op)
          printf("Digite o codigo da disciplina: ");
        scanf("%d", &cod);
        op = VereficarCod(A, qtd, cod);
        if (op) {
          A[qtd].codigo = cod;
        }
        printf("\nDisciplina editada com Sucesso!");
        back = 1;
        break;
      case 3:
        printf("Digite o novo semestre da disciplina: ");
        fgets(A[vet].semestre, 7, stdin);
        fim = strlen(A[vet].semestre);
        if (A[qtd].semestre[fim - 1] == '\n')
          A[qtd].semestre[fim - 1] = '\0';
        printf("\nDisciplina editada com Sucesso!");
        back = 1;
        break;
      case 4:
        printf("digite a matricula do novo professor: ");
        scanf("%d", &A[qtd].teacher.registration);
        int exist = getDataTeacher(A, qtd);
        if (!exist) {
          printf("\nProfessor não encontrado, adicione em *Editar Disciplina* "
                 "mais tarde!\n");
        } else {
        }
        printf("\nDisciplina editada com Sucesso!");
        back = 1;
        break;
      default:
        printf("Opção invalida!");
        break;
      }
    }
  } else {
    printf("Codigo nao encontrado!");
  }
}

void List_subject(Disciplina *A, int qtd) {
  int dis = 1;
  for (int i = 0; i < qtd; i++) {
    if (A[i].Active) {
      printf("\nDisciplina #%d\n\n", dis);
      printf("Nome: %s\n", A[i].nome);
      printf("Codigo: %d\n", A[i].codigo);
      printf("Semestre: %s\n", A[i].semestre);
      printf("Nome do professor: %s\n\n", A[i].teacher.name);
      dis++;
    }
  }
  if (dis == 1) {
    printf("\nAinda sem disciplinas regisitradas");
  }
}

void DetalharDisciplina(Disciplina *A, int qtd, int *qtd_std) {
  int cod, exist = 0;
  printf("\nDigite o codigo da disciplina: ");
  scanf("%d", &cod);
  getchar();
  for (int i = 0; i < qtd; i++) {
    if (A[i].codigo == cod) {
      exist = 1;
      printf("Disciplina: %s\n", A[i].nome);
      printf("Professor: %s\n", A[i].teacher.name);
      printf("\nAlunos:\n");
      for (int j = 0; j < qtd_std[i]; j++) {
        printf("%d - %s\n", j + 1, A[i].student[j].name);
      }
      if (qtd_std[i] == 0) {
        printf("Disciplina sem alunos matriculados!");
      }
    }
  }
  if (!exist) {
    printf("Codigo da disciplina não encontrado!");
  }
}

void Sobrecarregadas(Disciplina *A, int qtd, int *qtd_std) {
  int exist = 0;
  for (int i = 0; i < qtd; i++) {
    if (qtd_std[i] > 40) {
      exist = 1;
      printf("\nA disciplina %s tem mais de 40 alunos matriculados!\n",
             A[i].nome);
    }
  }
  if (!exist) {
    printf("\nNão tem disciplinas com mais de 40 alunos\n");
  }
}

void SemAlunos(Disciplina *A, int qtd, int *qtd_std) {
  int exist = 0;
  for (int i = 0; i < qtd; i++) {
    if (qtd_std[i] == 0) {
      exist = 1;
      printf("\nA disciplina %s não tem alunos matriculados!\n", A[i].nome);
    }
  }
  if (!exist) {
    printf("\nNão tem disciplinas sem alunos\n");
  }
}

void modelSubject(void) {
  Disciplina *subject = calloc(Len_dis, sizeof(Disciplina));
  int optionDis;
  int *qtd_alu = calloc(Len_dis, sizeof(int));
  int SairDis = 0;
  int qtd_Dis = 0;
  while (!SairDis) {
    optionDis = MenuDis();
    switch (optionDis) {
    case 0:
      SairDis = 1;
      break;
    case 1:
      Add_subject(subject, qtd_Dis);
      qtd_Dis++;
      break;
    case 2:
      Remove_subject(subject, qtd_Dis);
      break;
    case 3:
      Edit_subject(subject, qtd_Dis);
      break;
    case 4:
      List_subject(subject, qtd_Dis);
      break;
    case 5:
      AdicionarAluno(subject, studentsList, qtd_Dis, qtd_alu);
      break;
    case 6:
      DetalharDisciplina(subject, qtd_Dis, qtd_alu);
      break;
    case 7:
      Sobrecarregadas(subject, qtd_Dis, qtd_alu);
      break;
    case 8:
      SemAlunos(subject, qtd_Dis, qtd_alu);
      break;
    default:
      printf("Opcao invalida!\n");
      break;
    }
  }
}

void searchPerson(Teacher *vetor1, Person *vetor2) {
  int x, y, tam, auxN, auxP, verify, qtd, option, loop = 0;
  char namePerson[LEN_PERSON];
  while (loop == 0) {
    qtd = 0;
    fflush(stdin);
    setbuf(stdin, 0);
    printf("\nDigite o nome da pessoa que deseja buscar:\n");
    fgets(namePerson, 50, stdin);
    tam = strlen(namePerson) - 1;
    for (x = 0; x < 50; x++) {
      y = 0;
      while (y < LEN_PERSON) {
        if (vetor1[x].name[y] == namePerson[0]) {
          auxN = y;
          auxP = 0;
          verify = 0;
          while (vetor1[x].name[auxN] == namePerson[auxP] && verify < tam) {
            verify++;
            auxN++;
            auxP++;
          }
        }
        y++;
      }
      if (verify == tam) {
        printf("%s\n", vetor1[x].name);
        qtd++;
      }
      verify = 0;
      y = 0;
      while (y < LEN_PERSON) {
        if (vetor2[x].name[y] == namePerson[0]) {
          auxN = y;
          auxP = 0;
          verify = 0;
          while (vetor2[x].name[auxN] == namePerson[auxP] && verify < tam) {
            verify++;
            auxN++;
            auxP++;
          }
        }
        y++;
      }
      if (verify == tam) {
        printf("%s\n", vetor2[x].name);
        qtd++;
      }
    }
    if (qtd == 0) {
      printf("Resultado não encontrado\n");
    }

    printf("Deseja buscar outra pessoa?\n");
    printf("0 - Sim\n");
    printf("1 - Não\n");
    scanf("%d", &option);

    switch (option) {
    case 0:
      break;
    case 1:
      loop = 1;
      break;
    }
  }
}

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
  scanf("%d", &option);

  return option;
}

int getDataTeacher(Disciplina *A, int qtd) {
  int x = 0;

  for (x = 0; x < LEN_TEACHER; x++) {
    if (teachersList[x].registration == A[qtd].teacher.registration) {
      strcpy(A[qtd].teacher.cpf, teachersList[x].cpf);
      strcpy(A[qtd].teacher.name, teachersList[x].name);
      A[qtd].teacher.sex = teachersList[x].sex;
      A[qtd].teacher.dateOfBirth[0] = teachersList[x].dateOfBirth[0];
      A[qtd].teacher.dateOfBirth[1] = teachersList[x].dateOfBirth[1];
      A[qtd].teacher.dateOfBirth[2] = teachersList[x].dateOfBirth[2];
      return 1;
    }
  }
  return 0;
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
    fgets(type[0] == 'S' ? studentsList[qtd].name : teachersList[qtd].name, 50,
          stdin);

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
    fgets(type[0] == 'S' ? studentsList[qtd].cpf : teachersList[qtd].cpf, 15,
          stdin);

    printf("CADASTRADO COM SUCESSO!\n");
    printf("DESEJA CADASTRAR NOVAMENTE? (DIGITE 0 -> SIM | DIGITE 1-> NÃO)\n");

    scanf("%d", &option);
    if (option != 0 && option != 1) {
      while (option != 0 && option != 1) {
        printf("Valor invalido, digite novamente!\n");
        scanf("%d", &option);

        if (option == 0) {
          type[0] == 'S' ? qtd_std++ : qtd_tc++;
          break;
        } else if (option == 1) {
          break;
        }
      }
    }
  }

  return 0;
}

void getAll(char type[1]) {
  int index = 0;

  for (index = 0; index < 50; index++) {
    if (type[0] == 'S' && studentsList[index].status == 1 ||
        type[0] == 'T' && teachersList[index].status == 1) {
      printf("Nome: %s\n", type[0] == 'S' ? studentsList[index].name
                                          : teachersList[index].name);

      printf("Sexo: %c\n", type[0] == 'S' ? studentsList[index].sex
                                          : teachersList[index].sex);

      printf("Matricula: %d\n", type[0] == 'S'
                                    ? studentsList[index].registration
                                    : teachersList[index].registration);

      printf("Data de Nascimento: %d/%d/%d\n",
             type[0] == 'S' ? studentsList[index].dateOfBirth[0]
                            : teachersList[index].dateOfBirth[0],
             type[0] == 'S' ? studentsList[index].dateOfBirth[1]
                            : teachersList[index].dateOfBirth[1],
             type[0] == 'S' ? studentsList[index].dateOfBirth[2]
                            : teachersList[index].dateOfBirth[2]);

      printf("CPF: %s\n", type[0] == 'S' ? studentsList[index].cpf
                                         : teachersList[index].cpf);

      if (type[0] == 'S' && studentsList[index].status == 1 ||
          type[0] == 'T' && teachersList[index].status == 1) {
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
      if (type[0] == 'T' && teachersList[i].registration == regis &&
              teachersList[i].status == 1 ||
          type[0] == 'S' && studentsList[i].registration == regis &&
              studentsList[i].status == 1) {
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
      scanf("%d", type[0] == 'S' ? &studentsList[index].registration
                                 : &teachersList[index].registration);
      printf("Matricula editada com sucesso: %d\n",
             type[0] == 'S' ? studentsList[index].registration
                            : teachersList[index].registration);
      break;
    case 2:
      fflush(stdin);
      printf("Digite o novo nome: \n");
      fgets(type[0] == 'S' ? studentsList[index].name
                           : teachersList[index].name,
            50, stdin);
      printf("Nome editado com sucesso: %s \n", type[0] == 'S'
                                                    ? studentsList[index].name
                                                    : teachersList[index].name);
      break;
    case 3:
      fflush(stdin);
      printf("Digite o novo CPF: \n");
      fgets(type[0] == 'S' ? studentsList[index].cpf : teachersList[index].cpf,
            15, stdin);
      printf("CPF editado com sucesso! %s \n", type[0] == 'S'
                                                   ? studentsList[index].cpf
                                                   : teachersList[index].cpf);
      break;
    case 4:
      fflush(stdin);
      printf("Digite o novo sexo: \n");
      if (type[0] == 'S') {
        studentsList[index].sex = getchar();
      } else {
        teachersList[index].sex = getchar();
      }
      printf("Sexo editado com sucesso! %c \n", type[0] == 'S'
                                                    ? studentsList[index].sex
                                                    : teachersList[index].sex);
      break;
    case 5:
      printf("Digite a nova data de nascimento: \n");

      printf("Dia:\n ");
      scanf("%d", type[0] == 'S' ? &studentsList[index].dateOfBirth[0]
                                 : &teachersList[index].dateOfBirth[0]),
          days[index] = type[0] == 'S' ? studentsList[index].dateOfBirth[0]
                                       : teachersList[index].dateOfBirth[0];

      printf("Mês:\n ");
      scanf("%d", type[0] == 'S' ? &studentsList[index].dateOfBirth[1]
                                 : &teachersList[index].dateOfBirth[1]);
      if (type[0] == 'S') {
        days[index] = days[index] + studentsList[index].dateOfBirth[1] * 100;
      } else {
        days[index] = days[index] + teachersList[index].dateOfBirth[1] * 100;
      }

      printf("Ano:\n ");
      scanf("%d", type[0] == 'S' ? &studentsList[index].dateOfBirth[2]
                                 : &teachersList[index].dateOfBirth[2]);
      getchar();
      if (type[0] == 'S') {
        days[index] = days[index] + studentsList[index].dateOfBirth[2] * 10000;
      } else {
        days[index] = days[index] + teachersList[index].dateOfBirth[2] * 10000;
      }

      printf("Data de Nascimento editada com sucesso: %d/%d/%d\n",
             type[0] == 'S' ? studentsList[index].dateOfBirth[0]
                            : teachersList[index].dateOfBirth[0],
             type[0] == 'S' ? studentsList[index].dateOfBirth[1]
                            : teachersList[index].dateOfBirth[1],
             type[0] == 'S' ? studentsList[index].dateOfBirth[2]
                            : teachersList[index].dateOfBirth[2]);
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
      if (type[0] == 'T' && teachersList[index].registration == regis &&
              teachersList[index].status == 1 ||
          type[0] == 'S' && studentsList[index].registration == regis &&
              studentsList[index].status == 1) {
        if (type[0] == 'S') {
          studentsList[index].status = 0;
        } else {
          teachersList[index].status = 0;
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

        if (type[0] == 'T' && teachersList[i].sex == sex &&
                teachersList[i].status == 1 ||
            type[0] == 'S' && studentsList[i].sex == sex &&
                studentsList[i].status == 1) {
          printf("Nome: %s\n",
                 type[0] == 'S' ? studentsList[i].name : teachersList[i].name);
          printf("Sexo: %c\n",
                 type[0] == 'S' ? studentsList[i].sex : teachersList[i].sex);
          printf("Matricula: %d\n", type[0] == 'S'
                                        ? studentsList[i].registration
                                        : teachersList[i].registration);
          printf("Data de Nascimento: %d/%d/%d\n",
                 type[0] == 'S' ? studentsList[i].dateOfBirth[0]
                                : teachersList[i].dateOfBirth[0],
                 type[0] == 'S' ? studentsList[i].dateOfBirth[1]
                                : teachersList[i].dateOfBirth[1],
                 type[0] == 'S' ? studentsList[i].dateOfBirth[2]
                                : teachersList[i].dateOfBirth[2]);
          printf("CPF: %s\n",
                 type[0] == 'S' ? studentsList[i].cpf : teachersList[i].cpf);
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
      if (type[0] == 'S' && studentsList[z].date == days[x] ||
          type[0] == 'T' && teachersList[z].date == days[x])
        printf("%s\n",
               type[0] == 'S' ? studentsList[z].name : teachersList[z].name);
    }
  }
}

void listPersonName(char type[1]) {
  char *names[50];
  int i;
  for (i = 0; i < LEN_TEACHER; i++) {
    names[i] = type[0] == 'S' ? studentsList[i].name : teachersList[i].name;
  }

  int numNames = LEN_TEACHER;

  qsort(names, numNames, sizeof(char *), compareStrings);

  printf("\n<<<ORDEM ALFABÉTICA >>>:\n");
  for (int i = 0; i < numNames; i++) {
    if (names[i] != NULL)
      printf("%s\n", names[i]);
  }
}

void students() {
  int option = -1, createdPerson = 0, days[50];

  option = menu("alunos");

  switch (option) {
  case 0:
    printf("Sistema encerrado.\n");
    break;
  case 1:
    createPerson("S", qtd_std, days);
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

void teachers() {
  int opcao2 = -1;

  opcao2 = menu("professor");

  switch (opcao2) {
  case 0:
    printf("Sistema encerrado.\n");
    break;
  case 1:
    createPerson("T", qtd_tc, days);
    break;
  case 2:
    updatePerson("T", days);
    break;
  case 3:
    deletePerson("T");
    break;
  case 4:
    getAll("T");
    break;
  case 5:
    listPersonSex("T");
    break;
  case 6:
    listPersonDate("T", days);
    break;
  case 7:
    listPersonName("T");
    break;
  default:
    printf("Opção inválida! Digite novamente.\n");
    break;
  }
}

int mainMenu() {
  int option;
  printf("BEM VINDO AO SISTEMA!\n");
  printf("0 - Sair\n");
  printf("1 - Administrar alunos\n");
  printf("2 - Administrar professores\n");
  printf("3 - Administrar disciplinas\n");
  printf("4 - Buscar pessoas\n");
  printf("Digite sua opção:\n");

  scanf("%d", &option);

  return option;
}

int main() {
  int option = -1, logout = 0;

  while (!logout) {
    option = mainMenu();
    switch (option) {
    case 0:
      printf("SISTEMA ENCERRADO!\n");
      logout = 1;
      break;
    case 1:
      students();
      break;
    case 2:
      teachers();
      break;
    case 3:
      modelSubject();
      break;
    case 4:
      searchPerson(teachersList, studentsList);
    default:
      printf("Opção inválida! Digite novamente.\n");
    }
  }
  return 0;
}