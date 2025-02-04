/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 03:43:31 by kalicem           #+#    #+#             */
/*   Updated: 2025/02/02 04:06:40 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H
# define FT_READLINE_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <termios.h>

#ifdef ESC
# undef ESC
#endif
# define ESC '['
# define BACKSPACE 127
# define ENTER '\n'
# define ARROW_UP 'A'
# define ARROW_DOWN 'B'
# define CTRLC 3
# define CTRLD 4
# define HISTORY_FILE ".minishell_history"
# define MAX_HISTORY 100
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char	*ft_readline(char *prompt);

typedef struct s_data_term
{
	struct termios original_term;
} t_data_term;

typedef struct s_history
{
	char	*entries[MAX_HISTORY];
	
	char	**history_tab;
	int		history_count;
	int		history_index;
}	t_history;

typedef struct s_rl
{
	char 		*buffer;
	char		*prompt;
	int			prompt_len;
	t_history	*history;
	t_data_term	*term;
}	t_rl;

void		init_readline(t_rl *readline);

void		save_terminal_settings(t_data_term *term);
void		restore_terminal_settings(t_data_term *term);

//utils_readline
void		enable_raw_mode(t_data_term *term);
void		disable_raw_mode(t_data_term *term);
// t_data		*get_data(t_data *new_data);
t_data_term	*get_term_data(t_data_term *new_term);
void   		ft_readline_redisplay(void);

//readline_signal
void		setup_signals(void);

//readline history
void		add_to_history(char *cmd, t_history *history);
void 		load_history(t_history *history);
void		free_history(t_history *history);
// char		*ft_realine(t_rl *readline);
void		free_readline(t_rl *readline);

#endif