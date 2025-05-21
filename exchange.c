#include "exchange.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define BANCO_USUARIOS "usuarios.txt"

Usuario usuarios[MAX_USUARIOS];
float valor_bitcoin;
float valor_ethereum;
float valor_ripple;
int totalUsuarios;

struct usuario usuarios[MAX_USUARIOS] = {
    {"Renan Sartori", "1234567890", "12345", {0}},  
    {"Rafael Almeida", "9876543210", "54321", {0}}
};

Admin admin = {
    "12398745605",
    "23456"
};

Criptomoeda criptos[MAX_CRIPTOS];
int totalCriptos = 0;



float valor_bitcoin = 500000.00;
float valor_ethereum = 10000.00;
float valor_ripple = 12.00;

int totalUsuarios = 2;

int carregar_users(char* cpf, Saldos* saldos) {
    char filename[20];
    sprintf(filename, "CPF_%s.txt", cpf);

    FILE* file = fopen(filename, "r+");
    if (file == NULL) {
        file = fopen(filename, "w");
        if (file == NULL) {
            printf("Erro ao criar o arquivo.\n");
            return 0;
        }

        fprintf(file, "CPF: %s\n", cpf);
        fprintf(file, "Reais: 0.00\n");
        fprintf(file, "Bitcoin: 0.0000000\n");
        fprintf(file, "Ethereum: 0.0000000\n");
        fprintf(file, "Ripple: 0.0000000\n");
        fclose(file);

        saldos->reais = 0;
        saldos->bitcoin = 0;
        saldos->ethereum = 0;
        saldos->ripple = 0;
        return 1;
    }

    char linha[100];
    while (fgets(linha, sizeof(linha), file) != NULL) {
        if (strstr(linha, "Reais:")) {
            sscanf(linha, "Reais: %f", &saldos->reais);
        } 
        else if (strstr(linha, "Bitcoin:")) {
            sscanf(linha, "Bitcoin: %f", &saldos->bitcoin);
        }
        else if (strstr(linha, "Ethereum:")) {
            sscanf(linha, "Ethereum: %f", &saldos->ethereum);
        }
        else if (strstr(linha, "Ripple:")) {
            sscanf(linha, "Ripple: %f", &saldos->ripple);
        }
    }
    fclose(file);
    return 1;
}

int salvar_users(char* cpf, Saldos* saldos) {
    char filename[20];
    sprintf(filename, "CPF_%s.txt", cpf);

    FILE* file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    fprintf(file, "CPF: %s\n", cpf);
    fprintf(file, "Reais: %.2f\n", saldos->reais);
    fprintf(file, "Bitcoin: %.7f\n", saldos->bitcoin);
    fprintf(file, "Ethereum: %.7f\n", saldos->ethereum);
    fprintf(file, "Ripple: %.7f\n", saldos->ripple);

    fclose(file);
    return 1;
}

int login(char* cpf_out){
    char cpf[12];
    char senha[7];

    printf("==== Login ====\n");
    printf("= CPF: ");
    scanf("%s", cpf);

    printf("= Senha: ");
    scanf(" %s", senha);

    for(int i = 0; i < totalUsuarios; i++){
        if(strcmp(usuarios[i].cpf, cpf) == 0 &&
            strcmp(usuarios[i].senha, senha) == 0){
                printf("= Login concluído com sucesso =\n");
                strcpy(cpf_out, cpf);
                return 1;
        }
    }
    printf("= Login inválido =\n");
    return -1;
}

int consultar_extrato(char* cpf){
    char filename[30];
    sprintf(filename, "CPF_%s.txt", cpf);

    FILE* file = fopen(filename, "r");
    if(file == NULL){
        printf("Erro ao abrir o arquivo de extrato.\n");
        return 0;
    }

    char linha[100];
    printf("\n======== Extrato ========\n");
    while(fgets(linha, sizeof(linha), file)){
        printf("%s", linha);
    }
    fclose(file);
    return 1;
}

int depositar(Saldos* saldos, char* cpf){
    float valor;
    printf("\n");
    printf("============ Depositar ============\n");
    printf("= Digite o valor para depositar: ");
    scanf("%f", &valor);

    if(valor <= 0){
        printf("\n");
        printf("= Digite um valor positivo\n");
        return 0;
    }

    saldos->reais += valor;

    if (!salvar_users(cpf, saldos)) {
        printf("Erro ao salvar os dados do usuário.\n");
        return 0;
    }

    char filename[30];
    sprintf(filename, "extrato_%s.txt", cpf);
    FILE* extrato = fopen(filename, "a");
    fprintf(extrato, "Depósito: R$ %.2f\n", valor);
    fclose(extrato);


    printf("\n");
    printf("=====================\n");
    printf("= Deposito realizado\n");
    return 1;
}

char* validar_senha(char* cpf){
    for(int i = 0; i < totalUsuarios; i++){
        if(strcmp(usuarios[i].cpf, cpf) == 0){
            return usuarios[i].senha;
        }
    }
    return NULL;
}

int sacar(char* senha_usuario, Saldos* saldos, char* cpf){
    float valor;
    char senha[7];

    printf("\n");
    printf("======== Validação ========\n");
    printf("= Digite sua senha: ");
    scanf("%s", senha);

    if(strcmp(senha, senha_usuario) != 0){
        printf("\n");
        printf("= Senha incorreta\n");
        return 0;
    }

    printf("= Digite o valor para sacar: ");
    scanf("%f", &valor);

    if(valor <= 0){
        printf("\n");
        printf("= Digite um valor positivo\n");
        return 0;
    }

    if(valor > saldos->reais){
        printf("\n");
        printf("= Saldo insuficiente\n");
        return 0;
    }
    
    saldos->reais -= valor;

    if (!salvar_users(cpf, saldos)) {
        printf("Erro ao salvar os dados do usuário.\n");
        return 0;
    }
    

    char filename[30];
    sprintf(filename, "extrato_%s.txt", cpf);
    FILE* extrato = fopen(filename, "a");
    fprintf(extrato, "Depósito: R$ %.2f\n", valor);
    fclose(extrato);


    printf("\n");
    printf("===== Saque =====\n");
    printf("= Saque realizado\n", valor);
    return 1;
}

