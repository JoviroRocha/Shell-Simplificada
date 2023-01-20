#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

#define COLOR_GREEN "\x1b[32m"
#define COLOR_RED "\x1b[31m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_RESET "\x1b[0m"

char HOST[30];
char *PRONTO;
char PRONTO_REF[256];
char DTA[256];
char SHELL[30];
char data[100];
char data_save[100];
char path[20];
char file_path[256];
int loop;
char *result;
char Linha[100];
char aux_meushell[256];
char aux_const[256];

void escreve();

void help()
{

    printf(COLOR_GREEN "BEM VINDO A CENTRAL DE AJUDA SHELL-SIMPLIFICADA\n");
    printf(COLOR_GREEN "\nCOMANDOS INTERNOS\n");
    printf(COLOR_GREEN " --VARIAVEIS AMBIENTE--\n");
    printf(COLOR_BLUE "\n   - \"amb\" lista as todas as variaveis ambiente da Shell-Simplificada\n");
    printf(COLOR_BLUE "\n   - \"amb $VAR\" retorna o valor atual da VAR\n");
    printf(COLOR_BLUE "\n   - \"amb VAR=<valor>\" uma variavel ambiente recebera o valor digitado\n");
    printf(COLOR_BLUE "       - Observação: <valor> não pode ser separado por espaço, exemplos de uso: VAR=Ola-Mundo, VAR=Ola\n");
    printf(COLOR_BLUE "       - Observação 2: <valor> pode ser outra variavel ambiente, exemplo: HOST=PRONTO\n");
    printf(COLOR_BLUE "           - Observação 2.1: quando atribuir o valor de uma variavel a outra será apenas o valor da variavel sem adicionais.\"\n");
    printf(COLOR_GREEN " --COMANDOS BASICOS DA SHELL-SIMPLIFICADA--\n");
    printf(COLOR_BLUE "\n   - \"cd <diretorio>\" muda do diretório atual para <diretório> e o valor da variável DTA é alterado.\n");
    printf(COLOR_BLUE "\n   - \"clear\" limpa a tela\n");
    printf(COLOR_BLUE "\n   - \"history\" mostra os comandos já executados pelo usuário\n");
    printf(COLOR_BLUE "\n   - \"exit\" Sai da SHELL-SIMPLIFICADA\n");
    printf(COLOR_GREEN "\nCOMANDOS EXTERNOS\n");
    printf(COLOR_BLUE "   - \"Observação: ao utilizar o comando externo hostname, o valor da VAR HOST será alterado.\n");
    printf(COLOR_GREEN "\nOUTRAS FUNCIONALIDADES\n");
    printf(COLOR_BLUE "\n   - Sempre que o usuario digitar um comando será armazenado em um historico.\n");
    printf(COLOR_BLUE "       - Observação: Se o usuario digitar seguidamente o mesmo comando, só sera armazenado uma vez.\n");
    printf(COLOR_BLUE "\n   - Apos utilizar a SHELL-SIMPLIFICADA uma vez e ter comandos salvos no historico, \n     o usuario podera acessar esses comandos por meio do comando !<numero>.\n");
    printf(COLOR_BLUE "\n  - Existe a capacidade de executar comandos a partir de um arquivo fornecido como entrada, \n    Ou seja, ler comandos a partir de um arquivo e executá-los.\n");
    printf(COLOR_BLUE "       - Observação: Os comandos dentro do arquivo devem estar separados por um espaço.\n");
}

void get_current_directory()
{
    if (getcwd(DTA, sizeof(DTA)) == NULL)
    {
        printf(COLOR_RED "ERROR: Could not get current directory <getcwd>\n" COLOR_RESET);
        exit(0);
    }
}

void cd(char *variables[])
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
    // sets aux_const path
    strcpy(aux_const, DTA);
    strcat(aux_const, "/.constants.txt");
    // sets aux_meushell path variaveis ambiente
    strcpy(aux_meushell, DTA);
    strcat(aux_meushell, "/.meushell.txt");
    // sets file_path
    strcpy(file_path, DTA);
    strcat(file_path, "/.meushell.hst");
    // Sets PRONTO
    PRONTO = DTA;
    // Get Shell name
    strcpy(SHELL, "Simplified-Shell");
    // Write constants file
    if(file_exists(aux_const) == 0)
    {
        printf(COLOR_RED "The constans file could not be found!\n" COLOR_RESET);
        exit(0);
    }
    // Write it to file
    FILE *config_file = fopen(aux_meushell, "w+");
    if (!config_file)
    {
        printf(COLOR_RED "ERROR: The file \".meushell.txt\" could not be found! \n" COLOR_RESET);
        exit(0);
    }
    fprintf(config_file, "HOST=%s\nPRONTO=%s\nSHELL=%s\nDTA=%s\n", HOST, PRONTO, SHELL, DTA);
    fclose(config_file);
    // Write to the history file
    if (file_exists(file_path) == 1)
    {

        return;
    }
    else
    {
        FILE *history_file = fopen(file_path, "w+");
        if (!history_file)
        {
            printf(COLOR_RED "ERROR: The file \".meushell.hst\" could not be found! \n" COLOR_RESET);
            exit(0);
        }
        fclose(history_file);
        return;
    }
}

