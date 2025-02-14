/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:16:24 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/14 15:32:38 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	main_loop(t_data *data)
{
	char	*input;
	char	*prompt;
	char	exit_code;

	configure_terminal();
	while (1)
	{
		prompt = get_prompt(data->env_ms);
		setup_signal_handlers();
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
		get_argv(input, data);
		// free(input);
		free_var(input);
	}
	unconfigure_terminal();
	return (exit_code);
}

int	main(int ac, char **av, char **envp)
{
	int		is_start;
	char	exit_code;
	t_data	data;

	is_start = 0;
	exit_code = 0;
	(void)ac;
	(void)av;
	ft_bzero(&data, sizeof(t_data));
	ft_init(envp, &is_start, &data);
	get_data(&data);
	// signal(SIGINT, handle_sigint);
	// if (ac > 1)
	// 	sh_tester(NULL, &data);
	exit_code = main_loop(&data);
	return (exit_code);
}
