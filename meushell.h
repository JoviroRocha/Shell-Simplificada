#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define COLOR_GREEN "\x1b[32m"
#define COLOR_RED "\x1b[31m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_RESET "\x1b[0m"

char HOST[30];
char *PRONTO;
char DTA[256];
char SHELL[30];
char data[100];
char data_save[100];
char path[20];
char *variables[0];
char file_path[256];

int loop;
char *variables_amb[20];
char *var_amb_arq[20];
char *result;
char Linha[100];

void get_current_directory()
{
    if (getcwd(DTA, sizeof(DTA)) == NULL)
    {
        printf(COLOR_RED "ERROR: Could not get current directory <getcwd>\n" COLOR_RESET);
        exit(0);
    }
}

void cd()
{
    if (variables[2])
    {
        printf(COLOR_RED "ERROR: Too many arguments for cd\n" COLOR_RESET);
        return;
    }
    if (chdir(variables[1]) != 0)
    {
        printf(COLOR_RED "ERROR: Command cd has failed\n" COLOR_RESET);
        return;
    }
    get_current_directory();
}

void clear()
{
    printf("\033c");
}

int file_exists(const char *filename)
{
    FILE *arquivo;
    if (arquivo = fopen(filename, "r"))
    {
        fclose(arquivo);
        return 1;
    }

    return 0;
}
void config()
{
    // Get Hostname
    gethostname(HOST, sizeof(HOST));
    // Get Pronto
    get_current_directory();
    // sets file_path
    strcpy(file_path, DTA);
    strcat(file_path, "/.meushell.hst");
    // Sets PRONTO
    PRONTO = DTA;
    // Get Shell name
    strcpy(SHELL, "Simplified Shell");
    // Write it to file
    FILE *config_file = fopen(".meushell.rec", "w+");
    if (!config_file)
    {
        printf(COLOR_RED "ERROR: The file \".meushell.rec\" could not be found! \n" COLOR_RESET);
        exit(0);
    }
    fprintf(config_file, "HOST=%s\nPRONTO=%s\nSHELL=%s\nDTA=%s\n", HOST, PRONTO, SHELL, DTA);
    fclose(config_file);
    // Write to the history file
    if (file_exists(".meushell.hst") == 1)
    {

        return;
    }
    else
    {

        FILE *history_file = fopen(".meushell.hst", "w+");
        if (!history_file)
        {
            printf(COLOR_RED "ERROR: The file \".meushell.hst\" could not be found! \n" COLOR_RESET);
            exit(0);
        }
        fprintf(history_file, "1");
        fclose(history_file);
        return;
    }
}

void change_value();

void show_value();

void escreve();

void var_ambiente()
{

    if (strstr(variables[1], "=") != NULL)
    {
        // Atribui valor
        change_value();
    }
    else if (strstr(variables[1], "$") != NULL)
    {
        // Consulta valor
        show_value();
    }
    else
    {
        printf("Variaveis Ambientes do Shell: HOST, PRONTO, SHELL, DTA\n");
    }
}

void change_value()
{
    char *token = strtok(variables[1], "=");
    char aux_amb[10];
    strcpy(aux_amb, token);

    while (token != NULL)
    {
        variables_amb[++loop] = malloc(sizeof(token) + 1);
        strcpy(variables_amb[loop], token);

        token = strtok(NULL, "=");
    }

    FILE *config_file = fopen(".meushel.txt", "rt");
    if (!config_file)
    {
        printf("ERROR: The file \".meushel.txt\" could not be found! \n");
        exit(0);
    }
    int i = 1;
    int loop = -1;
    while (!feof(config_file))
    {

        // Lê uma linha (inclusive com o '\n')
        result = fgets(Linha, 128, config_file); // o 'fgets' lê até 99 caracteres ou até o '\n'

        if (result)
        { // Se foi possível ler
            char *token2 = strtok(Linha, "=");
            loop = -1;
            while (token2 != NULL)
            {
                var_amb_arq[++loop] = malloc(sizeof(token2) + 1);
                strcpy(var_amb_arq[loop], token2);
                token2 = strtok(NULL, "=");
            }

            if (strcmp(var_amb_arq[0], "HOST") == 0 && strcmp(var_amb_arq[0], aux_amb) != 0)
            {
                strcpy(HOST, var_amb_arq[1]);
            }
            if (strcmp(var_amb_arq[0], "PRONTO") == 0 && strcmp(var_amb_arq[0], aux_amb) != 0)
            {
                strcpy(PRONTO, var_amb_arq[1]);
            }
            if (strcmp(var_amb_arq[0], "SHELL") == 0 && strcmp(var_amb_arq[0], aux_amb) != 0)
            {
                strcpy(SHELL, var_amb_arq[1]);
            }
            if (strcmp(var_amb_arq[0], "DTA") == 0 && strcmp(var_amb_arq[0], aux_amb) != 0)
            {
                strcpy(DTA, var_amb_arq[1]);
            }
        }
        i++;
    }
    if (strcmp(variables_amb[2], "HOST") == 0)
    {
        if (strcmp(aux_amb, "HOST") == 0)
        {
            strcpy(HOST, HOST);
        }
        else if (strcmp(aux_amb, "PRONTO") == 0)
        {
            strcpy(PRONTO, HOST);
        }
        else if (strcmp(aux_amb, "SHELL") == 0)
        {
            strcpy(SHELL, HOST);
        }
        else if (strcmp(aux_amb, "DTA") == 0)
        {
            strcpy(DTA, HOST);
        }
    }
    else if (strcmp(variables_amb[2], "PRONTO") == 0)
    {

        if (strcmp(aux_amb, "HOST") == 0)
        {
            strcpy(HOST, PRONTO);
        }
        else if (strcmp(aux_amb, "PRONTO") == 0)
        {
            strcpy(PRONTO, PRONTO);
        }
        else if (strcmp(aux_amb, "SHELL") == 0)
        {
            strcpy(SHELL, PRONTO);
        }
        else if (strcmp(aux_amb, "DTA") == 0)
        {
            strcpy(DTA, PRONTO);
        }
    }
    else if (strcmp(variables_amb[2], "SHELL") == 0)
    {
        if (strcmp(aux_amb, "HOST") == 0)
        {
            strcpy(HOST, SHELL);
        }
        else if (strcmp(aux_amb, "PRONTO") == 0)
        {
            strcpy(PRONTO, SHELL);
        }
        else if (strcmp(aux_amb, "SHELL") == 0)
        {
            strcpy(SHELL, SHELL);
        }
        else if (strcmp(aux_amb, "DTA") == 0)
        {
            strcpy(DTA, SHELL);
        }
    }
    else if (strcmp(variables_amb[2], "DTA") == 0)
    {
        if (strcmp(aux_amb, "HOST") == 0)
        {
            strcpy(HOST, DTA);
        }
        else if (strcmp(aux_amb, "PRONTO") == 0)
        {
            strcpy(PRONTO, DTA);
        }
        else if (strcmp(aux_amb, "SHELL") == 0)
        {
            strcpy(SHELL, DTA);
        }
        else if (strcmp(aux_amb, "DTA") == 0)
        {
            strcpy(DTA, DTA);
        }
    }
    else if (strcmp(aux_amb, "HOST") == 0)
    {
        strcpy(HOST, variables_amb[2]);
    }
    else if (strcmp(aux_amb, "PRONTO") == 0)
    {
        strcpy(PRONTO, variables_amb[2]);
    }
    else if (strcmp(aux_amb, "SHELL") == 0)
    {
        strcpy(SHELL, variables_amb[2]);
    }
    else if (strcmp(aux_amb, "DTA") == 0)
    {
        strcpy(DTA, variables_amb[2]);
    }
    fclose(config_file);
    escreve();
}

