/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:16:24 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/30 18:27:58 by ahoizai          ###   ########.fr       */
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
	(void)argv;

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
		// free_tab(argv);
		// data->argv = argv;
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
	int		is_start;
	char	exit_code;
	t_data	data;

	is_start = 0;
	exit_code = 0;
	(void)ac;
	(void)av;
	ft_bzero(&data, sizeof(t_data));
	ft_init(envp, &is_start, &data);
	signal(SIGINT, handle_sigint);
	if (ac > 1)
		sh_tester(NULL, &data);
	exit_code = main_loop(NULL, &data);
	return (exit_code);
}

// ==490092== 3,474 bytes in 54 blocks are still reachable in loss record 40 of 65
// ==490092==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==490092==    by 0x406DD8: ft_strjoin (ft_strjoin.c:23)
// ==490092==    by 0x405E38: lst_to_tab (utils_list2.c:72)
// ==490092==    by 0x404CA3: init_env_ms (builtins_env.c:59)
// ==490092==    by 0x405EC7: ft_init (utils_data.c:20)
// ==490092==    by 0x40140B: main (minishell.c:54)
// ==490092== 
