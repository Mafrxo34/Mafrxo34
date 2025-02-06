#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50
#define MAX_CATEGORIA 30
#define MAX_UNIDADE 10
#define MAX_TIPO 10
#define MAX_REGISTROS 100

typedef struct {
    char nome[MAX_NOME];
    char categoria[MAX_CATEGORIA];
    char unidade[MAX_UNIDADE];
    float quantidade;
} Insumo;

typedef struct {
    char nome[MAX_NOME];
    float quantidade;
    float quantidade_final;
    char tipo_movimentacao[MAX_TIPO];
    char data[11];
} Movimentacao;

Insumo *insumos = NULL;
Movimentacao *movimentacoes = NULL;
int total_insumos = 0;
int total_movimentacoes = 0;

void registrar_aquisicao() {  
    int insumo_adquirido;

    if (total_insumos == 0)
    {
        printf("Adicione um insumo primeiro!\n");
        return;
    }

    for (int i = 0; i < total_insumos; i++)
    {
        printf("[ %d ] Nome do insumo: %s\n", i, insumos[i].nome);
    }
    
    printf("Escolha a qual insumo voce quer registrar a aquisicao: ");
    scanf("%d", &insumo_adquirido);
    while (insumo_adquirido < 0 || insumo_adquirido > total_insumos - 1)
    {
        printf("Opcao invalida! Escolha de novo: ");
        scanf("%d", &insumo_adquirido);
    }

    movimentacoes = realloc(movimentacoes, (total_movimentacoes + 1) * sizeof(Movimentacao));

    if (movimentacoes == NULL)
    {
        printf("Erro ao alocar memoria para fazer o registro de movimentacao.");
        exit(1);
    }
    total_movimentacoes++;

    char nome[MAX_NOME];
    float quantidade_adquirida;
    char data[11];
    
    strcpy(nome, insumos[insumo_adquirido].nome);

    printf("\nDigite a quantidade adquirida: ");
    scanf("%f", &quantidade_adquirida);
    while (quantidade_adquirida < 0)
    {
        printf("Quantidade inválida, digite novamente: ");
        scanf("%f", &quantidade_adquirida);
    }
    
    printf("Digite a data (dd/mm/aaaa): ");
    setbuf(stdin, NULL);
    fgets(data, 11, stdin);
    strtok(data, "\n");

    insumos[insumo_adquirido].quantidade += quantidade_adquirida;

    strcpy(movimentacoes[total_movimentacoes - 1].nome, nome);
    movimentacoes[total_movimentacoes - 1].quantidade = quantidade_adquirida;
    movimentacoes[total_movimentacoes - 1].quantidade_final = insumos[insumo_adquirido].quantidade;
    strcpy(movimentacoes[total_movimentacoes - 1].tipo_movimentacao, "AQUISICAO");
    strcpy(movimentacoes[total_movimentacoes - 1].data, data);
}

void registrar_consumo() {
    
    int insumo_consumido;

    if (total_insumos == 0)
    {
        printf("Adicione um insumo primeiro!\n");
        return;
    }

    for (int i = 0; i < total_insumos; i++)
    {
        printf("[ %d ] Nome do insumo: %s\n", i, insumos[i].nome);
    }
    
    printf("Escolha a qual insumo voce quer registrar o consumo: ");
    scanf("%d", &insumo_consumido);
    while (insumo_consumido < 0 || insumo_consumido > total_insumos - 1)
    {
        printf("Opcao invalida! Escolha de novo: ");
        scanf("%d", &insumo_consumido);
    }
    
    movimentacoes = realloc(movimentacoes, (total_movimentacoes + 1) * sizeof(Movimentacao));

    if (movimentacoes == NULL)
    {
        printf("Erro ao alocar memoria para fazer o registro de movimentacao.");
        exit(1);
    }
    total_movimentacoes++;

    char nome[MAX_NOME];
    float quantidade_consumo;
    char data[11];
    
    strcpy(nome, insumos[insumo_consumido].nome);

    printf("\nDigite a quantidade consumida: ");
    scanf("%f", &quantidade_consumo);
    while (quantidade_consumo < 0 || quantidade_consumo > insumos[insumo_consumido].quantidade)
    {
        printf("Quantidade inválida ou maior que a posse do insumo, digite novamente: ");
        scanf("%f", &quantidade_consumo);
    }
    
    printf("Digite a data (dd/mm/aaaa): ");
    setbuf(stdin, NULL);
    fgets(data, 11, stdin);
    strtok(data, "\n");


    insumos[insumo_consumido].quantidade -= quantidade_consumo;

    strcpy(movimentacoes[total_movimentacoes - 1].nome, nome);
    movimentacoes[total_movimentacoes - 1].quantidade = quantidade_consumo;
    movimentacoes[total_movimentacoes - 1].quantidade_final = insumos[insumo_consumido].quantidade;
    strcpy(movimentacoes[total_movimentacoes - 1].tipo_movimentacao, "CONSUMO");
    strcpy(movimentacoes[total_movimentacoes - 1].data, data);
}

void mostrar_movimentacoes() {
    if (total_movimentacoes == 0) {
        printf("Nenhuma movimentacao registrada.\n");
        return;
    }

    for (int i = 0; i < total_movimentacoes; i++) {
        printf("Movimentacao %d:\n", i+1);
        printf("Data: %s\n", movimentacoes[i].data);
        printf("Insumo: %s\n", movimentacoes[i].nome);
        printf("Quantidade: %.2f\n", movimentacoes[i].quantidade);
        printf("Quantidade final: %.2f\n", movimentacoes[i].quantidade_final);
        printf("Tipo de movimentacao: %s\n\n", movimentacoes[i].tipo_movimentacao);
    }
}


