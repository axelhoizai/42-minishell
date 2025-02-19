/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 23:18:58 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/19 19:03:25 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	skip_whitespace(const char *str, int *i)
{
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
}

//? Remove all whitespaces and quotes
static char	**parse_args(char *str, t_data *data)
{
	char	**tokens;
	char	*token;
	int		i;
	int		count;

	if (!str || check_unclosed_quotes(str))
		return (write(2, "Error: unclosed quotes\n", 23), NULL);
	tokens = malloc(sizeof(char *) * 256);
	if (!tokens)
		return (NULL);
	i = 0;
	count = 0;
	while (str[i])
	{
		skip_whitespace(str, &i);
		if (str[i])
		{
			if (str[i] == '|' && str[i + 1] == '|')
			{
				token = ft_substr(str, i, 2);
				i+=2;
			}
			else if ((str[i] == '<' || str[i] == '>' || str[i] == '|') && str[i + 1] != '|')
			{
				token = ft_calloc(2, 1);
				token[0] = str[i];
				i++;
			}
			else
				token = parse_token(str, &i, data, tokens);			
			if (!token)
				return (free_tokens(tokens), NULL);
			tokens[count++] = token;
		}
	}
	tokens[count] = NULL;
	print_tab(tokens);
	return (tokens);
}

//? Parse builtins to removes quotes and parse dollars
static void	process_builtins(char *builtins, t_data *data)
{
	char	**argv;
	int		argc;

	argv = NULL;
	argc = 0;
	argv = parse_args(builtins, data);
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
		send_to_exec(argc, argv, data);
		return ;
	}
}

//? Get the input and 
void	get_argv(char *input, t_data *data)
{
	char	*token;	

	if (!input)
		return ;
	input = replace_double_ampersand(input);
	if (ft_strchr(input, '\n'))
	{
		token = ft_strtok(input, "\n");
		while (token)
		{
			process_builtins(token, data);
			if (data->exit_code > 0)
				break ;
			token = ft_strtok(NULL, "\n");
		}
	}
	else
		process_builtins(input, data);
	free(input);
}
