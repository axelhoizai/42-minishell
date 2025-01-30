/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:13:59 by ahoizai           #+#    #+#             */
/*   Updated: 2025/01/30 18:20:52 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_first_arg(char **argv, int *exit_code, t_data *data)
{
	if (argv && argv[1] && ft_isnumeric(argv[1]) == 1)
	{
		*exit_code = ft_atoi(argv[1]);
		return (1);
	}
	if (argv && argv[1])
	{
		data->exit_code = 2;
		ft_print_error("exit", argv[1], "numeric argument required");
		*exit_code = 2;
		return (0);
	}
	return (1);
}

static int	validate_exit_args(char **argv, int *exit_code, t_data *data)
{
	int	i;

	if (handle_first_arg(argv, exit_code, data) == 0)
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
		data->exit_code = 1;
		ft_print_error("exit", NULL, "too many arguments");
		*exit_code = 1;
		return (0);
	}
	return (1);
}

void	handle_exit(char **argv, t_data	*data)
{
	int	exit_code;

	exit_code = data->exit_code;
	printf("exit\n");
	if (validate_exit_args(argv, &exit_code, data) == 1)
	{
		rl_clear_history();
		if (argv)
			free_tab(argv);
		free_tab(data->my_envp);
		ms_lstclear(&data->env_ms);
		// free_tab(data->my_envp);
		exit(exit_code);
	}
}
