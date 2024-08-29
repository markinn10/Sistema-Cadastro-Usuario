#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

typedef struct {
    int dia;
    int mes;
    int ano;
} Nascimento;

typedef struct {
    char nome[256];
    char CPF[12]; 
    char address[256];
    Nascimento nascimento;
} Pessoa;

void exibirMenu(int size, Pessoa *pessoa);
void cadastrarUsuarios(int size, Pessoa *pessoa);
void exibirDados(int size, Pessoa *pessoa);
void alterarDados(int size, Pessoa *pessoa, int index);
void deletarUsuario(int *size, Pessoa **pessoa, int index);
void cadastrarNovoUsuario(int *size, Pessoa **pessoa);
void voltarAoMenu(int size, Pessoa *pessoa);
void exibirOpcoes(int size, Pessoa *pessoa);
int calcularIdade(int dia, int mes, int ano);
void encerrarPrograma();
void limparTela();

int main(void) {
    setlocale(LC_ALL, "Portuguese");
    system("color 0A");
    system("title Sistema Cadastro de Usuário");

    printf("Sistema Cadastro de Usuário\n\n");

    int size;

    printf("Digite a quantidade de pessoas que você deseja cadastrar: ");
    while (scanf("%d", &size) != 1 || size < 1 || size > 100) {
        printf("Quantidade inválida. Por favor, digite um número inteiro positivo entre 1 e 100: ");
        while (getchar() != '\n');
    }

    Pessoa *pessoa = (Pessoa *)malloc(size * sizeof(Pessoa));
    if (pessoa == NULL) {
        limparTela();
        printf("Erro ao alocar memória. Encerrando o programa...\n\n");
        exit(1);
    }

    cadastrarUsuarios(size, pessoa);
    exibirMenu(size, pessoa);

    free(pessoa);
    return 0;
}

void exibirMenu(int size, Pessoa *pessoa) {
    printf("--------Sistema Cadastro de Usuário-------\n\n");

    int input;

    printf("1. Exibir os dados\n2. Alterar dados cadastrados de um usuário\n3. Deletar usuário cadastrado\n4. Cadastrar novo usuário\n5. Sair do programa\n\n");
    printf("Escolha uma opção: ");
    scanf("%d", &input);

    while (input < 1 || input > 5) {
        printf("Opção inválida, tente novamente: ");
        scanf("%d", &input);
    }

    switch (input) {
    case 1:
        exibirDados(size, pessoa);
        exibirOpcoes(size, pessoa);
        break;
    case 2: {
        int index;
        exibirDados(size, pessoa);

        printf("Qual usuário você deseja alterar (1 a %d): ", size);
        scanf("%d", &index);

        while (index < 1 || index > size) {
            printf("Usuário inválido, tente novamente (Digite 0 para voltar ao menu): ");
            scanf("%d", &index);
            if (index == 0)
                voltarAoMenu(size, pessoa);
        }

        printf("\n");
        alterarDados(size, pessoa, index);
        break;
    }
    case 3: {
        int index;
        exibirDados(size, pessoa);

        printf("Qual usuário você deseja deletar (1 a %d): ", size);
        scanf("%d", &index);

        while (index < 1 || index > size) {
            printf("Usuário inválido, tente novamente (Digite 0 para voltar ao menu): ");
            scanf("%d", &index);
            if (index == 0)
                voltarAoMenu(size, pessoa);
        }

        deletarUsuario(&size, &pessoa, index);
        break;
    }
    case 4:
        cadastrarNovoUsuario(&size, &pessoa);
        break;
    case 5:
        encerrarPrograma();
        break;
    }
}

void exibirOpcoes(int size, Pessoa *pessoa) {
    int input;

    printf("1. Voltar ao menu\n2. Encerrar o programa\n\n");
    printf("Escolha uma opção: ");
    scanf("%d", &input);

    while (input < 1 || input > 2) {
        printf("Opção inválida, tente novamente: ");
        scanf("%d", &input);
    }

    switch (input) {
    case 1:
        voltarAoMenu(size, pessoa);
        break;
    case 2:
        encerrarPrograma();
        break;
    }
}

