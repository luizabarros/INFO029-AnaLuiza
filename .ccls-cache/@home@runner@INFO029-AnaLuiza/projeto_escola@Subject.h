#ifndef SUBJECT_H
#define SUBJECT_H
#define Len_dis 50
#include <stdio.h>
#include <string.h>
#include "Student.h"

typedef struct {
  char nome[50];
  int codigo;
  int Active;
  char semestre[7];
  Person teacher;
  Person student[Len_dis];
} Disciplina;

void menuSubject();

void Add_subject(Disciplina *A, int qtd);

void Remove_subject(Disciplina *A, int qtd);

void Edit_subject(Disciplina *A, int qtd);

void List_subject(Disciplina *A, int qtd);

int getDataTeacher(Disciplina *A, int qtd);

#endif