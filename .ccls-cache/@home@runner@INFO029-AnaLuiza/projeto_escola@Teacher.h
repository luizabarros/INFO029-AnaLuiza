#ifndef TEACHER_H
#define TEACHER_H
#include "Generic.h"
#include "Subject.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN_TEACHER 50

typedef struct Teacher {
  int registration;
  char name[50];
  char sex;
  int dateOfBirth[3];
  char cpf[15];
  int status;
} Teacher;

Person Teachers[LEN_TEACHER];
void getTeacher();
void app();
void deleteTeacher();
void changeTeacher();
void teachers();
int menu(char topic[]);
void registerTeacher();
void ListTeachersName();
void ListTeacherSex();
void ListTeachersDate();

#endif