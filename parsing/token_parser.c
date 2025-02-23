/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 02:46:56 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/23 14:24:32 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_argv(t_argv *argv, char *token)
{
	char	**new_tokens;
	int		i;

	if (!argv || !token)
		return ;
	if (argv->token_count >= argv->token_capacity)
	{
		argv->token_capacity *= 2;
		new_tokens = ft_calloc(argv->token_capacity, sizeof(char *));
		if (!new_tokens)
			return ;
		i = 0;
		while (i < argv->token_count)
		{
			new_tokens[i] = argv->tokens[i];
			i++;
		}
		free(argv->tokens);
		argv->tokens = new_tokens;
	}
	argv->tokens[argv->token_count] = ft_strdup(token);
	argv->token_count++;
}

void	process_token(t_argv *argv, char *lexingv, int i, t_data *data)
{
	char	*token;

	skip_whitespace(lexingv, &i);
	token = skip_pips(lexingv, &i);
	if (token)
	{
		append_argv(argv, token);
		free(token);
		return ;
	}
	token = parse_token(lexingv, &i, data);
	if (!token || *token == '\0')
	{
		free(token);
		return ;
	}
	if (chck_redir_pip(token, &i))
	{
		append_argv(argv, token);
		free(token);
		return ;
	}
	append_argv(argv, token);
	free(token);
}

int	check_pipe_syntax(t_argv *argv, t_data *data)
{
	if (argv->token_count > 0
		&& is_token_pipe(argv->tokens[argv->token_count - 1]))
	{
		ft_print_error(NULL, NULL, "Syntax error: pipe at end of command");
		free_argv(argv);
		data->exit_code = 2;
		return (1);
	}
	return (0);
}

void	parse_argv(char ***lexingv, int *lexingc, t_data *data)
{
	t_argv	argv;
	int		i;

	init_argv(&argv, 10);
	i = 0;
	while (i < *lexingc)
	{
		if (!(*lexingv)[i])
		{
			i++;
			continue ;
		}
		process_token(&argv, (*lexingv)[i], i, data);
		i++;
	}
	if (check_pipe_syntax(&argv, data))
		return ;
	if (argv.token_count > 0)
	{
		free_tab(*lexingv);
		*lexingv = argv.tokens;
		*lexingc = argv.token_count;
	}
	else
		free_argv(&argv);
}
