/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:25:14 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:41:31 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			result++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (result);
}

static char	**free_arr(char **p, int i)
{
	while (i > 0)
	{
		i--;
		free(p[i]);
	}
	free(p);
	return (0);
}

static char	*putword(char *word, char const *s, int i, int w_len)
{
	int	j;

	j = 0;
	while (w_len > 0)
	{
		word[j] = s[i - w_len];
		j++;
		w_len--;
	}
	word[j] = '\0';
	return (word);
}

static char	**split_words(char const *s, char c, char **split, int words)
{
	int	i;
	int	num_words;
	int	w_len;

	i = 0;
	num_words = 0;
	w_len = 0;
	while (num_words < words)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			w_len++;
		}
		split[num_words] = (char *)malloc(sizeof(char) * (w_len + 1));
		if (!split[num_words])
			return (free_arr(split, num_words));
		putword(split[num_words], s, i, w_len);
		w_len = 0;
		num_words++;
	}
	split[num_words] = NULL;
	return (split);
}

/**
 * The function `ft_split` takes a string `s` and a character `c` as input,
 * and splits `s` into an array of substrings based on the delimiter `c`.
 * 
 * @param s A pointer to a string that needs to be split into words.
 * @param c The parameter `c` is a character that is used as a delimiter to
 * split the string `s` into multiple words.
 * 
 * @return The function `ft_split` is returning a pointer to a pointer of
 * characters (`char **`).
 */
char	**ft_split(char const *s, char c)
{
	char			**split;
	unsigned int	words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	split = split_words(s, c, split, words);
	return (split);
}
