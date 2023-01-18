#include "meushell.h"

// USAREMOS O "which <comando>" para localizar?
// PRECISAMOS IMPLEMENTAR O "&&" para executar comandos diferentes -> and
// TBD: IMPLEMENTAR O CONFIG, A MUDANCA DE CONFIG, IMPLEMENTAR CD, LIMPA, SAIR, AJUDA E AMB, IMPLEMENTAR O HISTORICO, IMPLEMENTAR A LEITURA DE COMANDOS POR ARQUIVO
// USAREMOS /bin/ls /bin/pwd /bin/hostname 

int main(){
    char *variables[1];
    char *var_amb_arq[1];
    char *variables_amb[1];
    // Configure Shell
    printf(COLOR_GREEN "Configuring the shell...\n" COLOR_RESET);
    config();
    printf(COLOR_GREEN "Done configuring!\n" COLOR_RESET);
    while(1){
        // reseta as variáveis
        reset_variables(variables);
        reset_variables(var_amb_arq);
        reset_variables(variables_amb);
        // printa o PRONTO
        printf(COLOR_BLUE "%s $ " COLOR_RESET, PRONTO);
        // recebe o input
        scanf(" %[^\n]", data);
        strcpy(data_save,data);
        //save history
        // parseia o input
        parser(variables);
        //adiciona ao histórico
        add_history();
        // executa o input
        if (strcmp(variables[0], "cd") == 0){
            cd(variables);
        }
        else if(strcmp(variables[0],"amb") == 0){
            var_ambiente(variables, var_amb_arq, variables_amb);
        }
        else if (strcmp(variables[0],"clear") == 0){
            clear();
        } 
        else if (strcmp(variables[0],"exit") == 0){
            printf(COLOR_GREEN "Shell is exiting...\n" COLOR_RESET);
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
