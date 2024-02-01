/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:25:58 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:20:50 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

void	ft_putchar_c(char c, int *count)
{
	*count += write(1, &c, 1);
}

void	ft_putstr_c(char *str, int *count)
{
	if (str == NULL)
		str = "(null)";
	while (*str)
		*count += write(1, &(*str++), 1);
}

void	ft_putnbr_base(long long int n, int b_len, int *count, char *base)
{
	if (n < 0)
	{
		n *= -1;
		*count += write(1, "-", 1);
	}
	if (n >= b_len)
		ft_putnbr_base(n / b_len, b_len, count, base);
	ft_putchar_c(base[n % b_len], count);
}

void	ft_putunsignednbr_base(unsigned long n, size_t b_len, int *count, \
															char *base)
{
	if (n >= b_len)
		ft_putunsignednbr_base(n / b_len, b_len, count, base);
	ft_putchar_c(base[n % b_len], count);
}

void	ft_printpointer(void *ptr, int *count)
{
	unsigned long	num;

	if (!ptr)
	{
		ft_putstr_c("0x0", count);
		return ;
	}
	num = (unsigned long)ptr;
	ft_putstr_c("0x", count);
	ft_putunsignednbr_base(num, 16, count, "0123456789abcdef");
}
