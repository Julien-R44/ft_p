/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/23 02:15:19 by y0ja              #+#    #+#             */
/*   Updated: 2015/07/25 21:25:36 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

// Empty and redirect the shit from socket to /dev/null
int		ft_protocol_error(int sock, int er)
{
	int fd;

	fd = open("/dev/null", O_WRONLY);
	if (er == 550)
		printf("ERROR 550 : No such file or permission denied.\n");
	read2socket(sock, fd);
	close(fd);
	return (-1);
}

// Return the value from a header's string formated like ERROR=550;
char	*get_field_value_header(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i-1] != '=')
		i++;
	return (&str[i]);
}

int		usage(int cmd)
{
	printf("usage: ");
	if (cmd == CLIENT)
		printf("./client <addr> <port>\n");
	else if (cmd == GET)
		printf("get <filename> [new filename]\n");
	else if (cmd == PUT)
		printf("put <filename> [new filename]\n");
	return (0);
}

pid_t	secure_fork(void)
{
	pid_t child;

	if ((child = fork()) == -1)
		ft_error(FORK);
	return (child);
}

void	ft_error(int er)
{
	if (er == FORK)
		printf("Fork(2) failed.\n");
	if (er == CONNECT)
		printf("Connect(2) failed.\n");
	if (er == SOCKET)
		printf("Socket(2) failed.\n");
	if (er == HOSTBYNAME)
		printf("gethostbyname(3) failed.\n");
	exit(-1);
}
