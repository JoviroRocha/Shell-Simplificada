#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

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

int file_exists(const char *filename){
    FILE *arquivo;
    if(arquivo = fopen(filename, "r")){
        fclose(arquivo);
        return 1;
    }
    
    return 0;
    
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
    FILE *config_file = fopen(".meushell.rec","w+");
    if(!config_file){
        printf( COLOR_RED "ERROR: The file \".meushell.rec\" could not be found! \n" COLOR_RESET);
        exit(0);
    }
    fprintf(config_file,"HOST=%s\nPRONTO=%s\nSHELL=%s\nDTA=%s\n",HOST,PRONTO,SHELL,DTA);
    fclose(config_file);
    // Write to the history file
    if( file_exists(".meushell.hst") == 1){

        return;
    }
    else{

        FILE *history_file = fopen(".meushell.hst","w+");
        if(!history_file){
            printf( COLOR_RED "ERROR: The file \".meushell.hst\" could not be found! \n" COLOR_RESET);
            exit(0);
        }
        fprintf(history_file, "1");
        fclose(history_file);
        return;
    }
}

void add_history(){
    FILE *history_file = fopen(".meushell.hst", "a+");
    rewind(history_file);
    int loop;
    int offset;
    loop = (int)fscanf(history_file, "%d", &loop);
    printf("Loop: %i", loop);
    offset = loop % 100;
    printf("Ofset: %i", offset);    
    loop++;
    printf("Loop 2: %i", (char)loop);
    fputc((char)loop, history_file);
    fclose(history_file);
}

void parser(){
    char * token = strtok(data, " ");
    int loop = -1;
    while(token != NULL){
        variables[++loop] = malloc(sizeof(token) + 1);
        strcpy(variables[loop], token);
        token = strtok (NULL, " ");
    }
    // Adicionar isso a outra funcao específica
    strcpy(path, "/usr/bin/");
    strcat(path, variables[0]);
}

void reset_variables(){
    for(int i = 0; variables[i] != NULL; i++){
        variables[i] = NULL;
    }
}