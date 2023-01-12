all: programa.exe
  echo Executando o programa!
  programa.exe

programa.exe: meushell.c
  echo Compilando o programa
  gcc -o programa.exe meushell.c