void escreve()
{
    FILE *config_file2 = fopen("meushel.txt", "w+");
    if (!config_file2)
    {
        printf("ERROR: The file \".meushel.txt\" could not be found! \n");
        exit(0);
    }
    if (strstr(HOST, "\"") == NULL)
        fprintf(config_file2, "HOST=\"%s\"PRONTO=%sSHELL=%sDTA=%s", HOST, PRONTO, SHELL, DTA);
    else if (strstr(PRONTO, "\"") == NULL)
        fprintf(config_file2, "HOST=%sPRONTO=\"%s\"SHELL=%sDTA=%s", HOST, PRONTO, SHELL, DTA);
    else if (strstr(SHELL, "\"") == NULL)
        fprintf(config_file2, "HOST=%sPRONTO=%sSHELL=\"%s\"DTA=%s", HOST, PRONTO, SHELL, DTA);
    else if (strstr(DTA, "\"") == NULL)
        fprintf(config_file2, "HOST=%sPRONTO=%sSHELL=%sDTA=\"%s\"", HOST, PRONTO, SHELL, DTA);
    else
        fprintf(config_file2, "HOST=%sPRONTO=%sSHELL=%sDTA=\"%s\"", HOST, PRONTO, SHELL, DTA);
    fclose(config_file2);
}

void show_value()
{
    char *token = strtok(variables[1], "$");
    char aux_amb[10];
    strcpy(aux_amb, token);
    FILE *config_file = fopen(".meushel.txt", "rt");
    if (!config_file)
    {
        printf("ERROR: The file \".meushel.txt\" could not be found! \n");
        exit(0);
    }
    int i = 1;
    int loop = -1;
    while (!feof(config_file))
    {
        // Lê uma linha (inclusive com o '\n')
        result = fgets(Linha, 128, config_file); // o 'fgets' lê até 99 caracteres ou até o '\n'

        if (result)
        { // Se foi possível ler
            char *token2 = strtok(Linha, "=");
            loop = -1;
            while (token2 != NULL)
            {
                var_amb_arq[++loop] = malloc(sizeof(token2) + 1);
                strcpy(var_amb_arq[loop], token2);
                token2 = strtok(NULL, "=");
            }

            if (strcmp(var_amb_arq[0], aux_amb) == 0)
            {

                printf("%s = %s\n", var_amb_arq[0], var_amb_arq[1]);
                break;
            }
        }
        i++;
    }

    fclose(config_file);
}

void add_history()
{
    FILE *history_file = fopen(".meushell.hst", "r+");
    int loop;
    loop = fscanf(history_file, "%d", &loop);
    printf("%d", loop);
    fclose(history_file);
}

void parser()
{
    char *token = strtok(data, " ");
    int loop = -1;
    while (token != NULL)
    {
        variables[++loop] = malloc(sizeof(token) + 1);
        strcpy(variables[loop], token);
        token = strtok(NULL, " ");
    }
    // Adicionar isso a outra funcao específica
    strcpy(path, "/usr/bin/");
    strcat(path, variables[0]);
}

void reset_variables()
{
    for (int i = 0; variables[i] != NULL; i++)
    {
        variables[i] = NULL;
    }
}
