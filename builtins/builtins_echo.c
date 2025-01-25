/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:44:23 by ahoizai           #+#    #+#             */
/*   Updated: 2025/01/25 00:31:08 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_echo(char	**builtin_tab, t_data *data, int *i)
{
	while (builtin_tab[*i])
	{
		if (ft_strstr(builtin_tab[*i], "$?"))
			builtin_tab[*i] = parse_dollar(builtin_tab[*i], data);
		if (ft_strstr(builtin_tab[*i], "$$"))
			printf("variable env found");
		if (builtin_tab[*i] && builtin_tab[*i + 1])
			printf("%s ", builtin_tab[*i]);
		else if (builtin_tab[*i])
			printf("%s", builtin_tab[*i]);
		(*i)++;
	}
}

void	ft_echo(int argc, char **argv, t_data *data)
{
	int		i;
	char	**builtin_tab;

	builtin_tab = ft_echo_tab(argc, argv);
	if (!builtin_tab || !builtin_tab[0])
	{
		free_tab(builtin_tab);
		return;
	}
	if (ft_strcmp(builtin_tab[0], "echo") == 0)
	{
		i = 1;
		if (builtin_tab[1] && ft_strcmp("-n", builtin_tab[1]) == 0)
		{
			while (builtin_tab[i] && ft_strcmp("-n", builtin_tab[i]) == 0)
				i++;
			print_echo(builtin_tab, data, &i);
		}
		else
		{
			print_echo(builtin_tab, data, &i);
			printf("\n");
		}
	}
	free_tab(builtin_tab);
}
