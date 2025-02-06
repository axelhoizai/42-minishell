/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:13:59 by ahoizai           #+#    #+#             */
/*   Updated: 2025/02/04 17:09:38 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_first_arg(t_pipeline *pip, int *exit_code, t_data *data)
{
	char	**argv;

	argv = NULL;
	if (pip)
	{
		argv = pip->cmds[0]->args;
		if (argv && argv[1] && ft_isnumeric(argv[1]) == 1)
		{
			*exit_code = ft_atoi(argv[1]);
			if (*exit_code == -1)
				*exit_code = 255;
			return (1);
		}
		if (argv && argv[1])
		{
			data->exit_code = 2;
			ft_print_error("exit", argv[1], "numeric argument required");
			*exit_code = 2;
			// free_tab(argv);
			return (1);
		}
	}
	return (1);
}

static int	validate_exit_args(t_pipeline *pip, int *exit_code, t_data *data)
{
	int	i;

	if (handle_first_arg(pip, exit_code, data) == 0)
		return (0);
	i = 2;
	if (pip)
	{
		while (pip->cmds[0]->args && ft_isnumeric(pip->cmds[0]->args[1]) == 1
			&& pip->cmds[0]->args[i])
			i++;
		if (i > 2)
		{
			data->exit_code = 1;
			ft_print_error("exit", NULL, "too many arguments");
			*exit_code = 1;
			return (0);
		}
	}
	return (1);
}

void	handle_exit(t_pipeline *pip, t_data *data)
{
	int	exit_code;

	exit_code = data->exit_code;
	// print_pipeline(pip);
	if (validate_exit_args(pip, &exit_code, data) == 1)
	{
		printf("exit\n");
		free_tab(data->my_envp);
		ms_lstclear(&data->env_ms);
		if(pip)
			free_pipeline(pip);
		rl_clear_history();
		// if (argv)
		// 	free_tab(argv);
		exit(exit_code);
	}
}

void	handle_exit_parent(t_pipeline *pip, t_data *data)
{
	int	i;

	i = 2;
	while (pip->cmds[0]->args && ft_isnumeric(pip->cmds[0]->args[1]) == 1
		&& pip->cmds[0]->args[i])
			i++;
	if (i > 2)
	{
		data->exit_code = 1;
		return ;
	}
	free_tab(data->my_envp);
	ms_lstclear(&data->env_ms);
	if(pip)
		free_pipeline(pip);
	rl_clear_history();
	exit(data->exit_code);
}
