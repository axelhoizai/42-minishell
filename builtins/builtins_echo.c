/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:44:23 by ahoizai           #+#    #+#             */
/*   Updated: 2025/02/01 17:11:59 by ahoizai          ###   ########.fr       */
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

char	**ft_echo_tab(int argc, char **argv)
{
	int		i;
	char	**builtin_tab;

	builtin_tab = malloc(sizeof(char *) * (argc + 1));
	if (!builtin_tab)
		return (NULL);
	i = 0;
	while (i < argc)
	{
		builtin_tab[i] = process_arg(builtin_tab, argv, i);
		if (!builtin_tab[i])
		{
			while (i > 0)
				free(builtin_tab[--i]);
			free(builtin_tab);
			return (NULL);
		}
		i++;
	}
	builtin_tab[i] = NULL;
	return (builtin_tab);
}

void	ft_echo(int argc, t_pipeline *pip)
{
	int		i;
	char	**builtin_tab;

	builtin_tab = ft_echo_tab(argc, pip->cmds[0]->args);
	free_pipeline(pip);
	print_tab(builtin_tab);
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
