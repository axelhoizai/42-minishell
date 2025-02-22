/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 23:18:58 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/22 17:26:54 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_whitespace(const char *str, int *i)
{
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
}

static bool	tokenize_string(char *str, char **tokens, int *count, t_data *data)
{
	int		i;
	// char	*token;
	t_tok	*token;

	i = 0;
	while (str[i])
	{
		skip_whitespace(str, &i);
		if (str[i])
		{
			token = parse_token(str, &i, data);
			if (!token)
				return (free_tokens(tokens), false);
			if (!ft_isspace(token[0]) && ft_strlen(token) > 0)
				tokens[(*count)++] = token;
			else if (token)
				free(token);
		}
	}
	tokens[*count] = NULL;
	if (*count == 0)
		return (free_tokens(tokens), false);
	return (true);
}

static char	**parse_args(char *str, t_data *data)
{
	char	**tokens;
	int		count;

	if (!str || check_unclosed_quotes(str))
		return (ft_print_error(NULL, NULL, "Error: unclosed quotes"), NULL);
	tokens = malloc(sizeof(char *) * 256);
	if (!tokens)
		return (NULL);
	count = 0;
	if (!tokenize_string(str, tokens, &count, data))
		return (NULL);
	print_tab(tokens);
	return (tokens);
}

//? Get the input and 
void	get_argv(char *input, t_data *data)
{
	char	**argv;
	int		argc;

	argv = NULL;
	argc = 0;
	argv = parse_args(input, data);
	if (!input)
		return ;
	if (argv && !argv[0])
	{
		free(argv);
		data->exit_code = 0;
		return ;
	}
	while (argv && argv[argc])
		argc++;
	if (argc > 0)
	{
		send_to_exec(argv, data);
		return ;
	}
}
