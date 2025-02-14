/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:16:24 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/14 18:56:31 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	main_loop(t_data *data)
{
	char	*input;
	char	*prompt;
	char	exit_code;

	setup_signal_handlers();
	while (1)
	{
		configure_terminal();
		prompt = get_prompt(data->env_ms);
		input = readline(prompt);
		exit_code = data->exit_code;
		free(prompt);
		if (!input)
		{
			free(input);
			handle_exit(NULL, data);
			break ;
		}
		if (*input)
			add_history(input);
		unconfigure_terminal();
		get_argv(input, data);
		free_var(input);
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
