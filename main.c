#include "exchange.h"
#include <stdio.h>
#include <string.h>

int main(){
    Saldos saldos;
    char cpf[12];
    int usuario_logado;

    usuario_logado = login(cpf);
    if(usuario_logado == -1){
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
                    printf("Usuario não encontrado\n");
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
                atualizar_cotacao();
                break;
            case 8:
                printf("Fechando Programa\n");
                if (!salvar_users(cpf, &saldos)) {
                    printf("Erro ao salvar dados!\n");
                    return 1;
                }
                break;
            default:
                printf("Digite uma opção válida\n");
                break;
        }
    }while (opcao != 8);
    return 0;
}