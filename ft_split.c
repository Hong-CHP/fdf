/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:50:50 by hporta-c          #+#    #+#             */
/*   Updated: 2025/05/29 11:00:50 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "fdf.h"

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
			return (1);
	return (0);
}

int	count_words(char *str)
{
	int	is_ch;
	int	count;
    int i;
    
	count = 0;
	is_ch = 1;
	while (str[i])
	{
		if (!is_space(str[i]))
		{
			if (is_ch == 1)
			{
				count++;
				is_ch = 0;
			}
		}
		else
			is_ch = 1;
		i++;
	}
	return (count);
}

char	*allocate_copy_tab(int word_len, char *str)
{
	char	*p;
	char	*word;

	p = (char *)malloc((word_len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	word = p;
	p[word_len] = '\0';
	while (word_len > 0)
	{
		*p++ = *str++;
		word_len--;
	}
	return (word);
}

char	**ft_fill_split(char **tab, char *str, int *tab_i)
{
	int	word_len;
	int	i;

	word_len = 0;
	i = 0;
	while (str[i])
	{
		if (is_space(str[i]))
		{
			if (word_len > 0)
			{
				tab[*tab_i] = allocate_copy_tab(word_len, &str[i - word_len]);
				(*tab_i)++;
				word_len = 0;
			}
		}
		else
			word_len++;
		i++;
	}
	if (word_len > 0)
		tab[(*tab_i)++] = allocate_copy_tab(word_len, &str[i - word_len]);
	return (tab);
}

char	**ft_split(char	const *s)
{
	char	**tab;
	char	*str;
	int		tab_i;

	tab_i = 0;
	str = (char *)s;
	tab = (char **)malloc((count_words(str) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	ft_fill_split(tab, str, &tab_i);
	tab[tab_i] = NULL;
	return (tab);
}