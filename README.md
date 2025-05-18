# Projeto-Parte-4

# Exchange de Criptomoedas em C
Este é um programa de console simples para gerenciar um sistema de troca de criptomoedas. Ele permite que os usuários realizem operações de depósito, saque, compra e venda de criptomoedas, e consulte seus saldos e extratos. O sistema mantém os dados do usuário em arquivos de texto, garantindo que as informações sejam persistidas entre as execuções do programa.

Funcionalidades
O programa permite as seguintes operações:

Login: O usuário faz login com seu CPF e senha.

Consultar Saldo: Verifique o saldo atual em reais e criptomoedas (Bitcoin, Ethereum, Ripple).

Consultar Extrato: Consulte as transações realizadas, como depósitos, saques e compras/vendas de criptomoedas.

Depositar Reais: Deposite reais na conta do usuário.

Sacar Reais: Realize um saque de reais da conta do usuário.

Comprar Criptomoedas: Compre Bitcoin, Ethereum ou Ripple usando reais.

Vender Criptomoedas: Venda suas criptomoedas e converta de volta para reais.

Atualizar Cotação: Atualize as cotações das criptomoedas (com uma variação aleatória de -5% a +5%).

Sair: Encerre o programa.

# Estrutura do Arquivo
O programa usa arquivos de texto para persistir as informações dos usuários. Para cada usuário, um arquivo no formato CPF_(cpf_usuario).txt é criado, onde são armazenados:

CPF do usuário

Saldo em reais

Saldo em Bitcoin

Saldo em Ethereum

Saldo em Ripple

Além disso, o programa mantém um arquivo de extrato extrato_CPF.txt para cada usuário, onde são registradas as transações realizadas.

Usuários: CPF / SENHA

 1234567890  /  12345
 
 9876543211  /  54321

