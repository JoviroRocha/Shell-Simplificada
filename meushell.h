#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define COLOR_GREEN "\x1b[32m"
#define COLOR_RED "\x1b[31m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_RESET "\x1b[0m"

char HOST[30];
char PRONTO[256];
char DTA[256];
char SHELL[30];
char data[100];
char data_save[100];
char path[20];
char *variables[0];
int loop;
char file_path[256];
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
    strcpy(PRONTO, DTA);
    // Get Shell name
    strcpy(SHELL, "Simplified Shell");
    // Write it to file
    FILE *config_file = fopen(".meushel.rec", "w+");
    if (!config_file)
    {
        printf(COLOR_RED "ERROR: The file \".meushell.rec\" could not be found! \n" COLOR_RESET);
        exit(0);
    }
    fprintf(config_file, "HOST=%s\nPRONTO=%s\nSHELL=%s\nDTA=%s\n", HOST, PRONTO, SHELL, DTA);
    fclose(config_file);
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

void *add_history()
{
    char LINE[100];
    char *result;
    FILE *read = fopen(file_path, "r");
    FILE *history_file = fopen(file_path, "a+");
    if (!history_file)
    {
        printf(COLOR_RED "ERROR: The file \".meushell.hst\" could not be found! \n" COLOR_RESET);
        exit(0);
    }
    //
    fseek(read, -1, SEEK_END);

    // Volta para o início da penúltima linha
    while (fgetc(read) != '\n')
    {
        fseek(read, -2, SEEK_CUR);
    }

    // Lê a penúltima linha
    fgets(LINE, sizeof(LINE), read);

    printf("Penúltima linha: %s", LINE);
    //
    fprintf(history_file, "1234 %s \n", data_save);
    fclose(history_file);
    pthread_exit(0);
}

void parser()
{
    char *token = strtok(data, " ");
    loop = -1;
    while (token != NULL)
    {
        variables[++loop] = malloc(sizeof(token) + 1);
        strcpy(variables[loop], token);
        token = strtok(NULL, " ");
    }
    // Adicionar isso a outra funcao específica
    strcpy(path, "/bin/");
    strcat(path, variables[0]);
}

void reset_variables()
{
    int i;
    for (i = 0; variables[i] != NULL; i++)
    {
        variables[i] = NULL;
    }
}
