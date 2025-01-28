/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:13:59 by ahoizai           #+#    #+#             */
/*   Updated: 2025/01/28 21:40:12 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_first_arg(char **argv, int *exit_code)
{
	if (argv && argv[1] && ft_isnumeric(argv[1]) == 1)
	{
		*exit_code = ft_atoi(argv[1]);
		return (1);
	}
	if (argv && argv[1])
	{
		ft_print_error("exit", argv[1], "numeric argument required", 2);
		*exit_code = 2;
		return (0);
	}
	return (1);
}

static int	validate_exit_args(char **argv, int *exit_code)
{
	int	i;

	if (handle_first_arg(argv, exit_code) == 0)
		return (0);
	i = 1;
	while (argv && argv[i])
	{
		if (ft_isnumeric(argv[i]) == 0)
			return (1);
		i++;
	}
	if (i > 2)
	{
		ft_print_error("exit", NULL, "too many arguments", 1);
		*exit_code = 1;
		return (0);
	}
	return (1);
}

void	handle_exit(char **argv)
{
	int	exit_code;

	exit_code = g_data.exit_code;
	printf("exit\n");
	if (validate_exit_args(argv, &exit_code) == 1)
	{
		rl_clear_history();
		if (argv)
			free_tab(argv);
		ms_lstclear(&g_data.env_ms);
		exit(exit_code);
	}
}
