/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:23:02 by mzaian            #+#    #+#             */
/*   Updated: 2025/03/10 15:20:15 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

//IS
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		has_alpha(char *str);
int		has_elsethan(char *str, int (f)(int));
int		has_digits(char *str);

//LIST
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);

//MATH
size_t	ft_abs(long nbr);
int		ft_atoi(const char *nptr);
void	*ft_ternary(void *output1, void *output2, int condition);
int		ft_pow(int n, int pow);
int		get_lower_bound(int x, int n);
int		get_upper_bound(int x, int n);

//MEM
void	del_2d_array(void **array, int len);
void	del_3d_array(void ***array, int len, int *insidelens);
void	delchar(char **ptr);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_del(void *ptr);
void	*ft_memchr(void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_realloc(void *ptr, size_t size);

//PRINT
void	close_colored_output(int fd);
int		colorcode_by_str(char *color);
int		display_error(char *output);
void	ft_color_chars_but(int fd, char *output, int (f)(int), int colorcode);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	start_colored_output(int fd, int colorcode);

//STR
size_t	ft_insert_str(char **dest, char *src, int index);
char	*ft_itoa(int n);
char	**ft_split(const char *s, char c);
size_t	ft_strcat(char *dest, char *src);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnjoin(char *s1, const char *s2, int n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_substr(const char *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);

//PRINTF
int		handle_spaceplus(char *modifiers, long long n);
int		ft_put_ascii(int c, char *mods, const char *s);
int		ft_put_c(char c);
int		ft_put_di(long n, char *modifiers);
int		ft_put_ldli(long long n, char *modifiers);
int		ft_put_p(void *ptr, char *base, char *modifiers);
int		ft_put_s(char *str, char *modifiers);
int		ft_put_u(unsigned int n);
int		ft_put_x(unsigned long nbr, char *base, char *modifiers);
int		ft_printf(const char *str, ...);

//GNL
char	*get_next_line(int fd);

#endif