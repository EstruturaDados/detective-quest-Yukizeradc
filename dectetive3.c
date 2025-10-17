#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 10

// ---------- STRUCTS ----------

// Estrutura de um comodo da mansao
typedef struct Sala {
    char nome[30];
    struct Sala *esq;
    struct Sala *dir;
} Sala;

// Estrutura da arvore BST de pistas
typedef struct Pista {
    char nome[50];
    struct Pista *esq;
    struct Pista *dir;
} Pista;

// Estrutura da tabela hash (pista -> suspeito)
typedef struct HashItem {
    char pista[50];
    char suspeito[50];
    struct HashItem *prox;
} HashItem;

HashItem* tabelaHash[TAM_HASH];

// ---------- FUNCOES ----------

// Funcao para criar uma sala dinamicamente
Sala* criarSala(char nome[]) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    nova->esq = NULL;
    nova->dir = NULL;
    return nova;
}

// Funcao hash simples
int funcaoHash(char *pista) {
    int soma = 0;
    for (int i = 0; pista[i] != '\0'; i++)
        soma += pista[i];
    return soma % TAM_HASH;
}

// Insere na tabela hash
void inserirNaHash(char *pista, char *suspeito) {
    int indice = funcaoHash(pista);
    HashItem* novo = (HashItem*)malloc(sizeof(HashItem));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->prox = tabelaHash[indice];
    tabelaHash[indice] = novo;
}

// Busca suspeito por pista
char* encontrarSuspeito(char *pista) {
    int indice = funcaoHash(pista);
    HashItem *aux = tabelaHash[indice];
    while (aux != NULL) {
        if (strcmp(aux->pista, pista) == 0)
            return aux->suspeito;
        aux = aux->prox;
    }
    return "Desconhecido";
}

// Insere uma pista na arvore BST
Pista* inserirPista(Pista *raiz, char *nome) {
    if (raiz == NULL) {
        Pista* nova = (Pista*)malloc(sizeof(Pista));
        strcpy(nova->nome, nome);
        nova->esq = nova->dir = NULL;
        return nova;
    }
    if (strcmp(nome, raiz->nome) < 0)
        raiz->esq = inserirPista(raiz->esq, nome);
    else if (strcmp(nome, raiz->nome) > 0)
        raiz->dir = inserirPista(raiz->dir, nome);
    return raiz;
}

// Mostra pistas em ordem
void listarPistas(Pista *raiz) {
    if (raiz != NULL) {
        listarPistas(raiz->esq);
        printf("- %s\n", raiz->nome);
        listarPistas(raiz->dir);
    }
}

// Define a pista da sala (logica simples)
char* pistaDaSala(char *nome) {
    if (strcmp(nome, "Biblioteca") == 0) return "Luvas sujas de tinta";
    if (strcmp(nome, "Cozinha") == 0) return "Faca com sangue";
    if (strcmp(nome, "Jardim") == 0) return "Pegadas recentes";
    if (strcmp(nome, "Sala de estar") == 0) return "Relogio quebrado";
    if (strcmp(nome, "Escritorio") == 0) return "Carta de ameaca";
    return NULL;
}

// Explora as salas
void explorarSalas(Sala *sala, Pista **pistas) {
    if (sala == NULL) return;
    printf("\nVoce esta na sala: %s\n", sala->nome);

    char *pista = pistaDaSala(sala->nome);
    if (pista != NULL) {
        printf("Voce encontrou uma pista: %s\n", pista);
        *pistas = inserirPista(*pistas, pista);
    }

    char opcao;
    printf("Escolha: (e) esquerda, (d) direita, (s) sair: ");
    scanf(" %c", &opcao);

    if (opcao == 'e') explorarSalas(sala->esq, pistas);
    else if (opcao == 'd') explorarSalas(sala->dir, pistas);
    else if (opcao == 's') printf("Exploracao encerrada.\n");
}

// Verifica suspeito final
void verificarSuspeitoFinal(Pista *pistas, char *suspeito) {
    int cont = 0;
    if (pistas == NULL) return;
    if (strcmp(encontrarSuspeito(pistas->nome), suspeito) == 0)
        cont++;
    verificarSuspeitoFinal(pistas->esq, suspeito);
    verificarSuspeitoFinal(pistas->dir, suspeito);

    static int total = 0;
    total += cont;
    if (pistas->esq == NULL && pistas->dir == NULL) {
        if (total >= 2)
            printf("\nCulpado confirmado! %s foi o autor do crime.\n", suspeito);
        else
            printf("\nNao ha provas suficientes contra %s.\n", suspeito);
        total = 0;
    }
}

// ---------- MAIN ----------
int main() {
    // Cria salas fixas (arvore binaria manual)
    Sala *raiz = criarSala("Sala de estar");
    raiz->esq = criarSala("Biblioteca");
    raiz->dir = criarSala("Cozinha");
    raiz->esq->esq = criarSala("Jardim");
    raiz->esq->dir = criarSala("Escritorio");

    // Cria tabela hash de pistas -> suspeitos
    inserirNaHash("Luvas sujas de tinta", "Arthur");
    inserirNaHash("Faca com sangue", "Beatriz");
    inserirNaHash("Pegadas recentes", "Arthur");
    inserirNaHash("Relogio quebrado", "Carlos");
    inserirNaHash("Carta de ameaca", "Arthur");

    Pista *pistas = NULL;

    printf("=== Detective Quest ===\n");
    printf("Explore a mansao e colete pistas!\n");

    explorarSalas(raiz, &pistas);

    printf("\nPistas coletadas:\n");
    listarPistas(pistas);

    char suspeito[30];
    printf("\nQuem voce acusa? ");
    scanf(" %[^\n]", suspeito);

    verificarSuspeitoFinal(pistas, suspeito);

    return 0;
}