int menu() {
    printf("\n------------------------\n");
    printf("Escolha uma opcao:\n");
    printf("[ 1 ] Registrar Insumo\n");
    printf("[ 2 ] Registrar Aquisicao\n");
    printf("[ 3 ] Registrar Consumo\n");
    printf("[ 4 ] Mostrar Insumos\n");
    printf("[ 5 ] Mostrar Movimentacoes\n");
    printf("[ 6 ] Sair\n");
    printf("Opcao: ");

    int opcao;
    scanf("%d", &opcao);

    while (opcao > 6 || opcao < 1)
    {
        printf("Opcao invalida, digite uma valida: ");
        scanf("%d", &opcao);
    }
    
    printf("------------------------\n\n");
    return opcao;
}

void adicionar_insumo() {

    insumos = realloc(insumos, (total_insumos + 1) * sizeof(Insumo));

    if (insumos == NULL)
    {
        printf("Erro ao alocar a memória!");
        exit(1);
    }
    
    printf("Digite o nome do insumo (max 49 letras): ");
    setbuf(stdin, NULL);
    fgets(insumos[total_insumos].nome, MAX_NOME, stdin);
    strtok(insumos[total_insumos].nome, "\n");

    printf("Digite a categoria (max 29 letras): ");
    setbuf(stdin, NULL);
    fgets(insumos[total_insumos].categoria, MAX_CATEGORIA, stdin);
    strtok(insumos[total_insumos].categoria, "\n");

    printf("Digite a unidade (max 9 letras): ");
    setbuf(stdin, NULL);
    fgets(insumos[total_insumos].unidade, MAX_UNIDADE, stdin);
    strtok(insumos[total_insumos].unidade, "\n");

    printf("Digite a quantidade: ");
    scanf("%f", &insumos[total_insumos].quantidade);

    total_insumos++;

    printf("\nInsumo registrado com sucesso!\n");
}

void mostrar_insumos() {
    
    if (total_insumos == 0)
    {
        printf("Nenhum insumo registrado.\n");
        return;
    }
    
    for (int i = 0; i < total_insumos; i++)
    {
        printf("\nNome: %s\n", insumos[i].nome);
        printf("Categoria: %s\n", insumos[i].categoria);
        printf("Quantidade: %.2f %s\n", insumos[i].quantidade, insumos[i].unidade);
        printf("\n");
    }
}

void salvar_insumos() {

    FILE *arquivo = fopen("insumos.bin", "wb");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo dos insumos para salvar!\n");
        return;
    }

    fwrite(&total_insumos, sizeof(int), 1, arquivo);
    fwrite(insumos, sizeof(Insumo), total_insumos, arquivo);

    fclose(arquivo);
}

void salvar_movimentacoes() {

    FILE *arquivo = fopen("movimentacoes.bin", "wb");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo das movimentacoes para salvar!\n");
        return;
    }

    fwrite(&total_movimentacoes, sizeof(int), 1, arquivo);
    fwrite(movimentacoes, sizeof(Movimentacao), total_movimentacoes, arquivo);

    fclose(arquivo);   
}

void carregar_insumos() {

    FILE *arquivo = fopen("insumos.bin", "rb");

    if (arquivo == NULL) {
        printf("Nenhum arquivo dos insumos encontrado. Iniciando sem dados.\n");
        return;
    }

    fread(&total_insumos, sizeof(int), 1, arquivo);
    insumos = realloc(insumos, total_insumos * sizeof(Insumo));

    if (insumos == NULL) {
        printf("Erro ao alocar memória para carregar os insumos!\n");
        fclose(arquivo);
        exit(1);
    }

    fread(insumos, sizeof(Insumo), total_insumos, arquivo);
    fclose(arquivo);
}

void carregar_movimentacoes() {

    FILE *arquivo = fopen("movimentacoes.bin", "rb");

    if (arquivo == NULL) {
        printf("Nenhum arquivo das movimentacoes encontrado. Iniciando sem dados.\n");
        return;
    }

    fread(&total_movimentacoes, sizeof(int), 1, arquivo);
    movimentacoes = realloc(movimentacoes, total_movimentacoes * sizeof(Movimentacao));

    if (movimentacoes == NULL) {
        printf("Erro ao alocar memória para carregar as movimentacoes!\n");
        fclose(arquivo);
        exit(1);
    }

    fread(movimentacoes, sizeof(Movimentacao), total_movimentacoes, arquivo);
    fclose(arquivo);
}

int main() {
    carregar_insumos();
    carregar_movimentacoes();
    int opcao;

    do {
        opcao = menu();

        switch (opcao) {
            case 1:
                adicionar_insumo();
                break;
            case 2:
                registrar_aquisicao();
                break;
            case 3:
                registrar_consumo();
                break;
            case 4:
                mostrar_insumos();
                break;
            case 5:
                mostrar_movimentacoes();
                break;
            case 6:
                printf("Saindo...\n");
                break;
        }

    } while (opcao != 6);

    salvar_insumos();
    salvar_movimentacoes();
    free(insumos);
    free(movimentacoes);
    return 0;
}
