/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:44:23 by ahoizai           #+#    #+#             */
/*   Updated: 2025/01/22 19:17:20 by mdemare          ###   ########.fr       */
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

void	ft_echo(int argc,char **argv)
{
	int		i;
	char	*tmp1;

	i = 0;
	(void)argc;
	print_tab(argv);
	while (argv[i])
	{
		tmp1 = parse_arg(argv[i]);
		if (tmp1 != argv[i])
			free(tmp1);
		i++;
	}
}