void cadastrarUsuarios(int size, Pessoa *pessoa) {
    for (int i = 0; i < size; i++) {
        printf("\n");

        // Nome:
        printf("Digite o nome do %dº usuário: ", i + 1);
        while (getchar() != '\n');
        scanf("%[^\n]s", pessoa[i].nome);

        // Data de nascimento:
        printf("Digite a data de nascimento de %s (DD/MM/AAAA): ", pessoa[i].nome);
        scanf("%d/%d/%d", &pessoa[i].nascimento.dia, &pessoa[i].nascimento.mes, &pessoa[i].nascimento.ano);

        while (pessoa[i].nascimento.dia < 1 || pessoa[i].nascimento.dia > 31 || pessoa[i].nascimento.mes < 1 || pessoa[i].nascimento.mes > 12 || pessoa[i].nascimento.ano < 1900 || pessoa[i].nascimento.ano > 2024) {
            printf("Data de nascimento inválida, tente novamente: ");
            scanf("%d/%d/%d", &pessoa[i].nascimento.dia, &pessoa[i].nascimento.mes, &pessoa[i].nascimento.ano);
        }

        // CPF:
        printf("Digite o CPF de %s (Apenas números): ", pessoa[i].nome);
        while (getchar() != '\n');
        scanf("%11s", pessoa[i].CPF);

        while (strlen(pessoa[i].CPF) != 11) {
            printf("CPF inválido, tente novamente: ");
            while (getchar() != '\n');
            scanf("%11s", pessoa[i].CPF);
        }

        // Endereço:
        printf("Digite o endereço de %s: ", pessoa[i].nome);
        while (getchar() != '\n');
        scanf("%[^\n]s", pessoa[i].address);
    }

    voltarAoMenu(size, pessoa);
}

void cadastrarNovoUsuario(int *size, Pessoa **pessoa) {
    *size += 1;

    Pessoa *temp = (Pessoa *)realloc(*pessoa, *size * sizeof(Pessoa));
    if (temp == NULL) {
        limparTela();
        printf("Erro ao alocar memória. Encerrando o programa...\n\n");
        exit(1);
    }
    *pessoa = temp;

    printf("\n");

    // Nome:
    printf("Digite o nome do novo usuário: ");
    while (getchar() != '\n');
    scanf("%[^\n]s", (*pessoa)[*size - 1].nome);

    // Data de nascimento:
    printf("Digite a data de nascimento de %s (DD/MM/AAAA): ", (*pessoa)[*size - 1].nome);
    scanf("%d/%d/%d", &(*pessoa)[*size - 1].nascimento.dia, &(*pessoa)[*size - 1].nascimento.mes, &(*pessoa)[*size - 1].nascimento.ano);

    while ((*pessoa)[*size - 1].nascimento.dia < 1 || (*pessoa)[*size - 1].nascimento.dia > 31 || (*pessoa)[*size - 1].nascimento.mes < 1 || (*pessoa)[*size - 1].nascimento.mes > 12 || (*pessoa)[*size - 1].nascimento.ano < 1900 || (*pessoa)[*size - 1].nascimento.ano > 2024) {
        printf("Data de nascimento inválida, tente novamente: ");
        scanf("%d/%d/%d", &(*pessoa)[*size - 1].nascimento.dia, &(*pessoa)[*size - 1].nascimento.mes, &(*pessoa)[*size - 1].nascimento.ano);
    }

    // CPF:
    printf("Digite o CPF de %s (Apenas números): ", (*pessoa)[*size - 1].nome);
    while (getchar() != '\n');
    scanf("%11s", (*pessoa)[*size - 1].CPF);

    while (strlen((*pessoa)[*size - 1].CPF) != 11) {
        printf("CPF inválido, tente novamente: ");
        while (getchar() != '\n');
        scanf("%11s", (*pessoa)[*size - 1].CPF);
    }

    // Endereço
    printf("Digite o endereço de %s: ", (*pessoa)[*size - 1].nome);
    while (getchar() != '\n');
    scanf("%[^\n]s", (*pessoa)[*size - 1].address);

    voltarAoMenu(*size, *pessoa);
}

