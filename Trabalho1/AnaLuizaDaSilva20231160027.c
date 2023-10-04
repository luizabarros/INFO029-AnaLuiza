// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do
//  trabalho

//  ----- Dados do Aluno -----
//  Nome: Ana Luiza dos Santos Barros da Silva
//  email: thecoderana@gmail.com
//  Matrícula: 20231160027
//  Semestre: 2023.2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include "AnaLuizaDaSilva20231160027.h" // Substitua pelo seu arquivo de header renomeado
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y) {
  int soma;
  soma = x + y;
  return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x) { // função utilizada para testes
  int i, fat = 1;

  for (i = x; i > 1; i--)
    fat = fat * i;

  return fat;
}

int teste(int a) {
  int val;
  if (a == 2)
    val = 3;
  else
    val = 4;

  return val;
}

int isBissexto(int year) {
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

DiasMesesAnos CalcularDiferencaDatas(int dia1, int mes1, int ano1, int dia2,
                                     int mes2, int ano2,
                                     DiasMesesAnos Resultado) {
  int DiasNoMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  if (isBissexto(ano2)) {
    DiasNoMes[2] = 29;
  }

  int DiferencaAnos = ano2 - ano1;
  int DiferencaMeses = mes2 - mes1;
  int DiferencaDias = dia2 - dia1;

  if (DiferencaDias < 0) {
    DiferencaMeses--;
    DiferencaDias += DiasNoMes[mes1];
  }

  if (DiferencaMeses < 0) {
    DiferencaAnos--;
    DiferencaMeses += 12;
  }

  if (ano1 > ano2 || (ano1 == ano2 && mes1 > mes2) ||
      (ano1 == ano2 && mes1 == mes2 && dia1 > dia2)) {
    Resultado.retorno = 4;
  } else {
    Resultado.retorno = 1;
  }

  Resultado.qtdAnos = DiferencaAnos;
  Resultado.qtdDias = DiferencaDias;
  Resultado.qtdMeses = DiferencaMeses;

  return Resultado;
}

DataQuebrada quebraData(char data[]) {
  DataQuebrada dq;
  char sDia[3];
  char sMes[3];
  char sAno[5];
  int i;

  for (i = 0; data[i] != '/'; i++) {
    sDia[i] = data[i];
  }
  if (i == 1 || i == 2) { // testa se tem 1 ou dois digitos
    sDia[i] = '\0';       // coloca o barra zero no final
  } else {
    dq.valido = 0;
    return dq;
  }

  int j = i + 1; // anda 1 cada para pular a barra
  i = 0;

  for (; data[j] != '/'; j++) {
    sMes[i] = data[j];
    i++;
  }

  if (i == 1 || i == 2) { // testa se tem 1 ou dois digitos
    sMes[i] = '\0';       // coloca o barra zero no final
  } else {
    dq.valido = 0;
    return dq;
  }

  j = j + 1; // anda 1 cada para pular a barra
  i = 0;

  for (; data[j] != '\0'; j++) {
    sAno[i] = data[j];
    i++;
  }

  if (i == 2 || i == 4) { // testa se tem 2 ou 4 digitos
    sAno[i] = '\0';       // coloca o barra zero no final
  } else {
    dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno);

  dq.valido = 1;

  return dq;
}
/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia,
mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa
podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[]) {
  DataQuebrada dataquebrada = quebraData(data);

  if (dataquebrada.valido == 1) {
    if (dataquebrada.iDia > 31 || dataquebrada.iDia < 1) {
      return 0;
    }

    if (dataquebrada.iMes > 12 || dataquebrada.iMes < 1) {
      return 0;
    }

    int bissexto = 0;

    if ((dataquebrada.iAno % 4 == 0 && dataquebrada.iAno % 100 != 0) ||
        (dataquebrada.iAno % 400 == 0)) {
      bissexto = 1;
    }

    if (bissexto == 1 && dataquebrada.iMes == 2 &&
        (dataquebrada.iDia == 29 || dataquebrada.iDia == 29)) {
      return 1;
    } else if (dataquebrada.iMes == 2 && (dataquebrada.iDia > 28)) {
      return 0;
    } else {
      return 1;
    }
  } else {
    return 0;
  }
}

