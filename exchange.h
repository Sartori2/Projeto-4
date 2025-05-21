#ifndef EXCHANGE_H
#define EXCHANGE_H
#define MAX_USUARIOS 100
#define MAX_EXTRATOS 100
#define MAX_CRIPTOS 10

typedef struct{
    char nome[20];
    float valor;
} Criptomoeda;

typedef struct{
    char cpf[12];
    char descricao[100]; // "compra" ou "venda"
} Extrato;

typedef struct Saldos {
    float reais;
    float bitcoin;
    float ethereum;
    float ripple;
} Saldos;

typedef struct usuario {
    char nome[50];
    char cpf[12];
    char senha[7];
    Saldos saldos;
} Usuario;

typedef struct admin {
    char cpf[12];
    char senha[7];
} Admin;

extern Usuario usuarios[MAX_USUARIOS];
extern Admin admin;
extern float valor_bitcoin;
extern float valor_ethereum;
extern float valor_ripple;
extern int totalUsuarios;
extern Criptomoeda criptomoedas[MAX_CRIPTOS];
extern int totalCriptos;
extern Extrato extratos[MAX_EXTRATOS];
extern int totalExtratos;


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
int saldo_investidor();
void atualizar_cotacao();
void cadastrar_criptomoeda();
void excluir_criptomoeda();
void adicionar_extrato(char cpf[], char descricao[]);
void extrato_investidor(char cpf[]);

// Sistema
int carregar_users(char* cpf, Saldos* saldos);
int salvar_users(char* cpf, Saldos* saldos);
char* validar_senha(char* cpf);

#endif