void escreve()
{
    FILE *config_file2 = fopen(aux_meushell, "w+");
    if (!config_file2)
    {
        printf(COLOR_RED "ERROR: The file \".meushell.txt\" could not be found! \n" COLOR_RESET);
        exit(0);
    }
    if (strstr(HOST, "\"") == NULL)
        fprintf(config_file2, "HOST=%s\nPRONTO=%s\nSHELL=%s\nDTA=%s", HOST, PRONTO, SHELL, DTA);
    else if (strstr(PRONTO, "\"") == NULL)
        fprintf(config_file2, "HOST=%s\nPRONTO=%s\nSHELL=%s\nDTA=%s", HOST, PRONTO, SHELL, DTA);
    else if (strstr(SHELL, "\"") == NULL)
        fprintf(config_file2, "HOST=%s\nPRONTO=%s\nSHELL=%s\nDTA=%s", HOST, PRONTO, SHELL, DTA);
    else if (strstr(DTA, "\"") == NULL)
        fprintf(config_file2, "HOST=%s\nPRONTO=%s\nSHELL=%s\nDTA=%s", HOST, PRONTO, SHELL, DTA);
    else
        fprintf(config_file2, "HOST=%s\nPRONTO=%s\nSHELL=%s\nDTA=%s", HOST, PRONTO, SHELL, DTA);
    fclose(config_file2);
}

void change_value(char var_amb_arq[][256], char variables_amb[][256], char *variables[])
{
    char *token = strtok(variables[1], "=");
    int loop = -1;
    while (token != NULL)
    {
        variables_amb[++loop];
        strcpy(variables_amb[loop], token);

        token = strtok(NULL, "=");
    }

    FILE *config_file = fopen(aux_meushell, "rt");
    if (!config_file)
    {
        printf(COLOR_RED "ERROR: The file \".meushell.txt\" could not be found! \n" COLOR_RESET);
        exit(0);
    }
    int i = 1;
    loop = -1;
    while (!feof(config_file))
    {

        // Lê uma linha (inclusive com o '\n')
        result = fgets(Linha, 99, config_file); // o 'fgets' lê até 99 caracteres ou até o '\n'

        if (result)
        { // Se foi possível ler
            char *token2 = strtok(Linha, "=");
            loop = -1;
            while (token2 != NULL)
            {

                var_amb_arq[++loop];
                strcpy(var_amb_arq[loop], token2);

                token2 = strtok(NULL, "=");
            }
        }

        if (strcmp(var_amb_arq[0], variables_amb[0]) == 0)
            break;
        i++;
    }
    if (strcmp(variables_amb[1], "HOST") == 0)
    {
        if (strcmp(var_amb_arq[0], "HOST") == 0)
        {
        }
        else if (strcmp(var_amb_arq[0], "PRONTO") == 0)
        {
            strcpy(PRONTO_REF, HOST);
            PRONTO = PRONTO_REF;
        }
        else if (strcmp(var_amb_arq[0], "SHELL") == 0)
        {
            strcpy(SHELL, HOST);
        }
        else if (strcmp(var_amb_arq[0], "DTA") == 0)
        {
            strcpy(DTA, HOST);
        }
    }
    else if (strcmp(variables_amb[1], "PRONTO") == 0)
    {

        if (strcmp(var_amb_arq[0], "HOST") == 0)
        {
            strcpy(HOST, PRONTO);
        }
        else if (strcmp(var_amb_arq[0], "PRONTO") == 0)
        {
        }
        else if (strcmp(var_amb_arq[0], "SHELL") == 0)
        {
            strcpy(SHELL, PRONTO);
        }
        else if (strcmp(var_amb_arq[0], "DTA") == 0)
        {
            strcpy(DTA, PRONTO);
        }
    }
    else if (strcmp(variables_amb[1], "SHELL") == 0)
    {
        if (strcmp(var_amb_arq[0], "HOST") == 0)
        {
            strcpy(HOST, SHELL);
        }
        else if (strcmp(var_amb_arq[0], "PRONTO") == 0)
        {
            strcpy(PRONTO_REF, SHELL);
            PRONTO = PRONTO_REF;
        }
        else if (strcmp(var_amb_arq[0], "SHELL") == 0)
        {
            strcpy(SHELL, SHELL);
        }
        else if (strcmp(var_amb_arq[0], "DTA") == 0)
        {
            strcpy(DTA, SHELL);
        }
    }
    else if (strcmp(variables_amb[1], "DTA") == 0)
    {
        if (strcmp(var_amb_arq[0], "HOST") == 0)
        {
            strcpy(HOST, DTA);
        }
        else if (strcmp(var_amb_arq[0], "PRONTO") == 0)
        {
            PRONTO = DTA;
        }
        else if (strcmp(var_amb_arq[0], "SHELL") == 0)
        {
            strcpy(SHELL, DTA);
        }
        else if (strcmp(var_amb_arq[0], "DTA") == 0)
        {
            strcpy(DTA, DTA);
        }
    }
    else if (strcmp(var_amb_arq[0], "HOST") == 0)
    {

        strcpy(HOST, variables_amb[1]);
    }
    else if (strcmp(var_amb_arq[0], "PRONTO") == 0)
    {

        strcpy(PRONTO_REF, variables_amb[1]);
        PRONTO = PRONTO_REF;
    }
    else if (strcmp(var_amb_arq[0], "SHELL") == 0)
    {

        strcpy(SHELL, variables_amb[1]);
    }
    else if (strcmp(var_amb_arq[0], "DTA") == 0)
    {

        strcpy(DTA, variables_amb[1]);
    }

    fclose(config_file);
    escreve();
}

