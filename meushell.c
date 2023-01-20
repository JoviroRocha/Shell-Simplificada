#include "meushell.h"

// USAREMOS O "which <comando>" para localizar?
// PRECISAMOS IMPLEMENTAR O "&&" para executar comandos diferentes -> and
// TBD: IMPLEMENTAR O CONFIG, A MUDANCA DE CONFIG, IMPLEMENTAR CD, LIMPA, SAIR, AJUDA E AMB, IMPLEMENTAR O HISTORICO, IMPLEMENTAR A LEITURA DE COMANDOS POR ARQUIVO
// USAREMOS /bin/ls /bin/pwd /bin/hostname

int main()
{
    char *variables[1];
    char var_amb_arq[2][256];
    char variables_amb[2][256];

    // Configure Shell
    printf(COLOR_GREEN "Configuring the shell...\n" COLOR_RESET);
    config();
    printf(COLOR_GREEN "Done configuring!\n" COLOR_RESET);
    while (1)
    {
        // reseta as variáveis
        reset_variables(variables);
        // printa o PRONTO
        printf(COLOR_BLUE "%s $ " COLOR_RESET, PRONTO);
        // recebe o input
        scanf(" %[^\n]", data);
        // adiciona ao histórico
        add_history()
        //  parseia o input
        parser(variables);
        // executa o input
        if (strcmp(variables[0], "cd") == 0)
        {
            cd(variables);
            escreve();
        }
        else if (strcmp(variables[0], "help") == 0)
        {
            help();
        }
        else if (strcmp(variables[0], "amb") == 0)
        {
            var_ambiente(variables, var_amb_arq, variables_amb);
        }
        else if (strcmp(variables[0], "clear") == 0)
        {
            clear();
        }
        else if (strcmp(variables[0], "exit") == 0)
        {
            printf(COLOR_GREEN "Shell is exiting...\n" COLOR_RESET);
            return 0;
        }
        else
        {
            int resp;
            // Executar o comando
            if (fork() == 0)
            {
                if (strcmp(variables[0], "hostname") == 0)
                {
                    gethostname(HOST, sizeof(HOST));
                    escreve();
                }
                resp = execvp(path, variables);
                if (resp == -1)
                    printf(COLOR_RED "ERROR: Command not found\n" COLOR_RESET);
                exit(0);
            }
            wait(NULL);
        }
    };
    return 0;
}
