/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/23 02:21:07 by y0ja              #+#    #+#             */
/*   Updated: 2015/07/26 01:19:30 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	send_cmd2server(int sock, char *cmd)
{
	write(sock, cmd, ft_strlen(cmd));
	write(sock, "\n", 1);
}

static void		send_file(int cs, int fd)
{
	char	buf[4096];
	int		r;
	void	*ptr;
	int		byte_write;

	while ((r = read(fd, buf, sizeof(buf))))
	{
		ptr = buf;
		while (r > 0)
		{
			byte_write = write(cs, ptr, r);
			r -= byte_write;
			ptr += byte_write;
		}
	}
	close(fd);
}

int				cmd_put_file(t_request *req, int sock)
{
	int fd;

	if (!req->args[1])
		return (usage(PUT));
	fd = open(req->args[1], O_RDONLY);
	if (fd == -1)
		printf("ERROR 550 : No such file or permission denied.\n");
	else
	{
		send_cmd2server(sock, req->buf);
		// send_file(sock, fd);
		write(sock, "fdp", 4);
		write(sock, "\0", 1);
		printf("SUCESS : [%s] uploaded.\n", req->args[1]);
	}
	return (0);
}

int		cmd_get_file(t_request *req, int sock)
{
	int		fd;
	int		error;
	char	**header;

	if (!req->args[1])
		return (usage(GET));
	send_cmd2server(sock, req->buf);
	header = read_header(sock);
	error = atoi(get_field_value_header(header[ERROR]));
	if (error == 550)
		return (ft_protocol_error(sock, error));
	fd = open(req->args[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IWGRP | S_IRGRP | S_IROTH);
	if (fd == -1)
		return (ft_protocol_error(sock, 550));
	read2socket(sock, fd);
	close(fd);
	printf("SUCESS : [%s] received.\n", req->args[1]);
	return (0);
}

