# 42cursus_minishell
As beautiful as a shell. This project aims to create a minimal shell that can interpret and execute basic Unix operating system commands. GNU Bash 3.2 has been taken as a reference, as it is the default version on macOS for 42Madrid computers.

This recreation of Bash supports redirections (<, >, <<, >>), pipes ( | ), single and double quotes, environment variables expansion and signals such as CTRL-D, CTRL-C and CTRL-\\. Also, we had to recreate as Builtin this list of commands: echo (with -n option), cd, pwd, export, unset, env, exit.


![C](https://img.shields.io/badge/C-a?style=for-the-badge&logo=C&color=grey)
![LINUX](https://img.shields.io/badge/Linux-a?style=for-the-badge&logo=linux&color=grey)

You can see the subject [**HERE.**](https://github.com/MGuardia10/42cursus/blob/main/subjects/en/minishell_subject_en.pdf)

## Installing and running the project:
1- Clone this repository
	
	git clone https://github.com/MGuardia10/42cursus_minishell.git
2- Navigate to the new directory and run `make`
	
	cd 42cursus_minishell
   	make
3- Start the shell, no parameters needed:

	./minishell

## Compiling the Program
The philo program comes with a Makefile that includes the following rules:

- `all`: compiles the program.
- `re`: recompiles the program.
- `clean`: removes obj directory with objects files.
- `fclean`: removes obj directory with objects files and minishell binary.

## Disclaimer
> At [42School](https://en.wikipedia.org/wiki/42_(school)), almost every project must be written in accordance to the [Norm](https://github.com/MGuardia10/42cursus/blob/main/subjects/en/norm_en.pdf), the school's coding standard. As a result, the implementation of certain parts may appear strange and for sure had room for improvement.