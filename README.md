# Projeto Exchange de Criptomoedas

# Introdução
Este projeto é um sistema de console em C para gerenciamento de uma exchange de criptomoedas, permitindo operações tanto para investidores quanto para administradores. Investidores podem realizar depósitos, saques, compras/vendas de criptomoedas, consultar saldos e extratos. Administradores podem realizar cadastros de novos investidores, excluir investidores, cadastrar e excluir criptomoedas, ver saldo, extrato de investidores e atualizar a cotação das criptos.

# Funcionalidades para Investidores:
    Consultar Saldo: Verifique o saldo atual em reais e criptomoedas (Bitcoin, Ethereum,Ripple).
    Consultar Extrato: Consulte as transações realizadas, como depósitos, saques e compras/vendas de criptomoedas.
    Depositar Reais: Deposite reais na conta do usuário.
    Sacar Reais: Realize um saque de reais da conta do usuário.
    Comprar Criptomoedas: Compre Bitcoin, Ethereum ou Ripple usando reais.
    Vender Criptomoedas: Venda suas criptomoedas e converta de volta para reais.

# Funcionalidades para Administradores:
    Cadastrar Investidores: Cadastrar novos investidores.
    Excluir Investidores: Excluir investidores criados.
    Cadastrar Criptomoedas: Cadastrar novos tipos de criptomoedas.
    Excluir Criptomoedas: Excluir tipos de criptomoedas.
    Ver Saldo de Investidor: Verifica o saldo bancario de um certo investidor.
    Ver Extrato de Investidor: Verifica o extrato bancario de um investidor.
    Atualizar Cotação: Atualize as cotações das criptomoedas.

# Estrutura de Arquivos
O programa usa arquivos de texto para guardar as informações dos usuários. Para cada usuário, um arquivo no formato CPF_(cpf).txt é criado, e conforme o uso de depositos, saques e compras um novo arquivo no formato extrato_(cpf).txt é criado exibindo todos os dados de uso.

Para ter um investidor é preciso criar um, primeiro passo é entrar no Menu Administrador utilizando o login e senha abaixo, em seguida digite 1 para Cadastrar Investidor, o sistema solicitará o nome, cpf e uma senha, tendo assim um acesso pelo menu de Investidor.

    CPF: 54648618823
    Senha: rafis

# Execução
É recomendado utilizar o [replit.](https://replit.com/) como ferramenta. Crie os arquivos com o mesmo nome e coloque exatamente tudo o que está dentro do projeto. Depois, clique nos três pontos ao lado de "Files" e, em seguida, em "Show Hidden Files". Alguns arquivos ocultos irão aparecer. Se não existir o arquivo Makefile, crie um e coloque o código abaixo:


all: admin investidor

admin: admin.c exchange.c
	gcc admin.c exchange.c -o admin

investidor: investidor.c exchange.c
	gcc investidor.c exchange.c -o investidor

clean:
	rm -f admin investidor


Para definir qual programa você quer rodar (Investidor ou Administrador), abra o arquivo .replit e altere a linha do "run", que provavelmente estará como (run = "./main"), para (run = "./admin" ou run = "./investidor"). Agora na linha abaixo, modifique o entrypoint para (entrypoint = "admin.c" ou entrypoint = "investidor.c").


# Integrantes
    Renan Sartori Evangelista  RA: 24.224.004-2
    Rafael Almeida Ferreira    RA: 24.224.013-3 