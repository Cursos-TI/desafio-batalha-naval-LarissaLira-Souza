#include <stdio.h>
#include <stdbool.h>

#define TAMANHO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5

// Função para verificar se um navio pode ser posicionado em uma direção específica
bool validar_posicao(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int delta_linha, int delta_coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int nova_linha = linha + i * delta_linha;
        int nova_coluna = coluna + i * delta_coluna;

        // Verifica se a posição está fora dos limites ou já ocupada
        if (nova_linha < 0 || nova_linha >= TAMANHO || nova_coluna < 0 || nova_coluna >= TAMANHO ||
            tabuleiro[nova_linha][nova_coluna] != 0) {
            return false;
        }
    }
    return true;
}

// Função para posicionar o navio
void posicionar_navio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int delta_linha, int delta_coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i * delta_linha][coluna + i * delta_coluna] = 3;
    }
}

// Função para exibir o tabuleiro
void exibir_tabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para construir a matriz de habilidade em formato de cone
void construir_cone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (j >= TAMANHO_HABILIDADE / 2 - i && j <= TAMANHO_HABILIDADE / 2 + i) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para construir a matriz de habilidade em formato de cruz
void construir_cruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == TAMANHO_HABILIDADE / 2 || j == TAMANHO_HABILIDADE / 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para construir a matriz de habilidade em formato de octaedro
void construir_octaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (abs(i - TAMANHO_HABILIDADE / 2) + abs(j - TAMANHO_HABILIDADE / 2) <= TAMANHO_HABILIDADE / 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para sobrepor a habilidade no tabuleiro
void aplicar_habilidade(int tabuleiro[TAMANHO][TAMANHO], int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int linha, int coluna) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int nova_linha = linha - TAMANHO_HABILIDADE / 2 + i;
            int nova_coluna = coluna - TAMANHO_HABILIDADE / 2 + j;

            if (nova_linha >= 0 && nova_linha < TAMANHO && nova_coluna >= 0 && nova_coluna < TAMANHO && habilidade[i][j] == 1) {
                tabuleiro[nova_linha][nova_coluna] = 5;
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO] = {0}; // Inicializa o tabuleiro com água

    // Posiciona dois navios horizontais ou verticais
    if (validar_posicao(tabuleiro, 2, 2, 0, 1)) {
        posicionar_navio(tabuleiro, 2, 2, 0, 1);
    }

    if (validar_posicao(tabuleiro, 5, 5, 1, 0)) {
        posicionar_navio(tabuleiro, 5, 5, 1, 0);
    }

    // Posiciona dois navios diagonais
    if (validar_posicao(tabuleiro, 0, 0, 1, 1)) {
        posicionar_navio(tabuleiro, 0, 0, 1, 1);
    }

    if (validar_posicao(tabuleiro, 7, 2, -1, 1)) {
        posicionar_navio(tabuleiro, 7, 2, -1, 1);
    }

    // Construir e aplicar habilidades
    int habilidade_cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidade_cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidade_octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    construir_cone(habilidade_cone);
    construir_cruz(habilidade_cruz);
    construir_octaedro(habilidade_octaedro);

    // Aplicar habilidades no tabuleiro
    aplicar_habilidade(tabuleiro, habilidade_cone, 3, 3);
    aplicar_habilidade(tabuleiro, habilidade_cruz, 6, 6);
    aplicar_habilidade(tabuleiro, habilidade_octaedro, 8, 8);

    // Exibe o tabuleiro final
    exibir_tabuleiro(tabuleiro);

    return 0;
}
