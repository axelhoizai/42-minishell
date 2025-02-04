/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:04:47 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/03 04:49:53 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <fcntl.h>
# include <stdarg.h>

// # include <stdio.h>
// # include <bsd/string.h>

//ft_is
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_isspace(int c);
int				ft_isnumeric(const char *str);

//ft_lst
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstnew(void *content);
int				ft_lstsize(t_list *lst);

//ft_mem
void			*ft_realloc(void *ptr, size_t size);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp( const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);

//ft_printf
int				ft_printf(const char *str, ...);
int				ft_print_char(char c);
int				ft_print_str(char *s);
int				ft_print_nbr(int n);
int				ft_print_hex(unsigned int number, int upper_case);
int				ft_print_ptr(unsigned long ptr, int first);
int				ft_print_unsigned(unsigned int n);

//ft_put
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

//ft_str
char			**ft_split(char const *s, char c);
char			*ft_strcat(char *dest, char *src);
char			*ft_strcpy(char *dest, char *src);
char			*ft_strchr(const char *s, int c);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strdup(const char *s);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			_strlen(const char *s);
char			t_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strstr(char *str, char *to_find);
char			*ft_strrchr(const char *s, int c);
char			*ft_strtok(char *str, const char *delim);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);

//ft_to
int				ft_atoi(const char *nptr);
long			ft_atol(const char *str);
char			*ft_itoa(int n);
int				ft_toupper(int c);
int				ft_tolower(int c);

//get_next_line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

# define FD_MAX 1024

char			*get_next_line(int fd);
void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_strjoin_gnl(char *s1, char *s2);
char			*ft_strchr(const char *s, int c);

size_t			ft_strlen(const char *s);
char			*ft_strdup_gnl(const char *s, size_t len);

//int_to_argb
typedef struct s_color
{
	unsigned int	hex;
	int				r;
	int				g;
	int				b;
	int				a;
}			t_color;

t_color			ft_int_to_rgb(unsigned int color);

//hex_to_uint
unsigned int	ft_hex_to_uint(const char *hex);

#endif
