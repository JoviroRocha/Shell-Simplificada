#include "meushell.h"

// USAREMOS O "which <comando>" para localizar?
// PRECISAMOS IMPLEMENTAR O "&&" para executar comandos diferentes -> and
// TBD: IMPLEMENTAR O CONFIG, A MUDANCA DE CONFIG, IMPLEMENTAR CD, LIMPA, SAIR, AJUDA E AMB, IMPLEMENTAR O HISTORICO, IMPLEMENTAR A LEITURA DE COMANDOS POR ARQUIVO
// USAREMOS /bin/ls /bin/pwd /bin/hostname 

int main(){
    // Configure Shell
    printf(COLOR_GREEN "Configuring the shell...\n" COLOR_RESET);
    config();
    printf(COLOR_GREEN "Done configuring!\n" COLOR_RESET);
    pthread_t id;
    while(1){
        // reseta as variáveis
        reset_variables();
        // printa o PRONTO
        printf(COLOR_BLUE "%s $ " COLOR_RESET, PRONTO);
        // recebe o input
        scanf(" %[^\n]", data);
        strcpy(data_save,data);
        //save history
        pthread_create(&id, NULL, add_history , NULL);
        // parseia o input
        parser();
        // executa o input
        if (strcmp(variables[0], "cd") == 0){
            cd();
        }
        else if (strcmp(variables[0],"clear") == 0){
            clear();
        } 
        else if (strcmp(variables[0],"exit") == 0){
            printf(COLOR_GREEN "Shell is exiting...\n" COLOR_RESET);
            pthread_join(id, NULL);
            return 0;
        }
        else {
            int resp;
            // Executar o comando
           if( fork() == 0 ){
                resp = execvp(path, variables);
                if(resp == -1) printf(COLOR_RED "ERROR: Command not found\n" COLOR_RESET);
                exit(0);
           }
            wait(NULL);
        }
    };
    return 0;
}