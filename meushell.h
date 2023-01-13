#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define COLOR_GREEN   "\x1b[32m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_RESET   "\x1b[0m"

char HOST[30];
char *PRONTO;
char DTA[256];
char SHELL[30];
char data[100];
char data_save[100];
char path[20];
char *variables[0];
int loop;
char file_path[256];

void get_current_directory(){
    if (getcwd(DTA, sizeof(DTA)) == NULL){
		printf(COLOR_RED "ERROR: Could not get current directory <getcwd>\n" COLOR_RESET);
		exit(0);
    }
}

void cd(){
    if(variables[2]){
        printf(COLOR_RED "ERROR: Too many arguments for cd\n" COLOR_RESET);
        return;
    }
    if (chdir(variables[1]) != 0) {
        printf(COLOR_RED "ERROR: Command cd has failed\n" COLOR_RESET);
        return;
    }
    get_current_directory();
}

void clear(){
    printf("\033c");
}

void config(){
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
    strcpy(SHELL,"Simplified Shell");
    // Write it to file
    FILE *config_file = fopen(".meushel.rec","w+");
    if(!config_file){
        printf( COLOR_RED "ERROR: The file \".meushell.rec\" could not be found! \n" COLOR_RESET);
        exit(0);
    }
    fprintf(config_file,"HOST=%s\nPRONTO=%s\nSHELL=%s\nDTA=%s\n",HOST,PRONTO,SHELL,DTA);
    fclose(config_file);
}

void* add_history(){
    char LINE[100];
    char *result;
    FILE *read = fopen(file_path, "r");
    FILE *history_file = fopen(file_path, "a+");
     if(!history_file){
        printf( COLOR_RED "ERROR: The file \".meushell.hst\" could not be found! \n" COLOR_RESET);
        exit(0);
    }
    //
    fseek(read, -1, SEEK_END);

    // Volta para o início da penúltima linha
    while (fgetc(read) != '\n') {
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

void parser(){
    char * token = strtok(data, " ");
    loop = -1;
    while(token != NULL){
        variables[++loop] = malloc(sizeof(token) + 1);
        strcpy(variables[loop], token);
        token = strtok (NULL, " ");
    }
    // Adicionar isso a outra funcao específica
    strcpy(path, "/bin/");
    strcat(path, variables[0]);
}

void reset_variables(){
    for(int i = 0; variables[i] != NULL; i++){
        variables[i] = NULL;
    }
}