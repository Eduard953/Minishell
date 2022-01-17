/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 15:21:27 by pstengl           #+#    #+#             */
/*   Updated: 2022/01/17 15:03:25 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *nptr);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isupper(int c);
int		ft_islower(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(const char *s, size_t start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(const char *s1, const char *set);
char	**ft_split(const char *s, const char c);
char	*ft_itoa(int n);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
/*
** BONUS
*/
/*
** From PDF:
*/
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
/*
** Own Functions:
*/
void	ft_lstadd(t_list **lst, void *content);
t_list	*ft_lstat(t_list *lst, int n);
void	ft_lstdelat(t_list **lst, int n, void (*f)(void *));
char	**ft_lsttoarr(t_list *lst);
int		ft_pow(int base, int exp);
int		ft_sqrt(int nb);
char	*ft_itobase(int nb, const char *base);
char	*ft_itohex(int n);
char	*ft_itobin(int n);
char	*ft_itooct(int n);
int		ft_basetoi(const char *str, const char *base);
int		ft_hextoi(const char *str);
int		ft_octtoi(const char *str);
int		ft_bintoi(const char *str);
int		ft_printc(char c);
int		ft_print(char *str);
int		ft_println(char *str);
int		ft_printint(int n);
int		ft_printintarr(int *n, size_t len);
int		ft_printlst(t_list *lst);
int		ft_printinthex(int n);
int		ft_printintoct(int n);
int		ft_printintbin(int n);
int		ft_printintbase(int n, const char *base);
int		ft_printarr(char **arr);
int		ft_isspace(char c);
int		ft_isoneof(const char c, const char *ref);
char	*ft_strext(char **base, char *ext, size_t size);
int		ft_max(const int num1, const int num2);
int		ft_min(const int num1, const int num2);
int		ft_abs(const int num);
int		ft_printuint(unsigned int n);
char	*ft_uitobase(unsigned int num, char *base);
int		ft_strcmp(const char *s1, const char *s2);

#endif
