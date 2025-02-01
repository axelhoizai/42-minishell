/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:34:22 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/31 16:25:30 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void enable_raw_mode(t_data_term *term)
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

void disable_raw_mode(t_data_term *term)
{
    if (tcsetattr(STDIN_FILENO, TCSANOW, &term->original_term) == -1)
    {
        perror("tcsetattr");
        exit(1);
    }
}

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

void	handle_sigint(int sig)
{
	(void)sig;
	signal(SIGQUIT, SIG_IGN);
	write(STDOUT_FILENO, "^C\n", 3);
	ft_readline_redisplay();
}

void	ft_readline_redisplay(void)
{
	t_data		*data;
	t_data_term	*term;
	char		*prompt;

	data = get_data(NULL);
	if (!data)
		return;
	term = get_term_data(NULL);
	if (!term)
		return;
	data->term = term;
	
	// restore_terminal_settings(term);
	prompt = get_prompt(data->env_ms);
	if (!prompt)
		return;
	write(STDOUT_FILENO, "\r\033[K", 4);
	write(STDOUT_FILENO, prompt, ft_strlen(prompt));
	free(prompt);
	// enable_raw_mode(&term->original_term);
}