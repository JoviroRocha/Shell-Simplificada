all: programa.exe
  echo Executando o programa!
  programa.exe

programa.exe:
  echo Compilando o programa
  gcc -o programa.exe meushell.c
