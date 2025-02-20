/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:16:24 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/20 22:38:41 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_init(char **envp, int *is_start, t_data *data)
{
	char	*path_tmp;
	
	path_tmp = NULL;
	if (*is_start == 0)
	{
		path_tmp = getcwd(NULL, 0);
		data->exit_code = 0;
		data->is_reading = 0;
		init_env_ms(envp, data);
		*is_start = 1;
		data->term = (t_data_term *)ft_calloc(sizeof(t_data_term), 1);
		data->oldpwd = ft_strdup(path_tmp);
		data->pwd = ft_strdup(path_tmp);
		free_var(path_tmp);
		if (!data->term)
			return ;
	}
}

static char	main_loop(t_data *data)
{
	char	*input;
	char	*prompt;
	char	exit_code;

	setup_signal_handlers();
	while (1)
	{
		data->is_reading = true;
		prompt = get_prompt(data->env_ms);
		input = readline(prompt);
		exit_code = data->exit_code;
		free(prompt);
		if (!input)
		{
			free(input);
			handle_exit(NULL, NULL, data);
			break ;
		}
		if (*input)
			add_history(input);
		data->is_reading = false;
		get_argv(input, data);
	}
	return (exit_code);
}

// rl_already_prompted = 1;
int	main(int ac, char **av, char **envp)
{
	int		is_start;
	char	exit_code;
	t_data	data;

	is_start = 0;
	exit_code = 0;
	(void)ac;
	(void)av;
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	ft_bzero(&data, sizeof(t_data));
	ft_init(envp, &is_start, &data);
	get_data(&data);
	exit_code = main_loop(&data);
	return (exit_code);
}
