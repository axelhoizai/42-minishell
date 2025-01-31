/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:40:20 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/31 12:55:39 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*process_arg(char **builtin_tab, char **argv, int i)
{
	char	*temp;

	builtin_tab[i] = ft_strdup(argv[i]);
	if (((i > 0 && (ft_strcmp(builtin_tab[i - 1], "-n") == 0)) || i == 1)
		&& (ft_strcmp("-n", builtin_tab[i]) != 0 && builtin_tab[i][0] == '-'))
	{
		temp = builtin_tab[i];
		builtin_tab[i] = handle_n(builtin_tab[i]);
		if (temp != builtin_tab[i])
			free(temp);
	}
	return (builtin_tab[i]);
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
	free_tab(argv);
	return (builtin_tab);
}
