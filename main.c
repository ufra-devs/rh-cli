#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

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
        system("clear");
        printf("\n\nRH-cli\n\n");
        printf("1 - Cadastrar Funcionário\n");
        printf("0 - Sair\n");
        scanf("%d", &acao);

        switch (acao)
        {
            case 0:
                printf("\nSaindo...\n");
                sleep(2);
                system("clear");
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
    char record[BUFFER_SIZE];
    char nome[BUFFER_SIZE];
    char matricula[BUFFER_SIZE];
    char email[BUFFER_SIZE];
    char data_de_admissao[BUFFER_SIZE];
    char salario[BUFFER_SIZE];
    FILE *file;

    int new_id;
    char id[BUFFER_SIZE];

    new_id = last_id() + 1;
    sprintf(id, "%d", new_id);

    printf("Digite: Nome\n");
    fgets(nome, BUFFER_SIZE, stdin);
    nome[strcspn(nome, "\n")] = 0;

    printf("Digite: Matrícula\n");
    fgets(matricula, BUFFER_SIZE, stdin);
    matricula[strcspn(matricula, "\n")] = 0;

    printf("Digite: Email\n");
    fgets(email, BUFFER_SIZE, stdin);
    email[strcspn(email, "\n")] = 0;

    printf("Digite: Data de admisssão\n");
    fgets(data_de_admissao, BUFFER_SIZE, stdin);
    data_de_admissao[strcspn(data_de_admissao, "\n")] = 0;

    printf("Digite: Salario\n");
    fgets(salario, BUFFER_SIZE, stdin);

    snprintf(record, BUFFER_SIZE, "%s;%s;%s;%s;%s;%s", id, matricula, nome, email, data_de_admissao, salario);

    file = fopen(FUNCIONARIOS_FILE, "a");
    fputs(record, file);
    fclose(file);

    increment_id(new_id);

    printf("\nUsuário criado com successo.\n");
    sleep(2);
    system("clear");
    printf("\nVoltando para o menu principal...\n");
    sleep(1);

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
