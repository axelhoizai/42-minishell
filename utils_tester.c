/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tester.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:16:24 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/03 10:49:36 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_exit_tester(char **argv, t_data *data)
{
	int	exit_code;

	exit_code = data->exit_code;
	if (argv && argv[1] && ft_isnumeric(argv[1]) == 1)
		exit_code = ft_atoi(argv[1]);
	else if (argv && argv[1])
	{
		data->exit_code = 2;
		ft_print_error("exit", argv[1], "numeric argument required");
		exit_code = 2;
	}
	rl_clear_history();
	if (argv)
		free_tab(argv);
	ms_lstclear(&data->env_ms);
	exit(exit_code);
}

int	argc_from_argv(char **argv)
{
	int	count;

	count = 2;
	while (argv && argv[count])
		count++;
	return (count);
}

char	*join_argv2(char **argv)
{
	int		i;
	char	*cmd;
	char	*tmp;

	if (!argv || !argv[1])
		return (NULL);
	cmd = ft_strdup(argv[1]);
	if (!cmd)
		return (NULL);
	i = 2;
	while (argv[i])
	{
		tmp = ft_strjoin(cmd, " ");
		free(cmd);
		if (!tmp)
			return (NULL);
		cmd = ft_strjoin(tmp, argv[i]);
		free(tmp);
		if (!cmd)
			return (NULL);
		i++;
	}
	return (cmd);
}

void	handle_av_commands(char **av, t_data *data)
{
	char	**argv;

	argv = NULL;
	if (av && av[2])
	{
		printf("Usage tester: ./minishell \"cmds\"\n");
		handle_exit_tester(NULL, data);
		return ;
	}
	get_argv(av[1], data);
	handle_exit_tester(argv, data);
	free_tab(argv);
}

void	sh_tester(char **av, t_data	*data)
{
	char	**argv;
	char	*input;

	argv = NULL;
	if (!isatty(STDIN_FILENO))
	{
		input = get_next_line(STDIN_FILENO);
		while (input != NULL)
		{
			get_argv(input, data);
			if (!argv)
			{
				free(input);
				input = get_next_line(STDIN_FILENO);
				continue ;
			}
			free(input);
			input = get_next_line(STDIN_FILENO);
		}
	}
	else
		handle_av_commands(av, data);
	handle_exit_tester(argv, data);
}
