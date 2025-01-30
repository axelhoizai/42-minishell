/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:16:24 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/30 17:22:03 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_realine(void)
{
	char	*buffer;
	char	c;
	int		i;

	buffer = (char *)malloc(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	i = 0;
	c = 0;
	while (read(STDIN_FILENO, &c, 1) > 0 && c != '\n')
	{
		if (i < BUFFER_SIZE - 1)
			buffer[i++] = c;
		else
			break;
	}
	if (i == 0 && c == '\0')
	{
		free(buffer);
		return (NULL);
	}
	buffer[i] = '\0';
	return (buffer);
}

char	main_loop(char **argv, t_data *data)
{
	char	*input;
	char	*prompt;
	char	exit_code;

	while (1)
	{
		prompt = get_prompt(data->env_ms);
		if (!prompt)
			return (1);
		write(STDOUT_FILENO, prompt, ft_strlen(prompt));
		free(prompt);
		input = ft_realine();
		if (!input)
		{
			handle_exit(argv, data);
			break ;
		}
		argv = get_argv(input, data);
		free(input);
		exit_code = data->exit_code;
	}
	return (exit_code);
}

// char	main_loop(char **argv, t_data *data)
// {
// 	char	*input;
// 	char	*prompt;
// 	char	exit_code;

// 	while (1)
// 	{
		// prompt = get_promt();
// 		input = readline(prompt);
// 		exit_code = data->exit_code;
// 		free(prompt);
// 		if (!input)
// 		{
// 			free(input);
// 			handle_exit(argv, data);
// 			break ;
// 		}
// 		if (*input)
// 			add_history(input);
// 		argv = get_argv(input, data);
// 		free(input);
// 	}
// 	return (exit_code);
// }

int	main(int ac, char **av, char **envp)
{
	char	**argv;
	int		is_start;
	char	exit_code;
	t_data	data;

	is_start = 0;
	exit_code = 0;
	(void)ac;
	(void)av;
	argv = NULL;
	ft_bzero(&data, sizeof(t_data));
	ft_init(envp, &is_start, &data);
	signal(SIGINT, handle_sigint);
	if (ac > 1)
		sh_tester(NULL, &data);
	exit_code = main_loop(argv, &data);
	return (exit_code);
}
