/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:23:36 by mguardia          #+#    #+#             */
/*   Updated: 2024/04/06 20:35:00 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_dprintf.h"

static void	format_printf(char c, va_list ap, int *nums)
{
	if (c == '%')
		nums[0] += write(nums[1], "%", 1);
	else if (c == 'c')
		ft_fputchar_c(va_arg(ap, int), nums);
	else if (c == 's')
		ft_fputstr_c(va_arg(ap, char *), nums);
	else if (c == 'p')
		ft_fprintpointer(va_arg(ap, void *), nums);
	else if (c == 'd' || c == 'i')
		ft_fputnbr_base((long long int)va_arg(ap, int), 10, \
								nums, "0123456789");
	else if (c == 'u')
		ft_fputnbr_base((long long int)va_arg(ap, unsigned int), 10, \
								nums, "0123456789");
	else if (c == 'x')
		ft_fputnbr_base(va_arg(ap, unsigned int), 16, \
								nums, "0123456789abcdef");
	else if (c == 'X')
		ft_fputnbr_base(va_arg(ap, unsigned int), 16, \
								nums, "0123456789ABCDEF");
}

/**
 * The ft_fprintf function takes a file descriptor and a format string with
 * optional arguments, and writes formatted output to the specified file
 * descriptor.
 * 
 * @param fd The `fd` parameter in the `ft_fprintf` function represents the file
 * descriptor where the output will be written. It is an integer value that
 * specifies the file or stream to which the formatted output will be written.
 * @param str The `str` parameter in the `ft_fprintf` function is a pointer to a
 * constant character string that contains the format string to be printed. This
 * format string may contain format specifiers that start with `%` and are
 * followed by conversion specifiers (e.g., `%d`, `%s`...)
 * 
 * @return The function `ft_fprintf` is returning the total number of characters
 * written to the file descriptor `fd`.
 */
int	ft_dprintf(int fd, char const *str, ...)
{
	va_list	ap;
	int		nums[2];

	va_start(ap, str);
	nums[0] = 0;
	nums[1] = fd;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			format_printf(*str, ap, nums);
		}
		else
			nums[0] += write(nums[1], &(*str), 1);
		str++;
	}
	va_end(ap);
	return (nums[0]);
}
