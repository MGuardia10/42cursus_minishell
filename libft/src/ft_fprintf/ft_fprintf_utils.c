/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:25:58 by mguardia          #+#    #+#             */
/*   Updated: 2024/03/04 17:26:41 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_fprintf.h"

void	ft_fputchar_c(char c, int *nums)
{
	nums[0] += write(nums[1], &c, 1);
}

void	ft_fputstr_c(char *str, int *nums)
{
	if (str == NULL)
		str = "(null)";
	while (*str)
		nums[0] += write(nums[1], &(*str++), 1);
}

void	ft_fputnbr_base(long long int n, int b_len, int *nums, char *base)
{
	if (n < 0)
	{
		n *= -1;
		nums[0] += write(nums[1], "-", 1);
	}
	if (n >= b_len)
		ft_fputnbr_base(n / b_len, b_len, nums, base);
	ft_fputchar_c(base[n % b_len], nums);
}

void	ft_fputunsignednbr_base(unsigned long n, size_t b_len, int *nums, \
															char *base)
{
	if (n >= b_len)
		ft_fputunsignednbr_base(n / b_len, b_len, nums, base);
	ft_fputchar_c(base[n % b_len], nums);
}

void	ft_fprintpointer(void *ptr, int *nums)
{
	unsigned long	num;

	if (!ptr)
	{
		ft_fputstr_c("0x0", nums);
		return ;
	}
	num = (unsigned long)ptr;
	ft_fputstr_c("0x", nums);
	ft_fputunsignednbr_base(num, 16, nums, "0123456789abcdef");
}
