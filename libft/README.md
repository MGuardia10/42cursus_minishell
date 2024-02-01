# 42Madrid - libft
The libft project consists of creating your own first library by reproducing already existing functions. You can use libft on other 42 projects as long as it is allowed, so it will be updated frequently.

![C](https://img.shields.io/badge/C-a?style=for-the-badge&logo=C&color=grey)

You can see the subject [**HERE**](https://github.com/MGuardia10/42cursus/blob/main/subjects/en/libft_subject_en.pdf)

## Installing and compiling the library:

1- Clone this repository
	
	git clone https://github.com/MGuardia10/42cursus_libft.git
2- Navigate to the new directory and run `make`
	
	cd 42cursus_libft
   	make
3- `make clean` to remove the object files and work on a cleaner directory

	make clean
4- Include the libft header on your files and compile with the `libft.a` file.
```C
#include "includes/libft.h"

int main(void)
{
  char *str = "123456";
  int num = ft_atoi(str);

  ft_printf("%d\n", num);
  return (0);
}
```
## Compiling the Program
The libft comes with a Makefile that includes the following rules:

- `all`: compiles the library
- `re`: recompiles the library
- `clean`: removes all object files
- `fclean`: removes all object files and `libft.a`

## Disclaimer
> At [42School](https://en.wikipedia.org/wiki/42_(school)), almost every project must be written in accordance to the [Norm](https://github.com/MGuardia10/42cursus/blob/main/subjects/en/norm_en.pdf), the school's coding standard. As a result, the implementation of certain parts may appear strange and for sure had room for improvement.
