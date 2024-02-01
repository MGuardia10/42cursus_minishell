/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 09:37:13 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 16:17:56 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

int			ft_printf(char const *str, ...);
void		ft_putchar_c(char c, int *count);
void		ft_putstr_c(char *str, int *count);
void		ft_putnbr_base(long long int n, int base_len, int *count, \
													char *base);
void		ft_putunsignednbr_base(unsigned long n, size_t b_len, int *count, \
													char *base);
void		ft_printpointer(void *ptr, int *count);

#endif