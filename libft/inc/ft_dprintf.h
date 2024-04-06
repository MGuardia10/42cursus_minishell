/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 09:37:13 by mguardia          #+#    #+#             */
/*   Updated: 2024/04/06 20:35:16 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

int			ft_dprintf(int fd, char const *str, ...);
void		ft_fputchar_c(char c, int *nums);
void		ft_fputstr_c(char *str, int *nums);
void		ft_fputnbr_base(long long int n, int base_len, int *nums, \
													char *base);
void		ft_fputunsignednbr_base(unsigned long n, size_t b_len, int *nums, \
													char *base);
void		ft_fprintpointer(void *ptr, int *nums);

#endif