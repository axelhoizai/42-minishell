/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:44:23 by ahoizai           #+#    #+#             */
/*   Updated: 2025/01/25 17:10:54 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//TODO : Recheck the 'echo $VAR' logic
char	*parse_var(char *arg)
{
	t_env_ms	*to_find;
	char		*tmp;
	
	tmp = arg;
	to_find = NULL;
	if (is_key(data.env_ms, tmp + 1))
	{
		to_find = ms_find(data.env_ms, tmp + 1);
		free (tmp);
		return (to_find->value);
	}
	return (tmp);
}

void	print_echo(char	**builtin_tab, int *i, int is_n)
{
	while (builtin_tab[*i])
	{
		if (ft_strstr(builtin_tab[*i], "$?"))
		{
			builtin_tab[*i] = parse_dollar(builtin_tab[*i]);
			g_data.exit_code = 0;
		}
		if (ft_strstr(builtin_tab[*i], "$$"))
			builtin_tab[*i] = parse_dollar_double(builtin_tab[*i]);
		if (builtin_tab[*i][0] == '$')
			builtin_tab[*i] = parse_var(builtin_tab[*i]);
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
	}
	free_tab(builtin_tab);
}
