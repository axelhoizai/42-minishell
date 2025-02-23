// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   argv_parser.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/01/24 23:18:58 by mdemare           #+#    #+#             */
// /*   Updated: 2025/02/22 18:56:43 by kalicem          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../minishell.h"

// void	skip_whitespace(const char *str, int *i)
// {
// 	while (str[*i] && ft_isspace(str[*i]))
// 		(*i)++;
// }

// char	*skip_pips(char *str, int *i)
// {
// 	char	*token;

// 	token = NULL;
// 	if ((str[*i] == '|' && str[*i + 1] == '|')
// 		|| (str[*i] == '>' && str[*i + 1] == '>'))
// 	{
// 		token = ft_substr(str, *i, 2);
// 		*i += 2;
// 	}
// 	else if (str[*i] == '<' && str[*i + 1] == '|')
// 	{
// 		token = ft_calloc(2, 1);
// 		token[0] = str[*i];
// 		(*i)++;
// 	}
// 	else if ((str[*i] == '>' || str[*i] == '|') && str[*i + 1] != '|')
// 	{
// 		token = ft_calloc(2, 1);
// 		token[0] = str[*i];
// 		(*i)++;
// 	}
// 	return (token);
// }

// // static bool	tokenize_string(char *str, char **tokens, int *count, t_data *data)
// // {
// // 	int		i;
// // 	char	*token;

// // 	i = 0;
// // 	while (str[i])
// // 	{
// // 		skip_whitespace(str, &i);
// // 		if (str[i])
// // 		{
// // 			token = skip_pips(str, &i);
// // 			if (!token)
// // 				token = parse_token(str, &i, data);
// // 			if (!token)
// // 				return (free_tokens(tokens), false);
// // 			tokens[(*count)++] = token;
// // 		}
// // 	}
// // 	tokens[*count] = NULL;
// // 	return (true);
// // }

// static bool	tokenize_string(char *str, char **tokens, int *count, t_data *data)
// {
// 	int		i;
// 	char	*token;

// 	i = 0;
// 	while (str[i])
// 	{
// 		skip_whitespace(str, &i);
// 		if (str[i])
// 		{
// 			// token = skip_pips(str, &i);
// 			// if (!token)
// 				token = parse_token(str, &i, data);
// 			if (!token)
// 				return (free_tokens(tokens), false);
// 			// if (!ft_isspace(token[0]) && ft_strlen(token) > 0)
// 			tokens[(*count)++] = token;
// 			// else if (token)
// 			// 	free(token);
// 		}
// 	}
// 	tokens[*count] = NULL;
// 	if (*count == 0)
// 		return (free_tokens(tokens), false);
// 	return (true);
// }

// static char	**parse_args(char *str, t_data *data) //lexer
// {
// 	char	**tokens;
// 	int		count;

// 	if (!str || check_unclosed_quotes(str))
// 		return (ft_print_error(NULL, NULL, "Error: unclosed quotes"), NULL);
		
// 	tokens = malloc(sizeof(char *) * 256);
// 	if (!tokens)
// 		return (NULL);
// 	count = 0;
// 	if (!tokenize_string(str, tokens, &count, data))
// 		return (NULL);
// 	print_tab(tokens); //print_tab
// 	return (tokens);
// }

// //? Get the input and 
// void	get_argv(char *input, t_data *data) //lexer
// {
// 	char	**argv;
// 	int		argc;

// 	argv = NULL;
// 	argc = 0;
// 	argv = parse_args(input, data);
// 	if (!input)
// 		return ;
// 	if (argv && !argv[0])
// 	{
// 		free(argv);
// 		data->exit_code = 0;
// 		return ;
// 	}
// 	while (argv && argv[argc])
// 		argc++;
// 	if (argc > 0)
// 	{
// 		send_to_exec(argv, data);
// 		return ;
// 	}
// }
