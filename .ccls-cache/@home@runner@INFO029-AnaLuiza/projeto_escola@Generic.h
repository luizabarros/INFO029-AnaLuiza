#ifndef GENERIC_H
#define GENERIC_H
#include <stdio.h>
#include <string.h>

typedef struct Person {
  int registration;
  char name[50];
  char sex;
  int dateOfBirth[3];
  char cpf[15];
  int status;
  int date;
} Person;

int menu(char topic[]);
int createPerson(char type[1], int qtd, int days[]);
void getAll(char type[1]);
void updatePerson(char type[1], int days[]);
void deletePerson(char type[1]);
void listPersonSex(char type[1]);
void listPersonName(char type[1]);
void listPersonDate(char type[1], int days[]);
int compareStrings(const void *a, const void *b);

#endif