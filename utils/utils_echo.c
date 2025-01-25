/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:40:20 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/25 00:25:22 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_n(char *flag)
{
	int		i;

	i = 1;
	if (ft_strcmp("-n", flag) != 0 && flag[0] == '-')
	{
		while (flag[i] && flag[i] == 'n')
			i++;
		if (flag[i] == '\0')
			return (ft_strdup("-n"));
	}
	return (NULL);
}

char	*parse_dollar(char *arg, t_data *data)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	int		i;

	i = 0;
	while (arg)
	{
		if (arg[i] == '$' && arg[i + 1] == '?')
			break ;
		i++;
	}
	tmp1 = ft_substr(arg, 0, i);
	tmp2 = ft_itoa(data->exit_code);
	tmp3 = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	tmp1 = ft_substr(arg, i + 2, ft_strlen(arg));
	free(arg);
	arg = ft_strjoin(tmp3, tmp1);
	free(tmp1);
	free(tmp3);
	if (ft_strstr(arg, "$?"))
		return (parse_dollar(arg, data));
	return (arg);
}


char	*process_arg(char **builtin_tab, char **argv, int i)
{
	char	*temp;

	builtin_tab[i] = ft_strdup(argv[i]);
	if (((i > 0 && (ft_strstr(builtin_tab[i - 1], "-n") != NULL)) || i == 1)
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
	return (builtin_tab);
}
