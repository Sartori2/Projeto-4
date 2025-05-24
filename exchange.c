#include "exchange.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define BANCO_USUARIOS "usuarios.txt"

Usuario usuarios[MAX_USUARIOS];

Admin admin = {
    .cpf = "54648618823",
    .senha = "rafis"
};

Criptomoeda criptos[MAX_CRIPTOS];
int totalCriptos = 0;

Extrato extratos[MAX_EXTRATOS];
int totalExtratos = 0;

float valor_bitcoin = 500000.00;
float valor_ethereum = 10000.00;
float valor_ripple = 12.00;

int totalUsuarios = 0;

int carregar_criptos(char nomes[][20], float cotacoes[], int maximo){
    FILE* file = fopen("criptos.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de criptomoedas.\n");
        return 0;
    }

    int count = 0;
    while (count < maximo && fscanf(file, "%s %f", nomes[count], &cotacoes[count]) == 2) {
        count++;
    }
    fclose(file);
    return count;
}

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

    FILE* file = fopen(filename, "w");
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

int salvar_todos_users() {
    FILE* f = fopen("usuarios.txt", "w");
    if (!f) {
        printf("= Erro ao abrir o arquivo usuarios.txt para escrita\n");
        return 0;
    }
    for (int i = 0; i < totalUsuarios; i++) {
        fprintf(f, "%s;%s;%s\n", usuarios[i].nome, usuarios[i].cpf, usuarios[i].senha);
    }
    fflush(f);
    fclose(f);
    printf("= Usuários salvos com sucesso em usuarios.txt (%d usuários)\n", totalUsuarios);
    return 1;
}

int carregar_todos_users() {
    FILE* f = fopen("usuarios.txt", "r");
    if (!f) {
        printf("= Erro: Não foi possível abrir o arquivo usuarios.txt\n");
        return 0;
    }

    totalUsuarios = 0;
    char linha[100];
    while (fgets(linha, sizeof(linha), f) != NULL) {
        linha[strcspn(linha, "\n")] = '\0';
        printf("= Linha lida: %s\n", linha);
        if (sscanf(linha, "%49[^;];%11[^;];%6s", usuarios[totalUsuarios].nome, usuarios[totalUsuarios].cpf, usuarios[totalUsuarios].senha) == 3) {
            usuarios[totalUsuarios].saldos.reais = 0;
            usuarios[totalUsuarios].saldos.bitcoin = 0;
            usuarios[totalUsuarios].saldos.ethereum = 0;
            usuarios[totalUsuarios].saldos.ripple = 0;
            totalUsuarios++;
            printf("= Usuário carregado: %s (CPF: %s)\n", usuarios[totalUsuarios-1].nome, usuarios[totalUsuarios-1].cpf);
        } else {
            printf("= Erro: Formato inválido na linha: %s\n", linha);
        }
    }
    fclose(f);
    if (totalUsuarios == 0) {
        printf("= Nenhum usuário carregado de usuarios.txt\n");
    } else {
        printf("= Total de usuários carregados: %d\n", totalUsuarios);
    }
    return totalUsuarios > 0 ? 1 : 0;
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
    sprintf(filename, "extrato_%s.txt", cpf);

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
    fprintf(extrato, "Saque: R$ %.2f\n", valor);
    fclose(extrato);


    printf("\n");
    printf("===== Saque =====\n");
    printf("= Saque realizado: R$ %.2f\n", valor);    
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
    fprintf(extrato, "Compra de %s: R$ %.2f (%s)\n", 
    (opcoes == 1 ? "Bitcoin" : opcoes == 2 ? "Ethereum" : "Ripple"), 
    preco, 
    data_hora);
    fclose(extrato);

    printf("= Compra realizada com sucesso\n");
    return 1;
}

int vender_criptomoedas(Saldos* saldos, char* cpf) {
    float valor;
    int opcoes;
    float quantia;

    printf("\n======== Vender Criptomoedas ========\n");
    printf("1: Bitcoin (R$ %.2f)\n", valor_bitcoin);
    printf("2: Ethereum (R$ %.2f)\n", valor_ethereum);
    printf("3: Ripple (R$ %.2f)\n", valor_ripple);
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
    fprintf(extrato, "Venda: R$ %.2f (%s) \n", valor_reais, data_hora);
    fclose(extrato);

    printf("Venda realizada com sucesso: R$ %.2f.\n", valor_reais);
    printf("Novo saldo de Reais: R$ %.2f.\n", saldos->reais);
    return 1;
}

void atualizar_cotacao(){
    srand(time(NULL));

    float variacoes[3];
    float* cotacoes[3] = {&valor_bitcoin, &valor_ethereum, &valor_ripple};

    for(int i = 0; i < 3; i++){
        float variacao = ((rand() % 11) - 5) / 100.0;  // -0.05 a +0.05
        *cotacoes[i] *= (1 + variacao);
    }

    printf("\n======== Atualizar Cotação ========\n");
    printf("Cotação atual:\n");
    printf("Bitcoin: %.2f\n", valor_bitcoin);
    printf("Ethereum: %.2f\n", valor_ethereum);
    printf("Ripple: %.2f\n", valor_ripple);
}