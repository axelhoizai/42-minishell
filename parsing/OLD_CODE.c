#include "minishell.h"

bool	chck_redir_pip(char *line, int *i)
{
	if (line[*i] == '>' && line[*i + 1] == '|' && line[*i + 2] != '|')
	{
		line[*i + 1] = '>';
		(*i)++;
		return (true);
	}
	return (false);
}

//? Big function handling parsing
char	*parse_token(char *line, int *i, t_data *data)
{
	t_parse	parse;

	init_parse(&parse, 256);
	while (line[*i] && (parse.in_single || parse.in_double
			|| !ft_isspace(line[*i])))
	{
		if (*i > 0 && (line[*i] == '|' && ft_strncmp(line, "export", 6) != 0))
			return (parse.buffer);
		if ((line[*i] == '<' && line[*i + 1] != '<') || (line[*i] != '<' && line[*i + 1] == '<'))
		{
			append_char(&parse, line[*i]);
			(*i)++;
			return (parse.buffer);
		}
		if (chck_redir_pip(line, i))
			continue ;
		if (chck_quote_state(line, i, &parse))
			continue ;
		handle_parse_token(line, i, &parse);
		if (handle_check_var(line, i, data, &parse))
			continue ;
		check_closing_quote(line, i, &parse);
		(*i)++;
	}
	return (parse.buffer);
}

// static char	*skip_pips(char *str, int *i)
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
// 			token = skip_pips(str, &i);
// 			if (!token)
// 				token = parse_token(str, &i, data);
// 			if (!token)
// 				return (free_tokens(tokens), false);
// 			tokens[(*count)++] = token;
// 		}
// 	}
// 	tokens[*count] = NULL;
// 	return (true);
// }

static bool	chk_next_tok(char **tokens, int *i)
{
	char	*trim2;

	trim2 = ft_strtrim(tokens[*i + 1], "<|>");
	if (trim2[0] == '\0' && !tokens[*i + 2])
	{
		ft_print_error(NULL, NULL, MSG_ERROR_SYNTAX);
		free(trim2);
		return (false);
	}
	free(trim2);
	return (true);
}

bool	check_redir_pipe(char **tokens)
{
	int		i;
	char	*trim;

	i = 0;
	while (tokens[i])
	{
		trim = ft_strtrim(tokens[i], "<|>");
		if (tokens[i][0] && trim[0] == '\0' && ft_strncmp(tokens[i], "||", 2))
		{
			if (!tokens[i + 1])
			{
				ft_print_error(NULL, NULL, MSG_ERROR_SYNTAX);
				return (free(trim), false);
			}
			else if (chk_next_tok(tokens, &i) == false)
			{
				free(trim);
				return (false);
			}
		}
		i++;
		free(trim);
	}
	return (true);
}