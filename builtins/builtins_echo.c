/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:44:23 by ahoizai           #+#    #+#             */
/*   Updated: 2025/01/22 13:44:39 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("[%d] : \'%s\'\n", i, tab[i]);
		i++;
	}
}

char	**handle_n(char *builtins)
{
	int		i;
	int		j;
	char	**newline;
	
	newline = utils_parse_args(builtins);
	i = 1;
	while (newline[i])
	{
		j = 1;
		if (newline[i][0] == '-')
		{
			while (newline[i][j] && newline[i][j] == 'n')
				j++;
			if (newline[i][j] == '\0')
			{
				free (newline[i]);
				newline[i] = ft_strdup("-n");
				printf("newline[%d] : \'%s\'\n", i, newline[i]);
			}
		}
		i++;
	}
	print_tab(newline);
	return (newline);
}

void	ft_echo(char *input)
{
	int		i;
	char	**builtin_tab;

	builtin_tab = handle_n(input);
	if (ft_strcmp(builtin_tab[0], "echo") == 0)
	{
		if (!builtin_tab[1] || (ft_strcmp("-n", builtin_tab[1])) != 0)
		{
			i = 1;
			while (builtin_tab[i])
			{
				if (builtin_tab[i] && builtin_tab[i + 1])
					printf("%s ", builtin_tab[i]);
				else if (builtin_tab[i] && !builtin_tab[i + 1])
					printf("%s", builtin_tab[i]);
				i++;
			}
			printf("\n");
		}
		else if (ft_strcmp(builtin_tab[0], "echo") == 0 && (ft_strcmp("-n", builtin_tab[1])) == 0)
		{
			i = 1;
			while (builtin_tab[i] && (ft_strcmp("-n", builtin_tab[i])) == 0)
				i++;
			while (builtin_tab[i])
			{
				if (builtin_tab[i + 1])
					printf("\'%s\' ", builtin_tab[i]);
				else
					printf("\'%s\'", builtin_tab[i]);
				i++;
			}
		}
	}
}
