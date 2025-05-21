#include "exchange.h"
#include <stdio.h>
#include <string.h>

struct usuario usuarios[10] = {
    {"Renan Sartori", "1234567890", "12345", {0}},  
    {"Rafael Almeida", "9876543210", "54321", {0}}
};

struct admin admin = {
    "12398745605",
    "23456"
};

int totalUsuarios = 2;

float valor_bitcoin = 500000.00;
float valor_ethereum = 10000.00;
float valor_ripple = 12.00;

int login_admin(){
    char cpf[12];
    char senha[7];

    printf("==== Admin ====\n");
    printf("= CPF: ");
    scanf("%s", cpf);

    printf("= Senha: ");
    scanf(" %s", senha);
    if(strcmp(admin.cpf, cpf) == 0 &&
        strcmp(admin.senha, senha) == 0){
            printf("= Login concluído com sucesso =\n");
            return 1;
    }
    printf("= Login inválido =\n");
    return -1;
}

int menu_admin(){
    int opcao;
    printf("\n======== Menu Admin =======\n");
    printf("1: Cadastrar Investidor\n");
    printf("2: Remover Investidor\n");
    printf("3: Listar Investidores\n");
    printf("4: Atualizar Cotação\n");
    printf("5: Ver saldo de investidor\n");
    printf("6: Ver extrato de investidor\n");
    printf("7: Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    return opcao;
}


int cadastrar_usuario(){
    struct usuario novo_usuario;
    int c;
    while((c = getchar()) != '\n' && c != EOF);
    printf("Digite o nome do investidor: ");
    fgets(novo_usuario.nome, 50, stdin);
    novo_usuario.nome[strcspn(novo_usuario.nome, "\n")] = '\0';
    printf("Digite o CPF do investidor: ");
    scanf("%11s", novo_usuario.cpf);
    
    for(int i = 0; i < totalUsuarios; i++){
        if(strcmp(usuarios[i].cpf, novo_usuario.cpf) == 0){
            printf("CPF já cadastrado\n");
            return 0;
        }
    }

    printf("Digite a senha do investidor: ");
    scanf("%6s", novo_usuario.senha);

    novo_usuario.saldos.reais = 0;
    novo_usuario.saldos.bitcoin = 0;
    novo_usuario.saldos.ethereum = 0;
    novo_usuario.saldos.ripple = 0;

    if(totalUsuarios < 10){
        usuarios[totalUsuarios] = novo_usuario;
        totalUsuarios++;
        char filename[20];
        sprintf(filename, "CPF_%s.txt", novo_usuario.cpf);
        FILE* file = fopen(filename, "w");
        if(file == NULL){
            printf("Erro ao criar o arquivo.\n");
            return 0;
        }
        
        fprintf(file, "Nome: %s\n", novo_usuario.nome);
        fprintf(file, "CPF: %s\n", novo_usuario.cpf);
        fprintf(file, "Reais: 0.00\n");
        fprintf(file, "Bitcoin: 0.0000000\n");
        fprintf(file, "Ethereum: 0.0000000\n");
        fprintf(file, "Ripple: 0.0000000\n");
        fclose(file);
        printf("Investidor cadastrado\n");
        return 1;
    }else{
        printf("Limite de usuários atingido\n");
        return 0;
    }
}

int excluir_usuario(){
    char cpf[12];
    printf("Digite o CPF do investidor: ");
    scanf("%11s", cpf);
    int c;
    while((c = getchar()) != '\n' && c != EOF);
    int encontrado = -1;

    for(int i = 0; i < totalUsuarios; i++){
        if(strcmp(usuarios[i].cpf, cpf) == 0){
            encontrado = i;
            break;
        }
    }

    if(encontrado == -1){
        printf("CPF não encontrado\n", cpf);
        printf("CPF cadastrados:\n");
        for(int i = 0; i < totalUsuarios; i++){
            printf("- %s\n", usuarios[i].cpf);
        }
        return 0;
    }

    printf("\n=== Dados do Investidor ===\n");
    printf("Nome: %s\n", usuarios[encontrado].nome);
    printf("CPF: %s\n", usuarios[encontrado].cpf);
    
    char confirmar;
    printf("CONFIRMAÇÃO - Digite (s/n) para excluir: ");
    scanf(" %c", &confirmar);

    if(confirmar == 's' || confirmar == 'S'){
        char filename[20];
        sprintf(filename, "CPF_%s.txt", cpf);
        if(remove(filename) != 0){
            printf("Não foi possível excluir o arquivo\n");
        }

        for(int i = encontrado; i < totalUsuarios - 1; i++){
            usuarios[i] = usuarios[i + 1];
        }

        totalUsuarios--;
        printf("Investidor excluído\n");
        return 1;
    }
    return 0;
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

int consultar_investidor(){
    char cpf[12];
    Saldos saldos;
    
    printf("Digite o CPF do investidor: ");
    scanf("%11s", cpf);
    int c;
    while((c = getchar()) != '\n' && c != EOF);

    int encontrado = -1;
    for(int i = 0; i < totalUsuarios; i++){
        if(strcmp(usuarios[i].cpf, cpf) == 0){
            encontrado = i;
            break;
        }
    }

    if(encontrado == -1){
        printf("CPF não encontrado\n");
        printf("CPFs cadastrados:\n");
        for(int i = 0; i < totalUsuarios; i++){
            printf("- %s (%s)\n", usuarios[i].cpf, usuarios[i].nome);
        }
        return 0;
    }

    if(!carregar_users(cpf, &saldos)){
        printf("Erro ao carregar os saldos.\n");
        return 0;
    }

    printf("\n=== Dados do investidor ===\n");
    printf("Nome: %s\n", usuarios[encontrado].nome);
    printf("CPF: %s\n", usuarios[encontrado].cpf);
    printf("\n=== Saldos ===\n");
    printf("Reais: R$ %.2f\n", saldos.reais);
    printf("Bitcoin: %.7f\n", saldos.bitcoin);
    printf("Ethereum: %.7f\n", saldos.ethereum);
    printf("Ripple: %.7f\n", saldos.ripple);
    return 1;
}

int main(){
    if(!login_adm()){
        return 1;
    }

    int opcao;
    char cpf[12];
    char senha[7];
    Saldos saldos;

    do{
        opcao = menu_adm();

        switch (opcao){
            case 1:
                printf("\n=== Cadastrar Investidor ===\n");
                printf("= Digite o CPF: ");
                scanf("%s", cpf);
                printf("= Digite a senha: ");
                scanf("%s", senha);
                cadastrar_usuario(cpf, senha);
                break;
            case 2:
                printf("\n=== Remover Investidor ===\n");
                printf("= Digite o CPF: ");
                scanf("%s", cpf);
                // Implementar função de remoção
                break;
            case 3:
                printf("\n=== Listar Investidores ===\n");
                // Implementar função de listagem
                break;
            case 4:
                atualizar_cotacao();
                break;
            case 5:
                printf("\n=== Ver saldo de investidor ===\n");
                printf("= Digite o CPF: ");
                scanf("%s", cpf);
                if (carregar_users(cpf, &saldos)){
                    printf("= Saldo de %s:\n", cpf);
                    printf("= Reais: %.2f\n", saldos.reais);
                    printf("= Bitcoin: %.7f\n", saldos.bitcoin);
                    printf("= Ethereum: %.7f\n", saldos.ethereum);
                    printf("= Ripple: %.7f\n", saldos.ripple);
            } else {
                    printf("= Investidor não encontrado\n");
                }
                break;
            case 6:
                printf("\n=== Ver extrato de investidor ===\n");
                printf("= Digite o CPF: ");
                scanf("%s", cpf);
                consultar_extrato(cpf);
                break;
            case 7:
                printf("\n === Fechando Programa ===\n");
                break;
            default:
                printf("= Opcao invalida\n");
        }
    } while(opcao != 7);

    return 0;
}