void exibirDados(int size, Pessoa *pessoa) {
    limparTela();

    for (int i = 0; i < size; i++) {
        printf("Usuário nº %d:\n", i + 1);
        printf("Nome: %s\n", pessoa[i].nome);
        printf("Data de Nascimento: %02d/%02d/%04d (Idade: %d anos)\n", pessoa[i].nascimento.dia, pessoa[i].nascimento.mes, pessoa[i].nascimento.ano, calcularIdade(pessoa[i].nascimento.dia, pessoa[i].nascimento.mes, pessoa[i].nascimento.ano));
        printf("CPF: %s\n", pessoa[i].CPF);
        printf("Endereço: %s\n", pessoa[i].address);
        printf("\n");
    }
}

void alterarDados(int size, Pessoa *pessoa, int index) {
    index--;

    printf("1. Alterar nome\n2. Alterar data de nascimento\n3. Alterar CPF\n4. Alterar endereço\n5. Voltar ao menu\n\n");
    printf("Escolha uma opção: ");

    int input;
    scanf("%d", &input);

    while (input < 1 || input > 5) {
        printf("Opção inválida, tente novamente: ");
        scanf("%d", &input);
    }

    switch (input) {
    case 1:
        printf("Digite o novo nome de %s: ", pessoa[index].nome);
        while (getchar() != '\n');
        scanf("%[^\n]s", pessoa[index].nome);
        break;
    case 2:
        printf("Digite a nova data de nascimento de %s (DD/MM/AAAA): ", pessoa[index].nome);
        scanf("%d/%d/%d", &pessoa[index].nascimento.dia, &pessoa[index].nascimento.mes, &pessoa[index].nascimento.ano);

        while (pessoa[index].nascimento.dia < 1 || pessoa[index].nascimento.dia > 31 || pessoa[index].nascimento.mes < 1 || pessoa[index].nascimento.mes > 12 || pessoa[index].nascimento.ano < 1900 || pessoa[index].nascimento.ano > 2024) {
            printf("Data de nascimento inválida, tente novamente: ");
            scanf("%d/%d/%d", &pessoa[index].nascimento.dia, &pessoa[index].nascimento.mes, &pessoa[index].nascimento.ano);
        }
        break;
    case 3:
        printf("Digite o novo CPF de %s (Apenas números): ", pessoa[index].nome);
        while (getchar() != '\n');
        scanf("%11s", pessoa[index].CPF);

        while (strlen(pessoa[index].CPF) != 11) {
            printf("CPF inválido, tente novamente: ");
            while (getchar() != '\n');
            scanf("%11s", pessoa[index].CPF);
        }
        break;
    case 4:
        printf("Digite o novo endereço de %s: ", pessoa[index].nome);
        while (getchar() != '\n');
        scanf("%[^\n]s", pessoa[index].address);
        break;
    case 5:
        voltarAoMenu(size, pessoa);
        break;
    }

    printf("\n");

    exibirDados(size, pessoa);
    exibirOpcoes(size, pessoa);
}

void deletarUsuario(int *size, Pessoa **pessoa, int index) {
    index--;

    for (int i = index; i < *size - 1; i++) {
        (*pessoa)[i] = (*pessoa)[i + 1];
    }

    *size -= 1;
    Pessoa *temp = (Pessoa *)realloc(*pessoa, *size * sizeof(Pessoa));
    if (temp != NULL) {
        *pessoa = temp;
    }

    printf("Usuário deletado com sucesso.\n\n");

    exibirDados(*size, *pessoa);
    exibirOpcoes(*size, *pessoa);
}

int calcularIdade(int dia, int mes, int ano) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int idade = tm.tm_year + 1900 - ano;

    if (mes > tm.tm_mon + 1 || (mes == tm.tm_mon + 1 && dia > tm.tm_mday)) {
        idade--;
    }

    return idade;
}

void voltarAoMenu(int size, Pessoa *pessoa) {
    limparTela();
    exibirMenu(size, pessoa);
}

void encerrarPrograma() {
    limparTela();
    printf("Encerrando o programa...\n\n");
    exit(0);
}

void limparTela() {
    system("cls||clear");
}
