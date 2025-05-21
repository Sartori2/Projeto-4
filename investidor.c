#include "exchange.h"
#include <stdio.h>
#include <string.h>

int main(){
    int inicio;
    int user_logado;

    printf("=== Exchange Criptomoedas ===\n");
    printf("1. Administrador\n");
    printf("2. Usuário\n");
    printf("Digite uma opção para seguir: ");
    scanf("%d", &inicio);
    
    if(inicio == 1){
        if(login_admin() == 1){
            int opcao_adm;
            do{
                opcao_adm = menu_admin();
                switch(opcao_adm){
                    case 1:
                        cadastrar_usuario();
                        break;
                    case 2:
                        excluir_usuario();
                        break;
                    case 3:
                        consultar_investidor();
                        break;
                    case 4:
                        printf("=== Fechando Programa ===\n");
                        break;
                    default:
                        printf("Digite uma opção válida\n");
                        break;
                }
            }while(opcao_adm != 4);
        }
    }else if(inicio == 2){
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
                    char nomes[10][20];
                    float cotacoes[10];
                    int total = carregar_criptos(nomes, cotacoes, 10);
                    if (total == 0){
                        printf("= Nenhuma criptomoeda cadastrada\n");
                        break;
                    }
                    
                    printf("\n=== Comprar Criptomoedas ===\n");
                    for (int i = 0; i < total; i++) {
                        printf("%d: %s - Cotacao: R$ %.2f\n", i + 1, nomes[i], cotacoes[i]);
                    }

                    int escolha;
                    printf("= Escolha uma criptomoeda: ");
                    scanf("%d", &escolha);
                    if (escolha < 1 || escolha > total) {
                        printf("= Opção inválida.\n");
                        break;
                    }

                    comprar(nomes[escolha - 1], cotacoes[escolha - 1], &saldos, cpf);

                }  
                break;
                case 5:
                {
                    char nomes[10][20];
                    float cotacoes[10];
                    int total = carregar_criptos(nomes, cotacoes, 10);
                    if (total == 0){
                        printf("= Nenhuma criptomoeda cadastrada\n");
                        break;
                    }
                    
                    printf("\n=== Vender Criptomoedas ===\n");
                    for (int i = 0; i < total; i++) {
                        printf("%d: %s - Cotacao: R$ %.2f\n", i + 1, nomes[i], cotacoes[i]);
                    }

                    int escolha;
                    printf("= Escolha uma criptomoeda: ");
                    scanf("%d", &escolha);
                    if (escolha < 1 || escolha > total) {
                        printf("= Opção inválida.\n");
                        break;
                    }

                    vender(nomes[escolha - 1], cotacoes[escolha - 1], &saldos, cpf);                    
                }
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
    }else{
        printf("Digite uma opção válida\n");
        return 1;
    }
}