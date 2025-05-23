#include "exchange.h"
#include <stdio.h>
#include <string.h>

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

int main(){
    char cpf[12];
    Saldos saldos;
    
    if(login(cpf) == -1){
        return 1;
    }
    
    if(!carregar_users(cpf, &saldos)){
        printf("Erro ao carregar usuário\n");
        return 1;
    }
    
    int opcao;
    do{
        opcao = menu();
        switch (opcao){
            case 1:
                printf("===== Saldo atual: =====\n");
                printf("Reais: %.2f\n", saldos.reais);
                printf("Bitcoin: %.7f\n", saldos.bitcoin);
                printf("Ethereum: %.7f\n", saldos.ethereum);
                printf("Ripple: %.7f\n", saldos.ripple);
                printf("\n");
                break;
            case 2:
                consultar_extrato(cpf);
                break;
            case 3:
                depositar(&saldos, cpf);
                break;
            case 4: {
                char* senha_usuario = validar_senha(cpf);
                if(senha_usuario == NULL){
                    printf("Erro: Usuário não encontrado.\n");
                    break;
                }
                sacar(senha_usuario, &saldos, cpf);
                break;
            }
            case 5:
                comprar_criptomoedas(&saldos, cpf);
                break;
            case 6:
                vender_criptomoedas(&saldos, cpf);
                break;
            case 7:
                printf("Fechando Programa\n");
                if(!salvar_users(cpf, &saldos)){
                    printf("Erro ao salvar dados!\n");
                    return 1;
                }
                break;
            default:
                printf("Digite uma opção válida\n");
        }
    }while (opcao != 7);
    return 0;
}