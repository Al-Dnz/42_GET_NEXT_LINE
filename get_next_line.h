#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H


# include <stdlib.h>
# include <unistd.h>

typedef struct	s_list
{
	int		fd;
	char	*storage;
	struct	s_list	*next;
}				t_list;

int		get_next_line(int fd, char **line);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);

char	*ft_strnew(size_t size);

char	*ft_strchr(const char *s, int c);

char	*ft_strcpy(char *dest, char *src);
void	ft_strclr(char *s);
int		ft_strlen(char *s);

#endif
