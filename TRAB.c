#include <stdio.h>
#include <stdlib.h>
#include <string.h>
m
#define MAX_NOME 100
#define MAX_CATEGORIA 50
#define MAX_UNIDADE 20
#define MAX_REGISTROS 100

typedef struct {
    char nome[MAX_NOME];
    char categoria[MAX_CATEGORIA];
    char unidade[MAX_UNIDADE];
    float quantidade;
} Insumo;

typedef struct {
    char data[11];
    char nome[MAX_NOME]; 
    float quantidade;
    float quantidade_final;
    char tipo_movimentacao[20];
} Movimentacao;

void cadastrar_informacao(Insumo *insumos, int *total_insumos);
void mostrar_insumos(Insumo *insumos, int total_insumos);
void registrar_aquisicao(Insumo *insumos, int total_insumos, Movimentacao *movimentacoes, int *total_movimentacoes);
void registrar_consumo(Insumo *insumos, int total_insumos, Movimentacao *movimentacoes, int *total_movimentacoes);
void mostrar_movimentacoes(Movimentacao *movimentacoes, int total_movimentacoes);

int main() {
    Insumo insumos[MAX_REGISTROS];
    Movimentacao movimentacoes[MAX_REGISTROS];
    int total_insumos = 0;
    int total_movimentacoes = 0;
    int opcao;

    do {
        printf("\n1. Cadastrar novo insumo\n");
        printf("2. Mostrar insumos cadastrados\n");
        printf("3. Registrar aquisicao de insumo\n");
        printf("4. Registrar consumo de insumo\n");
        printf("5. Mostrar movimentacoes de estoque\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrar_informacao(insumos, &total_insumos);
                break;
            case 2:
                mostrar_insumos(insumos, total_insumos);
                break;
            case 3:
                registrar_aquisicao(insumos, total_insumos, movimentacoes, &total_movimentacoes);
                break;
            case 4:
                registrar_consumo(insumos, total_insumos, movimentacoes, &total_movimentacoes);
                break;
            case 5:
                mostrar_movimentacoes(movimentacoes, total_movimentacoes);
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while(opcao != 6);
    
    return 0;
}

void cadastrar_informacao(Insumo *insumos, int *total_insumos) {
    if (*total_insumos >= MAX_REGISTROS) {
        printf("Limite de insumos atingido!\n");
        return;
    }

    Insumo novo_insumo;
    printf("Digite o nome do insumo: ");
    scanf(" %[^\n]", novo_insumo.nome);
    printf("Digite a categoria do insumo: ");
    scanf(" %[^\n]", novo_insumo.categoria);
    printf("Digite a unidade do insumo: ");
    scanf(" %[^\n]", novo_insumo.unidade);
    printf("Digite a quantidade do insumo: ");
    scanf("%f", &novo_insumo.quantidade);

    insumos[*total_insumos] = novo_insumo;
    (*total_insumos)++;
}

void mostrar_insumos(Insumo *insumos, int total_insumos) {
    if (total_insumos == 0) {
        printf("Nenhum insumo cadastrado.\n");
        return;
    }
    for (int i = 0; i < total_insumos; i++) {
        printf("\nInsumo %d:\n", i+1);
        printf("Nome: %s\n", insumos[i].nome);
        printf("Categoria: %s\n", insumos[i].categoria);
        printf("Unidade: %s\n", insumos[i].unidade);
        printf("Quantidade: %.2f\n", insumos[i].quantidade);
    }
}

void registrar_aquisicao(Insumo *insumos, int total_insumos, Movimentacao *movimentacoes, int *total_movimentacoes) {
    if (*total_movimentacoes >= MAX_REGISTROS) {
        printf("Limite de movimentacoes atingido!\n");
        return;
    }

    char nome[MAX_NOME];
    float quantidade_aquisicao;
    char data[11];
    
    printf("Digite o nome do insumo: ");
    scanf(" %[^\n]", nome);
    printf("Digite a quantidade adquirida: ");
    scanf("%f", &quantidade_aquisicao);
    printf("Digite a data (dd/mm/aaaa): ");
    scanf(" %s", data);

    int encontrado = 0;
    for (int i = 0; i < total_insumos; i++) {
        if (strcmp(insumos[i].nome, nome) == 0) {
            insumos[i].quantidade += quantidade_aquisicao;
            Movimentacao nova_movimentacao = {
                .quantidade = quantidade_aquisicao,
                .quantidade_final = insumos[i].quantidade,
                .tipo_movimentacao = "aquisicao"
            };
            strcpy(nova_movimentacao.nome, nome);
            strcpy(nova_movimentacao.data, data);
            
            movimentacoes[*total_movimentacoes] = nova_movimentacao;
            (*total_movimentacoes)++;
            printf("Aquisicao registrada com sucesso!\n");
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("Insumo nao encontrado!\n");
    }
}

void registrar_consumo(Insumo *insumos, int total_insumos, Movimentacao *movimentacoes, int *total_movimentacoes) {
    if (*total_movimentacoes >= MAX_REGISTROS) {
        printf("Limite de movimentacoes atingido!\n");
        return;
    }

    char nome[MAX_NOME];
    float quantidade_consumo;
    char data[11];
    
    printf("Digite o nome do insumo: ");
    scanf(" %[^\n]", nome);
    printf("Digite a quantidade consumida: ");
    scanf("%f", &quantidade_consumo);
    printf("Digite a data (dd/mm/aaaa): ");
    scanf(" %s", data);

    int encontrado = 0;
    for (int i = 0; i < total_insumos; i++) {
        if (strcmp(insumos[i].nome, nome) == 0) {
            if (insumos[i].quantidade >= quantidade_consumo) {
                insumos[i].quantidade -= quantidade_consumo;
                Movimentacao nova_movimentacao = {
                    .quantidade = quantidade_consumo,
                    .quantidade_final = insumos[i].quantidade,
                    .tipo_movimentacao = "consumo"
                };
                strcpy(nova_movimentacao.nome, nome);
                strcpy(nova_movimentacao.data, data);
                
                movimentacoes[*total_movimentacoes] = nova_movimentacao;
                (*total_movimentacoes)++;
                printf("Consumo registrado com sucesso!\n");
                encontrado = 1;
            } else {
                printf("Quantidade insuficiente de insumo!\n");
            }
            break;
        }
    }

    if (!encontrado) {
        printf("Insumo nao encontrado!\n");
    }
}

void mostrar_movimentacoes(Movimentacao *movimentacoes, int total_movimentacoes) {
    if (total_movimentacoes == 0) {
        printf("Nenhuma movimentacao registrada.\n");
        return;
    }

    for (int i = 0; i < total_movimentacoes; i++) {
        printf("\nMovimentacao %d:\n", i+1);
        printf("Data: %s\n", movimentacoes[i].data);
        printf("Insumo: %s\n", movimentacoes[i].nome);
        printf("Quantidade: %.2f\n", movimentacoes[i].quantidade);
        printf("Quantidade final: %.2f\n", movimentacoes[i].quantidade_final);
        printf("Tipo de movimentacao: %s\n", movimentacoes[i].tipo_movimentacao);
    }
}
