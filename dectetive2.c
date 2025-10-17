#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo a struct Sala
typedef struct Sala {
    char nome[50];        // Nome do comodo
    char pista[100];      // Pista opcional encontrada
    struct Sala *esquerda; // Comodo a esquerda
    struct Sala *direita;  // Comodo a direita
} Sala;

// Definindo a struct para a arvore de pistas (BST)
typedef struct PistaNode {
    char pista[100];      // Pista coletada
    struct PistaNode *esquerda; // No a esquerda (menor)
    struct PistaNode *direita;  // No a direita (maior)
} PistaNode;

// Funcao para criar uma sala
Sala* criarSala(char nome[], char pista[]) {
    Sala* novaSala = (Sala*) malloc(sizeof(Sala));
    strcpy(novaSala->nome, nome);
    if (strlen(pista) > 0) {
        strcpy(novaSala->pista, pista);
    } else {
        strcpy(novaSala->pista, "");  // Sem pista
    }
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

// Funcao para inserir pista na arvore de pistas (BST)
PistaNode* inserirPista(PistaNode* raiz, char pista[]) {
    if (raiz == NULL) {
        PistaNode* novaPista = (PistaNode*) malloc(sizeof(PistaNode));
        strcpy(novaPista->pista, pista);
        novaPista->esquerda = novaPista->direita = NULL;
        return novaPista;
    }

    if (strcmp(pista, raiz->pista) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    } else {
        raiz->direita = inserirPista(raiz->direita, pista);
    }

    return raiz;
}

// Funcao para explorar as salas e coletar pistas
void explorarSalasComPistas(Sala* salaAtual, PistaNode** raizPista) {
    char opcao;
    while (1) {
        // Exibe o nome do comodo e, se houver, a pista
        printf("Sala: %s\n", salaAtual->nome);
        if (strlen(salaAtual->pista) > 0) {
            printf("Pista: %s\n", salaAtual->pista);
            // Adiciona a pista a arvore de pistas
            *raizPista = inserirPista(*raizPista, salaAtual->pista);
        }

        // Pergunta ao jogador para qual direcao ele quer ir
        printf("Escolha a direcao (e - esquerda, d - direita, s - sair): ");
        scanf(" %c", &opcao);

        if (opcao == 'e' && salaAtual->esquerda != NULL) {
            salaAtual = salaAtual->esquerda;
        } else if (opcao == 'd' && salaAtual->direita != NULL) {
            salaAtual = salaAtual->direita;
        } else if (opcao == 's') {
            break; // Sair
        } else {
            printf("Opcao invalida. Tente novamente.\n");
        }
    }
}

// Funcao para exibir as pistas ordenadas (em ordem alfabetica)
void exibirPistas(PistaNode* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);  // Percorre a esquerda
        printf("%s\n", raiz->pista);   // Exibe a pista
        exibirPistas(raiz->direita);   // Percorre a direita
    }
}

// Funcao principal (main)
int main() {
    // Criar salas da mansao
    Sala* hall = criarSala("Hall de Entrada", "");
    Sala* salaEstar = criarSala("Sala de Estar", "Pista 1: Chave na gaveta");
    Sala* cozinha = criarSala("Cozinha", "Pista 2: A faca sumiu");
    Sala* biblioteca = criarSala("Biblioteca", "Pista 3: Livro aberto na pagina 42");
    
    // Definindo conexoes entre as salas (arvore binaria)
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->direita = biblioteca;
    
    // Iniciar exploracao
    PistaNode* raizPista = NULL;
    explorarSalasComPistas(hall, &raizPista);

    // Exibir todas as pistas coletadas
    printf("\nPistas coletadas:\n");
    exibirPistas(raizPista);

    // Liberar memoria (importante em C)
    free(hall);
    free(salaEstar);
    free(cozinha);
    free(biblioteca);

    return 0;
}
