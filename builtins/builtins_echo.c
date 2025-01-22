/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:44:23 by ahoizai           #+#    #+#             */
/*   Updated: 2025/01/22 19:55:29 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_n(char *flag)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (flag[0] == '-')
	{
		while (flag[i] && flag[i] == 'n')
			i++;
		if (flag[i] == '\0')
			return (ft_strdup("-n"));
	}
	return (ft_strdup(flag));
}

char	*parse_arg(char *arg)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	int		i;
	
	i = 0;
	if (ft_strchr(arg, '"') || ft_strchr(arg, '\''))
	{
		tmp1 = ft_strdup(arg);
		tmp2 = parse_quote(tmp1);
		free(tmp1);
		tmp3 = handle_n(tmp2);
		if (tmp3)
		{
			free(tmp2);
			tmp2 = ft_strdup(tmp3);
			free(tmp3);
		}
		return (tmp2);
	}
	return (handle_n(arg));
}

char	**ft_echo_tab(int argc, char **argv)
{
	int		i;
	char	**builtin_tab;

	i = 0;
	print_tab(argv);
	builtin_tab = malloc(sizeof (char *) * (argc + 1));
	while (argv[i])
	{
		builtin_tab[i] = parse_arg(argv[i]);
		printf("arg : %s\n", builtin_tab[i]);
		i++;
	}
	builtin_tab[i] = NULL;
	return (builtin_tab);
}

void	ft_echo(int argc, char **argv)
{
	int		i;
	char	**builtin_tab;

	builtin_tab = ft_echo_tab(argc, argv);
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
					printf("%s ", builtin_tab[i]);
				else
					printf("%s", builtin_tab[i]);
				i++;
			}
		}
	}
	free_tab(builtin_tab);
}
