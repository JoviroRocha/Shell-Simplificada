#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

char HOST[30];
char PRONTO[256];
char SHELL[30];
char data[100];
char path[20];
char *variaveis[100];
int loop;

void config(){
    // Get Hostname
    gethostname(HOST, sizeof(HOST));
    // Get Pronto
    if (getcwd(PRONTO, sizeof(PRONTO)) == NULL){
		printf(ANSI_COLOR_RED "Error while get current directory <getcwd>\n" ANSI_COLOR_RESET);
		strcpy(PRONTO, "/\\");
    }
    // Get Shell name
    strcpy(SHELL,"Simplified Shell");
    // Write it to file
    FILE *config_file = fopen(".meushel.rec","w+");
    if(!config_file){
        printf( ANSI_COLOR_RED "ERROR: The file \".meushell.rec\" could not be found! \n" ANSI_COLOR_RESET);
        exit(0);
    }
    fprintf(config_file,"HOST=%s\nPRONTO=%s\nSHELL=%s\n",HOST,PRONTO,SHELL);
    fclose(config_file);
}

void parser(){
    char * token = strtok(data, " ");
    loop = -1;
    while(token != NULL){
        variaveis[++loop]=malloc(sizeof(token) + 1);
        strcpy(variaveis[loop], token);
        token = strtok (NULL, " ");
    }
    // Adicionar isso a outra funcao específica
    strcpy(path, "/bin/");
    strcat(path, variaveis[0]);
}

void reseta_variaveis(){
    for(int i = 0; i < sizeof(variaveis); i++){
        variaveis[i] = NULL;
    }
}