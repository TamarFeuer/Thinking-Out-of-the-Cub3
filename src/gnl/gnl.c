#include "../../inc/gnl.h"
// #include "../../inc/game.h"


# define BUFFER_SIZE 10

typedef	enum e_gnl_ecode
{
	SUCCESS,
	ERR_INIT,
	ERR_READ,
	ERR_MALLOC,
}	t_gnl_ecode;

typedef struct s_lst
{
	char buffer[BUFFER_SIZE];

}	t_lst;

typedef struct s_data
{
	t_gnl_ecode	err_no;
}	t_data;

char	*get_next_line(t_data *data, int fd);

int	main(void)
{
	t_data	data;
	int		fd;

	fd = open("tests/gnl.txt", O_RDONLY);
	printf("FD is: %i\n", fd);
	get_next_line(&data, fd);
	return (0);
}

char	*get_next_line(t_data *data, int fd)
{
	static char	*rem;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		data->err_no = ERR_INIT;
		return (NULL);
	}


	if (!rem)
	{
		read_until_nl_or_eof();
	}
	else if (rem && ft_hasnl(rem))
	{
		//don't read at all, we have all we need in the remainder. We just need to split it.
	}
}

void	read_until_nl_or_eof(t_data *data, int fd, char **line, char **rem)
{
	char	*buffer;
	int		bytes_read;

	buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		data->err_no = ERR_MALLOC;
		return ;
	}

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			data->err_no = ERR_READ;
			free(buffer);
			return ;
		}
		else if (bytes_read == 0)
		{
			free(buffer);
			return ;
		}
		else
		{
			if (!ft_hasnl(buffer))
			{
				
			}
		}
	}

}


























































// char	*get_next_line(int fd)
// {
// 	static char	*rem = NULL;
// 	char		*line;

// 	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
// 		return (gnl_free(&rem));
// 	if (rem && ft_checknl(rem) >= 0)
// 		return (ft_parse(&rem));
// 	ft_read(fd, &rem);
// 	if (!rem)
// 		return (NULL);
// 	else if (rem && ft_checknl(rem) >= 0)
// 		return (ft_parse(&rem));
// 	else if (rem && rem[0] == '\0')
// 		return (gnl_free(&rem));
// 	else
// 	{
// 		line = ft_strdup(rem);
// 		gnl_free(&rem);
// 		return (line);
// 	}
// }

// char	*ft_parse(char **rem)
// {
// 	char	*line;
// 	char	*new_rem;

// 	new_rem = ft_get_new_rem(*rem);
// 	line = ft_get_nl_line(*rem);
// 	gnl_free(rem);
// 	*rem = new_rem;
// 	return (line);
// }

// char	*ft_get_new_rem(char *rem)
// {
// 	ssize_t	nl_index;
// 	ssize_t	rem_len;
// 	char	*new_rem;
// 	ssize_t	i;

// 	nl_index = ft_checknl(rem);
// 	rem_len = ft_strlen(rem);
// 	if (nl_index < 0 || rem_len == 0 || nl_index == rem_len)
// 		return (NULL);
// 	new_rem = (char *) malloc(rem_len - nl_index + 1);
// 	if (!new_rem)
// 	{
// 		perror("ft_get_new_rem");
// 		exit(EXIT_FAILURE);
// 	}
// 	i = 0;
// 	while (rem && rem[i] && i < (rem_len - nl_index))
// 	{
// 		new_rem[i] = rem[nl_index + 1 + i];
// 		i++;
// 	}
// 	new_rem[i] = '\0';
// 	return (new_rem);
// }

// char	*ft_get_nl_line(char *rem)
// {
// 	char	*line;
// 	ssize_t	line_len;
// 	ssize_t	i;

// 	line_len = ft_checknl(rem);
// 	if (line_len < 0 || !rem)
// 		return (NULL);
// 	line = malloc(line_len + 2);
// 	if (!line)
// 		return (NULL);
// 	i = 0;
// 	while (rem && rem[i] && i < line_len)
// 	{
// 		line[i] = rem[i];
// 		i++;
// 	}
// 	line[i++] = '\n';
// 	line[i] = '\0';
// 	return (line);
// }

// void	ft_read(int fd, char **rem)
// {
// 	char	*buffer;
// 	ssize_t	bytes_read;
// 	char	*temp;

// 	buffer = (char *) malloc(BUFFER_SIZE + 1);
// 	if (!buffer)
// 		return ;
// 	buffer[0] = '\0';
// 	bytes_read = 1;
// 	while (bytes_read > 0) // && ft_checknl(buffer) < 0
// 	{
// 		bytes_read = read(fd, buffer, BUFFER_SIZE);
// 		if (bytes_read < 0)
// 		{
// 			gnl_free(rem);
// 			free(buffer);
// 			return ;
// 		}
// 		buffer[bytes_read] = '\0';
// 		temp = ft_strjoin(*rem, buffer);
// 		gnl_free(rem);
// 		*rem = temp;
// 	}
// 	free(buffer);
// }
