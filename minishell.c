/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:16:24 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/27 13:44:36 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_init(char **envp, int *is_start, t_data *data)
{
	char	*path_tmp;

	path_tmp = NULL;
	if (*is_start == 0)
	{
		data->exit_code = 0;
		data->is_reading = 0;
		init_env_ms(envp, data);
		*is_start = 1;
		path_tmp = getcwd(NULL, 0);
		data->oldpwd = ft_strdup(path_tmp);
		data->pwd = ft_strdup(path_tmp);
		free_var(path_tmp);
	}
}

static int	main_loop(t_data *data)
{
	char	*input;
	char	*prompt;
	int		exit_code;

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
		input_lexer(input, data);
	}
	return (exit_code);
}

int	main(int ac, char **av, char **envp)
{
	int		is_start;
	int		exit_code;
	t_data	data;

	(void)ac;
	(void)av;
	is_start = 0;
	exit_code = 0;
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	ft_bzero(&data, sizeof(t_data));
	ft_init(envp, &is_start, &data);
	get_data(&data);
	exit_code = main_loop(&data);
	return (exit_code);
}
