#include <stdio.h>

int main(void) {
  int num, idades[10], soma = 0;
  
  for (num = 0; num < 10; num++) {
    printf("Digite o numero %d", num + 1);
    scanf("%d", &idades[num]);
    soma += idades[num];
  }

  for (num = 0; num < 10; num++) {
    if (idades[num] > (soma / 10)) {
      printf("%d \n", idades[num]);
    }
  }
}