/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal.
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis
 valores abaixo 1 -> cálculo de diferença realizado com sucesso 2 -> datainicial
 inválida 3 -> datafinal inválida 4 -> datainicial > datafinal Caso o cálculo
 esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos
 com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[]) {
  DiasMesesAnos valorFinal;
  int isValida = q1(datainicial);
  int isValidaFinal = q1(datafinal);

  switch (isValida) {
  case 0:
    valorFinal.retorno = 2;
    valorFinal.qtdAnos = 0;
    valorFinal.qtdDias = 0;
    valorFinal.qtdMeses = 0;
    break;

  case 1:

    if (isValidaFinal == 0) {
      valorFinal.retorno = 3;
      valorFinal.qtdAnos = 0;
      valorFinal.qtdDias = 0;
      valorFinal.qtdMeses = 0;
    } else {
      DataQuebrada d1 = quebraData(datainicial);
      DataQuebrada d2 = quebraData(datafinal);
      valorFinal = CalcularDiferencaDatas(d1.iDia, d1.iMes, d1.iAno, d2.iDia,
                                          d2.iMes, d2.iAno, valorFinal);
    }
    break;
  }
  return valorFinal;
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa
 Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar
 diferenças entre maiúsculos e minúsculos. Se isCaseSensitive != 1, a pesquisa
 não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive) {
  int i = 0, qtdOcorrencias = 0;
  while (texto[i] != '\0') {

    if (isCaseSensitive == 1) {
      if (c == texto[i]) {
        qtdOcorrencias++;
      }
    } else {
      if (tolower(c) == tolower(texto[i])) {
        qtdOcorrencias++;
      }
    }

    i++;
  }
  return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros
 (posicoes) que irá guardar as posições de início e fim de cada ocorrência da
 palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída
 correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do
 vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve
 ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a
 segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente.
 Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como
 há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da
 seguinte forma: posicoes[0] = 13; posicoes[1] = 16; Observe que o índice da
 posição no texto deve começar ser contado a partir de 1. O retorno da função,
 n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[]) {
  int tamanhoTexto = strlen(strTexto);
  int tamanhoBusca = strlen(strBusca);
  int qtdOcorrencias = 0;

  for (int i = 0; i <= tamanhoTexto - tamanhoBusca; i++) {
    int j;

    for (j = 0; j < tamanhoBusca; j++) {
      if (strTexto[i + j] != strBusca[j]) {
        break;
      }
    }

    if (j == tamanhoBusca) {
      int posicaoInicial = i + 1;
      int posicaoFinal = i + tamanhoBusca;

      posicoes[qtdOcorrencias * 2] = posicaoInicial;
      posicoes[qtdOcorrencias * 2 + 1] = posicaoFinal;

      qtdOcorrencias++;
      i += tamanhoBusca - 1;
    }
  }
  return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num) {
  int reversed = 0;

  while (num != 0) {
    int digito = num % 10;
    reversed = reversed * 10 + digito;
    num = num / 10;
  }

  return reversed;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca) {
  int qtdOcorrencias = 0;
  long long div, i, subDiv, buscarCasa, num;

  buscarCasa = 10;

  while (numerobusca / buscarCasa != 0) {
    buscarCasa *= 10;
  }

  div = 10;
  while (numerobase / div != 0) {
    div *= 10;
  }

  subDiv = div / buscarCasa;

  for (i = div; subDiv > 0; i /= 10) {
    num = (numerobase % i) / subDiv;

    if (num == numerobusca) {
      qtdOcorrencias++;
      i = i / buscarCasa * 10;
      subDiv = subDiv / buscarCasa * 10;
    }

    subDiv /= 10;
  }

  return qtdOcorrencias;
}