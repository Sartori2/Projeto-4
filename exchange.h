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


// Investidor
int login(char* cpf_out);
int menu();
int consultar_extrato(char* cpf);
int comprar_criptomoedas(Saldos* saldos, char* cpf);
int vender_criptomoedas(Saldos* saldos, char* cpf);
int depositar(Saldos* saldos, char* cpf);
int sacar(char* senha_usuario, Saldos* saldos, char* cpf);

// Admin
int login_admin();
int menu_admin();
int cadastrar_usuario();
int excluir_usuario();
int consultar_investidor();
void atualizar_cotacao();

// Sistema
int carregar_users(char* cpf, Saldos* saldos);
int salvar_users(char* cpf, Saldos* saldos);
char* validar_senha(char* cpf);

#endif
