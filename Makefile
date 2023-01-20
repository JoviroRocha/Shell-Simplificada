all: compile_message programa.exe ; @echo "Running the shell..." ; ./programa.exe
programa.exe: meushell.c meushell.h ; gcc -pthread -o programa.exe meushell.c
compile_message: ; @echo "Compiling the shell..."