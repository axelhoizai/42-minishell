/* ************************************************************************** */
/*		                                                                    */
/*                                                        :::      ::::::::   */
/*   ft_readline_termimal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:07:17 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/04 10:08:03 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	enable_raw_mode(t_data_term *term)
{
	struct termios raw;

	if (tcgetattr(STDIN_FILENO, &term->original_term) == -1)
	{
		perror("tcgetattr");
		exit(1);
	}
	raw = term->original_term;
	raw.c_lflag &= ~(ECHO | ICANON);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &raw) == -1)
	{
		perror("tcsetattr");
		exit(1);
	}
}

void	disable_raw_mode(t_data_term *term)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term->original_term) == -1)
	{
		perror("tcsetattr");
		exit(1);
	}
}

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

int	get_prompt_length(char *prompt)
{
	int		len;
	bool	in_escape;

	len = 1;
	in_escape = false;
	while (*prompt)
	{
		if (*prompt == '\033')
			in_escape = true;
		else if (in_escape && *prompt == 'm')
			in_escape = false;
		else if (!in_escape)
			len++;
		prompt++;
	}
	return (len);
}
