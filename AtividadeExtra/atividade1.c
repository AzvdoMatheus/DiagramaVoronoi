#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void preencheMatriz(int **matriz, int linha, int coluna, int sementes);
void exibeMatriz(int **matriz, int linha, int coluna);

int main(void) {
    srand(time(NULL));
    int coluna, linha;
    int **matriz;
    int sementes;

    printf("Insira as dimensoes da matriz: \n");
    printf("Linhas: ");
    scanf("%i", &linha);
    printf("Colunas: ");
    scanf("%i", &coluna);

    printf("Insira o número de sementes: ");
    scanf("%i", &sementes);

    matriz = malloc(linha * sizeof(int *));
    if (matriz == NULL) {
        printf("Erro na alocacao!\n");
        exit(1);
    }
    for (int i = 0; i < linha; i++) {
        matriz[i] = malloc(coluna * sizeof(int));
        if (matriz[i] == NULL) {
            printf("Erro na alocacao!\n");
            exit(1);
        }
    }

    preencheMatriz(matriz, linha, coluna, sementes);
    exibeMatriz(matriz, linha, coluna);
    
    for (int i = 0; i < linha; i++) {
        free(matriz[i]);
    }
    free(matriz);
    return 0;
}

void preencheMatriz(int **matriz, int linha, int coluna, int sementes) {
    int randomLinha, randomColuna;
    int *sementesUtilizadas = malloc(sementes * sizeof(int)); 
    if (sementesUtilizadas == NULL) {
        printf("Erro na alocacao!\n");
        exit(1);
    }
    for (int i = 0; i < sementes; i++) {
        sementesUtilizadas[i] = 0;
    }
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            matriz[i][j] = 0;
        }
    }

    for (int i = 0; i < sementes; i++) {
        int valorSemente;
        do {
            valorSemente = rand() % 50; 
            int sementeJaUtilizada = 0;
            for (int k = 0; k < sementes; k++) {
                if (valorSemente == sementesUtilizadas[k]) {
                    sementeJaUtilizada = 1;
                    break;
                }
            }
            if (!sementeJaUtilizada) {
                sementesUtilizadas[i] = valorSemente;
                break;
            }
        } while (1);

        do {
            randomLinha = rand() % linha;
            randomColuna = rand() % coluna;
        } while (matriz[randomLinha][randomColuna] != 0);
        matriz[randomLinha][randomColuna] = valorSemente;
    }
    free(sementesUtilizadas);
}

void exibeMatriz(int **matriz, int linha, int coluna) {
    printf("\nMatriz com as sementes:\n\n");
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            if (matriz[i][j] != 0) {
                printf("%d ", matriz[i][j]);
            } else {
                printf("%c ", '.');
            }
        }
        printf("\n");
    }
}
