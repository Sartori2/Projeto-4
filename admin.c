#include "exchange.h"
#include <stdio.h>
#include <string.h>

int login_adm(){
    char cpf[12];
    char senha[7];

    printf("==== Login Admin =====\n");
    printf("= Digite seu CPF: ");
    scanf("%s", cpf);
    printf("= Digite sua senha: ");
    scanf("%s", senha);

    if(strcmp(cpf, "admin") == 0 && strcmp(senha, "admin") == 0){
        printf("= Login concluído com sucesso =\n");
        return 1;
    }
    printf("= Login inválido =\n");
    return 0;
    
}

int menu_adm(){
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
                // Implementar função de cadastro
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