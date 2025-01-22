/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:44:23 by ahoizai           #+#    #+#             */
/*   Updated: 2025/01/22 19:02:08 by mdemare          ###   ########.fr       */
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

int		ft_count_single(char *arg)
{
	int	count_simgle;
	int	i;
	
	count_simgle = 0;
	i = 0;
	while(arg[i])
	{
		if (arg[i] == '\'')
			count_simgle++;
		i++;
	}
	if (count_simgle % 2 == 1)
		count_simgle -=1;
	return (count_simgle);
}

int		ft_count_double(char *arg)
{
	int	count_double;
	int	i;
	
	count_double = 0;
	i = 0;
	while(arg[i])
	{
		if (arg[i] == '\"')
			count_double++;
		i++;
	}
	if (count_double % 2 == 1)
		count_double -=1;
	
	return (count_double);
}

char	*parse_quote(char *arg)
{
	char	*tmp1;
	int		j;
	int		count_double;
	int		count_simgle;

	j = 0;
	count_simgle = ft_count_single(arg);
	count_double = ft_count_double(arg);
	tmp1 = ft_calloc(ft_strlen(arg), 1);
	while (*arg)
	{
		while (count_double > 0 && *arg == '"')
		{
			count_double -= 1;
			arg++;
		}
		while (count_simgle > 0 && *arg == '\'')
		{
			count_simgle -= 1;
			arg++;
		}
		tmp1[j++] = *arg;
		arg++;
	}
	return (tmp1);
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
