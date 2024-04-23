#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> 

// calcular distancia = raiz de (x2 - x1)ˆ2 + (y2 - y1)ˆ2

int main(void) {

  int coluna, linha;
  int **matriz;
  int sementes;
  int randomLinha, randomColuna;

  printf("Insira as dimensoes da matriz: \n");
  printf("Linhas: ");
  scanf("%i", &linha); 
  printf("Colunas :");
  scanf("%i", &coluna); 

  printf("Insira numero de sementes: ");
  scanf("%i", &sementes); 

  matriz = malloc(linha * sizeof(int *));

  if (matriz == NULL) {
    printf("Erro na alocacao!\n");
    exit(1);
  }

  for(int i = 0; i < linha; i++) {
    matriz[i] = malloc(coluna * sizeof(int)); 
  }

  srand(time(NULL));

  for(int i = 0; i < linha; i++) {
    for(int j = 0; j < coluna; j++) {
      matriz[i][j] = 0;
    }
  }

  for(int i = 0; i < sementes; i++) {
    do {
      randomLinha = rand() % linha;
      randomColuna = rand() % coluna;
    } while (matriz[randomLinha][randomColuna] != 0); 

    matriz[randomLinha][randomColuna] = i + 1; 
  }

  printf("\nMatriz com as sementes:\n\n");
  for(int i = 0; i < linha; i++) {
    for (int j = 0; j < coluna; j++) {
      printf("%3d ", matriz[i][j]);
    }
    printf("\n");
  }

  for(int i = 0; i < linha; i++) {
    free(matriz[i]);
  }
  free(matriz);

  return 0;
}
