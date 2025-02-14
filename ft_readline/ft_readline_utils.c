/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:47:47 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/14 13:22:58 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	*get_data(t_data *new_data)
{
	static t_data	*data = NULL;

	if (new_data)
		data = new_data;
	return (data);
}

t_data_term	*get_term_data(t_data_term *new_term)
{
	static t_data_term term;

	if (new_term) 
		term = *new_term;
	return (&term);
}

// t_pipeline	*get_pipeline(t_pipeline *new_pip)
// {
// 	static t_pipeline pip;

// 	if (new_pip) 
// 		pip = *new_pip;
// 	return (&pip);
// }

int actual_prompt_length(char *str)
{
	int i = 0, len = 0;
	while (str[i])
	{
		if (str[i] == '\033')
		{
			while (str[i] && str[i] != 'm')
			  i++;
		}
		else
			len++;
		i++;
	}
	return (len);
}

// int	get_prompt_length(char *prompt)
// {
// 	int		len;
// 	bool	in_escape;

// 	len = 1;
// 	in_escape = false;
// 	while (*prompt)
// 	{
// 		if (*prompt == '\033')
// 			in_escape = true;
// 		else if (in_escape && *prompt == 'm')
// 			in_escape = false;
// 		else if (!in_escape)
// 			len++;
// 		prompt++;
// 	}
// 	return (len);
// }

void	print_prompt(t_rl *rl)
{
	get_cursor_position(rl);
	rl->prompt_row = rl->term->cursor_row;
	printf("%s", rl->prompt);
	printf("\033[C\033[J");
}
