#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000 //valor maximo de um elemento do vetor
int fator=1;

// Função para gerar um vetor de números aleatórios
void gerar_vetor(float* vetor, int n) {
    for (int i = 0; i < n; i++) {
        vetor[i] = (rand() % MAX )/ RAND_MAX * fator;  // Gera números fracionários
        fator*=-1;
    }
}

// Função para calcular o produto interno de dois vetores
double calcular_produto_interno(float* vetor1, float* vetor2, int n) {
    double produto_interno = 0.0;
    for (int i = 0; i < n; i++) {
        produto_interno += vetor1[i] * vetor2[i];
    }
    return produto_interno;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Uso: %s <N> <arquivo_saida>\n", argv[0]);
        return -1;
    }

    int N = atoi(argv[1]);
    char* arq = argv[2];

    // Alocar memória para os vetores
    float* vetor1 = (float*)malloc(N * sizeof(float));
    float* vetor2 = (float*)malloc(N * sizeof(float));
    if (vetor1 == NULL || vetor2 == NULL) {
        printf("Erro ao alocar memória para os vetores.\n");
        return -1;
    }

    // Inicializar gerador de números aleatórios
    srand(time(NULL));

    // Gerar os vetores de entrada
    gerar_vetor(vetor1, N);
    gerar_vetor(vetor2, N);

    // Calcular o produto interno
    double produto_interno = calcular_produto_interno(vetor1, vetor2, N);

    // Escrever os dados no arquivo binário
    FILE* arquivo = fopen(arq, "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        free(vetor1);
        free(vetor2);
        return -1;
    }

    fwrite(&N, sizeof(int), 1, arquivo);                  // Escreve o valor de N
    fwrite(vetor1, sizeof(float), N, arquivo);            // Escreve o primeiro vetor
    fwrite(vetor2, sizeof(float), N, arquivo);            // Escreve o segundo vetor
    fwrite(&produto_interno, sizeof(double), 1, arquivo); // Escreve o produto interno

    // Fechar o arquivo e liberar memória
    fclose(arquivo);
    free(vetor1);
    free(vetor2);

    printf("Arquivo binário '%s' gerado com sucesso.\n", arq);

    return 0;
}