int comprar_criptomoedas(Saldos* saldos, char* cpf) {
    float valor;
    int opcoes;
    float preco, quantidade = 0.0;

    printf("\n======== Comprar Criptomoedas ========\n");
    printf("1: Bitcoin - %.2f\n", valor_bitcoin);
    printf("2: Ethereum - %.2f\n", valor_ethereum);
    printf("3: Ripple - %.2f\n", valor_ripple);
    printf("= Escolha uma opção: ");
    scanf("%d", &opcoes);

    printf("= Digite o valor, em reais, para comprar: ");
    scanf("%f", &preco);

    if (preco <= 0 || preco > saldos->reais) {
        printf("= Saldo insuficiente ou valor inválido\n");
        return 0;
    }

    switch (opcoes) {
        case 1:
            quantidade = preco / valor_bitcoin;
            saldos->bitcoin += quantidade;
            printf("= Você comprou %.7f BTC\n", quantidade);
            break;
        case 2:
            quantidade = preco / valor_ethereum;
            saldos->ethereum += quantidade;
            printf("= Você comprou %.7f ETH\n", quantidade);
            break;
        case 3:
            quantidade = preco / valor_ripple;
            saldos->ripple += quantidade;
            printf("= Você comprou %.7f XRP\n", quantidade);
            break;
        default:
            printf("= Opção inválida\n");
            return 0;
    }

    saldos->reais -= preco;

    time_t t;
    struct tm* tm_info;
    char data_hora[25];  

    time(&t);
    tm_info = localtime(&t);
    strftime(data_hora, sizeof(data_hora), "%Y-%m-%d %H:%M:%S", tm_info);

    char filename[30];
    sprintf(filename, "extrato_%s.txt", cpf);
    FILE* extrato = fopen(filename, "a");
    fprintf(extrato, "Depósito: R$ %.2f\n", valor);
    fclose(extrato);

    printf("= Compra realizada com sucesso\n");
    return 1;
}

int vender_criptomoedas(Saldos* saldos, char* cpf) {
    float valor;
    int opcoes;
    float quantia;

    printf("\n======== Vender Criptomoedas ========\n");
    printf("1: Bitcoin\n", valor_bitcoin);
    printf("2: Ethereum\n", valor_ethereum);
    printf("3: Ripple\n", valor_ripple);
    printf("= Escolha uma opção: ");
    scanf("%d", &opcoes);

    printf("= Digite a quantidade que deseja vender: ");
    scanf("%f", &quantia);

    float valor_reais = 0.0;

    switch(opcoes){
        case 1:
            if(quantia > saldos->bitcoin){
                printf("Saldo insuficiente de Bitcoin.\n");
                return 0;
            }
            saldos->bitcoin -= quantia;
            valor_reais = quantia * valor_bitcoin;
            break;
        case 2:
            if(quantia > saldos->ethereum){
                printf("Saldo insuficiente de Ethereum.\n");
                return 0;
            }
            saldos->ethereum -= quantia;
            valor_reais = quantia * valor_ethereum;
            break;
        case 3:
            if(quantia > saldos->ripple){
                printf("Saldo insuficiente de Ripple.\n");
                return 0;
            }
            saldos->ripple -= quantia;
            valor_reais = quantia * valor_ripple;
            break;
        default:
            printf("Opção inválida.\n");
            return 0;        
    }

    saldos->reais += valor_reais;

    if (!salvar_users(cpf, saldos)) {
        printf("Erro ao salvar os dados do usuário.\n");
        return 0;
    }

    time_t t;
    struct tm* tm_info;
    char data_hora[25];

    time(&t);
    tm_info = localtime(&t);
    strftime(data_hora, sizeof(data_hora), "%Y-%m-%d %H:%M:%S", tm_info);

    char filename[30];
    sprintf(filename, "extrato_%s.txt", cpf);
    FILE* extrato = fopen(filename, "a");
    fprintf(extrato, "Depósito: R$ %.2f\n", valor);
    fclose(extrato);

    printf("Venda realizada com sucesso: R$ %.2f.\n", valor_reais);
    printf("Novo saldo de Reais: R$ %.2f.\n", saldos->reais);
    return 1;
}

void cadastrar_criptomoeda() {
    printf("\n");
    printf("======== Cadastrar Criptomoeda ========\n");
    if (totalCriptos >= MAX_CRIPTOS) {
        printf("Limite de criptomoedas atingido.\n");
        return;
    }

    printf("= Digite o nome da criptomoeda que deseja adicionar: ");
    scanf("%s", criptos[totalCriptos].nome);

    printf("Digite o valor da criptomoeda, em R$: ");
    scanf("%f", &criptos[totalCriptos].valor);

    printf("\n=== Criptomoeda %s cadastrada com sucesso! ===\n", criptos[totalCriptos].nome);
    totalCriptos++;

}

int menu(){
    int opcao;
    printf("\n");
    printf("========= Menu ========\n");
    printf("1: Consultar Saldo\n");
    printf("2: Consultar Extrato\n");
    printf("3: Depositar Reais\n");
    printf("4: Sacar Reais\n");
    printf("5: Comprar Criptomoedas\n");
    printf("6: Vender Criptomoedas\n");
    printf("7: Atualizar Cotação\n");
    printf("8: Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    return opcao;
}