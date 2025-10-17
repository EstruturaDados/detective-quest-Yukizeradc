#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_MAXIMO 5

// Struct para representar uma peca
typedef struct {
    char nome; // 'I', 'O', 'T', 'L'
    int id;    // identificador unico
} Peca;

// Fila circular
Peca fila[TAMANHO_MAXIMO];
int inicio = 0;
int fim = 0;
int quantidade = 0;
int proximoId = 0; // usado para gerar ids unicos

// Gera uma peca nova automaticamente
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4]; // escolhe aleatorio entre os tipos
    nova.id = proximoId++;
    return nova;
}

// Insere uma peca no final da fila
void enfileirar() {
    if (quantidade == TAMANHO_MAXIMO) {
        printf("Fila cheia. Nao foi possivel inserir nova peca.\n");
        return;
    }

    fila[fim] = gerarPeca();
    fim = (fim + 1) % TAMANHO_MAXIMO;
    quantidade++;
    printf("Peca inserida com sucesso.\n");
}

// Remove a peca da frente da fila
void desenfileirar() {
    if (quantidade == 0) {
        printf("Fila vazia. Nenhuma peca para jogar.\n");
        return;
    }

    Peca removida = fila[inicio];
    inicio = (inicio + 1) % TAMANHO_MAXIMO;
    quantidade--;
    printf("Peca [%c %d] jogada.\n", removida.nome, removida.id);
}

// Exibe o estado atual da fila
void exibirFila() {
    printf("\nFila de pecas:\n");
    if (quantidade == 0) {
        printf("[vazia]\n");
        return;
    }

    int i;
    int idx = inicio;
    for (i = 0; i < quantidade; i++) {
        printf("[%c %d] ", fila[idx].nome, fila[idx].id);
        idx = (idx + 1) % TAMANHO_MAXIMO;
    }
    printf("\n");
}

// Exibe o menu de opcoes
void menu() {
    printf("\nOpcoes disponiveis:\n");
    printf("1 - Jogar peca (dequeue)\n");
    printf("2 - Inserir nova peca (enqueue)\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");
}

// Funcao principal
int main() {
    srand(time(NULL)); // inicializa gerador aleatorio

    // Inicializa a fila com 5 pecas
    for (int i = 0; i < TAMANHO_MAXIMO; i++) {
        enfileirar();
    }

    int opcao;
    do {
        exibirFila();
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                desenfileirar();
                break;
            case 2:
                enfileirar();
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
