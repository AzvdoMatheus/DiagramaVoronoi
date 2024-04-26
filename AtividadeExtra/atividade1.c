#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double distanciaEuclidiana(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void preencheMatriz(int **matriz, int linha, int coluna, int sementes);
void exibeMatriz(int **matriz, int linha, int coluna);
void calculaVoronoi(int **matriz, int linha, int coluna, int sementes, int **posicoesSementes);

int main(void) {
    srand(time(NULL));
    int coluna, linha, sementes;
    int **matriz, **posicoesSementes;

    printf("Insira as dimensoes da matriz: \n");
    printf("Linhas: ");
    scanf("%i", &linha);
    printf("Colunas: ");
    scanf("%i", &coluna);

    printf("Insira o número de sementes: ");
    scanf("%i", &sementes);

    matriz = malloc(linha * sizeof(int *));
    posicoesSementes = malloc(sementes * sizeof(int *));
    if (matriz == NULL || posicoesSementes == NULL) {
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
    for (int i = 0; i < sementes; i++) {
        posicoesSementes[i] = malloc(2 * sizeof(int));
        if (posicoesSementes[i] == NULL) {
            printf("Erro na alocacao!\n");
            exit(1);
        }
    }

    preencheMatriz(matriz, linha, coluna, sementes);
    exibeMatriz(matriz, linha, coluna);
    calculaVoronoi(matriz, linha, coluna, sementes, posicoesSementes);
    exibeMatriz(matriz, linha, coluna);

    for (int i = 0; i < linha; i++) {
        free(matriz[i]);
    }
    free(matriz);
    for (int i = 0; i < sementes; i++) {
        free(posicoesSementes[i]);
    }
    free(posicoesSementes);
    return 0;
}

void preencheMatriz(int **matriz, int linha, int coluna, int sementes) {
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            matriz[i][j] = -1; 
        }
    }

    for (int i = 0; i < sementes; i++) {
        int randomLinha, randomColuna, valorSemente = i; 
        do {
            randomLinha = rand() % linha;
            randomColuna = rand() % coluna;
        } while (matriz[randomLinha][randomColuna] != -1);
        matriz[randomLinha][randomColuna] = valorSemente;
    }
}

void exibeMatriz(int **matriz, int linha, int coluna) {
    printf("\nDiagrama de Voronoi:\n\n");
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            if (matriz[i][j] != -1) {
                printf("%2d ", matriz[i][j]);
            } else {
                printf("%2c ", '.');
            }
        }
        printf("\n");
    }
}

void calculaVoronoi(int **matriz, int linha, int coluna, int sementes, int **posicoesSementes) {
    int semente = 0;
    for (int i = 0; i < linha && semente < sementes; i++) {
        for (int j = 0; j < coluna && semente < sementes; j++) {
            if (matriz[i][j] != -1) {
                posicoesSementes[semente][0] = i;
                posicoesSementes[semente][1] = j;
                semente++;
            }
        }
    }

    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            if (matriz[i][j] == -1) { 
                double menorDistancia = INFINITY;
                int SementeMaisProxima;
                for (int k = 0; k < sementes; k++) {
                    double dist = distanciaEuclidiana(i, j, posicoesSementes[k][0], posicoesSementes[k][1]);
                    if (dist < menorDistancia) {
                        menorDistancia = dist;
                        SementeMaisProxima = matriz[posicoesSementes[k][0]][posicoesSementes[k][1]];
                    }
                }
                matriz[i][j] = SementeMaisProxima;
            }
        }
    }
}
