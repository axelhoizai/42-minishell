/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:44:23 by ahoizai           #+#    #+#             */
/*   Updated: 2025/01/28 20:50:04 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_echo(char	**builtin_tab, int *i, int is_n)
{
	while (builtin_tab[*i])
	{
		if (builtin_tab[*i] && builtin_tab[*i + 1])
			printf("%s ", builtin_tab[*i]);
		else if (builtin_tab[*i])
			printf("%s", builtin_tab[*i]);
		(*i)++;
	}
	if (is_n == 1)
		printf("\n");
}

void	ft_echo(int argc, char **argv)
{
	int		i;
	char	**builtin_tab;

	builtin_tab = ft_echo_tab(argc, argv);
	if (!builtin_tab || !builtin_tab[0])
	{
		free_tab(builtin_tab);
		return ;
	}
	if (ft_strcmp(builtin_tab[0], "echo") == 0)
	{
		i = 1;
		if (builtin_tab[1] && ft_strcmp("-n", builtin_tab[1]) == 0)
		{
			while (builtin_tab[i] && ft_strcmp("-n", builtin_tab[i]) == 0)
				i++;
			print_echo(builtin_tab, &i, 0);
		}
		else
			print_echo(builtin_tab, &i, 1);
		free_tab(builtin_tab);
	}
}
