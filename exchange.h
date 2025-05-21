#ifndef EXCHANGE_H
#define EXCHANGE_H

typedef struct Saldos {
    float reais;
    float bitcoin;
    float ethereum;
    float ripple;
} Saldos;

struct usuario {
    char nome[50];
    char cpf[12];
    char senha[7];
    Saldos saldos;
};

struct admin {
    char cpf[12];
    char senha[7];
};

int login_admin();
int login(char* cpf_out);
int menu_admin();
int menu();
int cadastrar_usuario();
int excluir_usuario();
int carregar_users(char* cpf, Saldos* saldos);
int salvar_users(char* cpf, Saldos* saldos);
int consultar_extrato(char* cpf);
int consultar_investidor();
int depositar(Saldos* saldos, char* cpf);
char* validar_senha(char* cpf);
int sacar(char* senha_usuario, Saldos* saldos, char* cpf);
int comprar_criptomoedas(Saldos* saldos, char* cpf);
int vender_criptomoedas(Saldos* saldos, char* cpf);
void atualizar_cotacao();

#endif