void show_value(char var_amb_arq[][256], char *variables[])
{
    char *token = strtok(variables[1], "$");
    char aux_amb[10];
    strcpy(aux_amb, token);
    FILE *config_file = fopen(aux_meushell, "rt");
    if (!config_file)
    {
        printf(COLOR_RED "ERROR: The file \".meushell.txt\" could not be found! \n" COLOR_RESET);
        exit(0);
    }
    int i = 1;
    int loop = -1;
    while (!feof(config_file))
    {
        // Lê uma linha (inclusive com o '\n')
        result = fgets(Linha, 99, config_file); // o 'fgets' lê até 99 caracteres ou até o '\n'

        if (result)
        { // Se foi possível ler
            char *token2 = strtok(Linha, "=");
            loop = -1;
            while (token2 != NULL)
            {
                var_amb_arq[++loop];
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

void var_ambiente(char *variables[], char var_amb_arq[][256], char variables_amb[][256])
{

    if (variables[1] == NULL)
    {
        printf(COLOR_GREEN "Variaveis Ambientes do Shell: HOST, PRONTO, SHELL, DTA\n" COLOR_RESET);
        return;
    }
    else if (strstr(variables[1], "=") != NULL)
    {
        // Atribui valor
        change_value(var_amb_arq, variables_amb, variables);
    }
    else if (strstr(variables[1], "$") != NULL)
    {
        ;
        // Consulta valor
        show_value(var_amb_arq, variables);
    }
}

int find_history()
{
    FILE *history_file = fopen(file_path, "r");
    if(!history_file){
        printf(COLOR_RED "ERROR: The file \".meushell.hst\" could not be found! \n" COLOR_RESET);
        exit(0);
    }
    while(!feof(history_file)){
        fgets(Linha, 99, history_file);
    } 
    int len = strlen(Linha);
    Linha[--len] = 0;
    fclose(history_file);
    if(strcmp(Linha, data) == 0){
        return 1;
    }
    return 0;
}

void add_history() 
{
    int position;
    if(find_history() == 1) return;
    FILE *const_file = fopen(aux_const, "r");
    fscanf(const_file, "%i", &position);
    fclose(const_file);
    FILE *history_file = fopen(file_path, "a");
    if(!history_file){
        printf(COLOR_RED "ERROR: The file \".meushell.hst\" could not be found! \n" COLOR_RESET);
        exit(0);
    }
    fprintf(history_file,"%d %s\n", position + 1, data);
    fclose(history_file);
    FILE *new_const = fopen(aux_const, "w");
    fprintf(new_const, "%d", position + 1);
    fclose(new_const);
    return;
}

void execute_history(char * variables[])
{
    int tamanho = strlen(variables[0]);
    if(! variables[0][1]){
        printf(COLOR_RED "The command is empty!\n" COLOR_RESET);
        return;
    }
    else{
        variables[0][0] = "0";
    }
    for(int x = 0; x < tamanho - 1; x ++)
    {
        if(isdigit(variables[0][x]) && isdigit(variables[0][x+1]))
        {
            variables[0][x] = variables[0][x+1];
            printf("!!==%s\n",variables[0]);
        }
        else
        {
            printf(COLOR_RED "The value must be an integer\n" COLOR_RESET);
            return;
        }
    }
    variables[0][tamanho] = "\0";
    return;
}

void print_history(){
    char c = ' ';
    FILE *history_file = fopen(file_path, "r");
    if(!history_file){
        printf(COLOR_RED "ERROR: The file \".meushell.hst\" could not be found! \n" COLOR_RESET);
        exit(0);
    }
    c = fgetc(history_file);
    while (c != EOF)
    {
        printf (COLOR_GREEN "%c", c);
        c = fgetc(history_file);
    }
    return;
}

void parser(char *variables[])
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

void reset_variables(char *variables[])
{
    for (int i = 0; variables[i] != NULL; i++)
    {
        variables[i] = NULL;
    }
}
