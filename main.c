#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void adicionar_funcionario(); // átila
void listar_funcionarios();   // marília
void atualizar_funcionario(); // irinaldo;
void excluir_funcionario();   // marília
int last_id();                // átila/marília/irinaldo
int increment_id(int id);     // átila/marília/irinaldo

#define BUFFER_SIZE 1000
#define DATABASE_FILE "database.txt"
#define FUNCIONARIOS_FILE "funcionarios.txt"

int main()
{
    char data[BUFFER_SIZE];
    int acao;

    do
    {
        printf("\n\nRH-cli\n\n");
        printf("1 - Cadastrar Funcionário\n");
        printf("0 - Sair\n");
        scanf("%d", &acao);

        switch (acao)
        {
        case 0:
            printf("\nSaindo...\n");
            return 0;
        case 1:
            fgets(data, BUFFER_SIZE, stdin);
            adicionar_funcionario();
            break;
        default:
            printf("Opção inválida\n");
        }

    } while (acao != acao + 1);

    return 0;
}

void adicionar_funcionario()
{
    char line[BUFFER_SIZE];
    char nome[BUFFER_SIZE];
    char salario[BUFFER_SIZE];
    FILE *file;

    int lastid;
    char id[BUFFER_SIZE];

    lastid = last_id();

    sprintf(id, "%d", lastid++);
    strcat(line, id);
    strcat(line, ";");

    printf("Digite: Nome\n");
    fgets(nome, BUFFER_SIZE, stdin);
    strcat(line, nome);
    strcat(line, ";");

    printf("Digite: Salario\n");
    fgets(salario, BUFFER_SIZE, stdin);
    strcat(line, salario);

    file = fopen(FUNCIONARIOS_FILE, "a");
    fputs(line, file);
    fclose(file);

    increment_id(lastid);

    printf("Usuário criado com successo.\n");
    return;
}

int last_id()
{
    FILE *file;
    int id;
    char id_str[BUFFER_SIZE];

    file = fopen(DATABASE_FILE, "r");
    fgets(id_str, BUFFER_SIZE, file);
    fclose(file);
    id = atoi(id_str);

    if (id == 0)
    {
        id = 1;
    }

    return id;
}

int increment_id(int id)
{
    FILE *file;
    char id_str[BUFFER_SIZE];

    sprintf(id_str, "%d", id);

    file = fopen(DATABASE_FILE, "w");
    fputs(id_str, file);
    fclose(file);

    return id;
}
