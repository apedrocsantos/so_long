/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:37:31 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/20 12:17:14 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	buf[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*str;

	str = NULL;
	if (BUFFER_SIZE < 1 || read(fd, 0, 0) == -1)
	{
		if (fd >= 0 && fd <= FOPEN_MAX)
			ft_clean_buf(buf[fd]);
		return (NULL);
	}
	while (buf[fd][0] || read(fd, buf[fd], BUFFER_SIZE) > 0)
	{
		str = ft_strjoin_gnl(str, buf[fd]);
		if (ft_move_and_clean(buf[fd]))
			break ;
	}
	return (str);
}

/* int	main(void) */
/* { */
/* 	int		fd1; */
/* 	int		fd2; */
/* 	int		fd3; */
/* 	char	*str1; */
/* 	char	*str2; */
/* 	char	*str3; */

/* 	fd1 = open("test.txt", O_RDONLY); */
/* 	fd2 = open("test2.txt", O_RDONLY); */
/* 	fd3 = open("test3.txt", O_RDONLY); */
/* 	str1 = get_next_line(fd1); */
/* 	printf("%s", str1); */
/* 	free(str1); */
/* 	str2 = get_next_line(fd2); */
/* 	printf("%s", str2); */
/* 	free(str2); */
/* 	str3 = get_next_line(fd3); */
/* 	printf("%s", str3); */
/* 	free(str3); */
/* 	str1 = get_next_line(fd1); */
/* 	printf("%s", str1); */
/* 	free(str1); */
/* 	str2 = get_next_line(fd2); */
/* 	printf("%s", str2); */
/* 	free(str2); */
/* 	str3 = get_next_line(fd3); */
/* 	printf("%s", str3); */
/* 	free(str3); */
/* } */
