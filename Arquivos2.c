#include <stdio.h>
#include <string.h>

#define MAX 100

// ----------------------------
// ESTRUTURA DE CONTA
// ----------------------------
typedef struct {
    int numero;
    char nome[50];
    char cpf[15];
    char telefone[20];
    float saldo;
} Conta;

// ----------------------------
// FUNÇÃO (a): BUSCA
// ----------------------------
int buscaConta(Conta cadastro[], int qtd, int numeroProcurado) {
    if (qtd == 0)
        return -1;  // cadastro vazio
    
    for (int i = 0; i < qtd; i++) {
        if (cadastro[i].numero == numeroProcurado)
            return i;   // posição encontrada
    }
    return -2;  // não encontrado
}

// ----------------------------
// PROCEDIMENTO (b): CADASTRAR NOVA CONTA
// ----------------------------
void cadastrarConta(Conta cadastro[], int *qtd, int numero) {
    if (*qtd >= MAX) {
        printf("Cadastro cheio!\n");
        return;
    }

    int pos = buscaConta(cadastro, *qtd, numero);

    if (pos >= 0) {
        printf("Conta ja cadastrada! Nao e possivel repetir numero.\n");
        return;
    }

    printf("Digite o nome: ");
    scanf(" %[^\n]", cadastro[*qtd].nome);

    printf("Digite o CPF: ");
    scanf(" %[^\n]", cadastro[*qtd].cpf);

    printf("Digite o telefone: ");
    scanf(" %[^\n]", cadastro[*qtd].telefone);

    cadastro[*qtd].numero = numero;
    cadastro[*qtd].saldo = 0.0;

    (*qtd)++;

    printf("Conta cadastrada com sucesso!\n");
}

// ----------------------------
// PROCEDIMENTO (c): CONSULTAR SALDO
// ----------------------------
void consultarSaldo(Conta cadastro[], int qtd, int numero) {
    int pos = buscaConta(cadastro, qtd, numero);

    if (pos >= 0) {
        printf("Saldo da conta %d: R$ %.2f\n", numero, cadastro[pos].saldo);
    } else {
        printf("Conta nao encontrada!\n");
    }
}

// ----------------------------
// PROCEDIMENTO (d): DEPOSITO
// ----------------------------
void depositar(Conta cadastro[], int qtd, int numero) {
    int pos = buscaConta(cadastro, qtd, numero);

    if (pos < 0) {
        printf("Conta nao encontrada!\n");
        return;
    }

    float valor;
    printf("Digite o valor do deposito: ");
    scanf("%f", &valor);

    cadastro[pos].saldo += valor;

    printf("Deposito realizado! Novo saldo: R$ %.2f\n", cadastro[pos].saldo);
}

// ----------------------------
// PROCEDIMENTO (e): SAQUE
// ----------------------------
void sacar(Conta cadastro[], int qtd, int numero) {
    int pos = buscaConta(cadastro, qtd, numero);

    if (pos < 0) {
        printf("Conta nao encontrada!\n");
        return;
    }

    float valor;
    printf("Digite o valor do saque: ");
    scanf("%f", &valor);

    if (valor > cadastro[pos].saldo) {
        printf("Saldo insuficiente!\n");
        return;
    }

    cadastro[pos].saldo -= valor;

    printf("Saque realizado! Novo saldo: R$ %.2f\n", cadastro[pos].saldo);
}

// ----------------------------
// PROCEDIMENTO (f): LISTAR CONTAS
// ----------------------------
void listarContas(Conta cadastro[], int qtd) {
    if (qtd == 0) {
        printf("Nenhuma conta cadastrada.\n");
        return;
    }

    for (int i = 0; i < qtd; i++) {
        printf("\nConta %d\n", cadastro[i].numero);
        printf("Nome: %s\n", cadastro[i].nome);
        printf("Telefone: %s\n", cadastro[i].telefone);
    }
}

// ----------------------------
// PROGRAMA PRINCIPAL (MENU)
// ----------------------------
int main() {
    Conta corrente[MAX], poupanca[MAX];
    int qtdCorr = 0, qtdPoup = 0;

    int opcao, tipo, numero;

    do {
        printf("\n=== BANCO DINHEIRO CERTO ===\n");
        printf("1 - Cadastrar conta\n");
        printf("2 - Consultar saldo\n");
        printf("3 - Depositar\n");
        printf("4 - Sacar\n");
        printf("5 - Listar contas\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 0) break;

        printf("1 - Conta Corrente\n2 - Conta Poupanca\nEscolha o tipo: ");
        scanf("%d", &tipo);

        Conta *cadastro;
        int *qtd;

        if (tipo == 1) {
            cadastro = corrente;
            qtd = &qtdCorr;
        } else {
            cadastro = poupanca;
            qtd = &qtdPoup;
        }

        switch (opcao) {
            case 1:
                printf("Numero da nova conta: ");
                scanf("%d", &numero);
                cadastrarConta(cadastro, qtd, numero);
                break;

            case 2:
                printf("Numero da conta: ");
                scanf("%d", &numero);
                consultarSaldo(cadastro, *qtd, numero);
                break;

            case 3:
                printf("Numero da conta para deposito: ");
                scanf("%d", &numero);
                depositar(cadastro, *qtd, numero);
                break;

            case 4:
                printf("Numero da conta para saque: ");
                scanf("%d", &numero);
                sacar(cadastro, *qtd, numero);
                break;

            case 5:
                listarContas(cadastro, *qtd);
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
