/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:13:59 by ahoizai           #+#    #+#             */
/*   Updated: 2025/02/20 20:22:13 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_first_arg(t_command *cmd, int *exit_code, t_data *data)
{
	if (cmd && cmd->args)
	{
		print_tab(cmd->args);
		if (cmd->args && cmd->args[1] && ft_isnumeric(cmd->args[1]) == 1)
		{
			*exit_code = ft_atoi(cmd->args[1]);
			if (*exit_code == -1)
				*exit_code = 255;
			return (1);
		}
		if (cmd->args && cmd->args[1])
		{
			data->exit_code = 2;
			ft_print_error("exit", cmd->args[1], "numeric argument required");
			*exit_code = 2;
			return (1);
		}
	}
	return (1);
}

static int	validate_exit_args(t_command *cmd, int *exit_code, t_data *data)
{
	int	i;

	if (handle_first_arg(cmd, exit_code, data) == 0)
		return (0);
	i = 2;
	if (cmd && cmd->args[0])
	{
		while (cmd->args && ft_isnumeric(cmd->args[1]) == 1
			&& cmd->args[i])
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

void	free_data(t_data * data)
{
	free(data->oldpwd);
	free(data->pwd);
}

void	handle_exit(t_command *cmd, t_pipeline *pip, t_data *data)
{
	int		exit_code;

	exit_code = data->exit_code;
	if (validate_exit_args(cmd, &exit_code, data) == 1)
	{
		printf("exit\n");
		if (pip && cmd != pip->cmds[pip->pipe_cnt] && pip->pipe_cnt > 0)
			exit_code = 0;
		if (data->my_envp)
		{
			free_tab(data->my_envp);
			data->my_envp = NULL;
		}
		ms_lstclear(&data->env_ms);
		if (pip)
		{
			free_pipeline(pip);
			pip = NULL;
		}
		data->is_reading = false;
		rl_clear_history();
		free_term(data);
		free_data(data);
		exit(exit_code);
	}
}
