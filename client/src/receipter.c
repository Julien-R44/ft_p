/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receipter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/23 05:11:25 by y0ja              #+#    #+#             */
/*   Updated: 2015/07/23 18:25:25 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int		get_header_size(int sock)
{
	int		bytes_read;
	char	buf[2];
	char	header_size[10];
	int		j;
	int		in;

	j = -1;
	in = 0;
	while ((bytes_read = read(sock, buf, 1)))
	{
		buf[1] = 0;
		if (buf[0] == ';')
			break;
		if (in)
			header_size[++j] = buf[0];
		if (buf[0] == '=')
			in = 1;
	}
	header_size[++j] = 0;
	return (ft_atoi(header_size));
}

char	**gimme_last_header_part(int sock, int byte_left_header)
{
	char buf[byte_left_header + 1];
	int r;

	r = read(sock, buf, byte_left_header);
	buf[r] = 0;
	return (ft_strsplit(buf, ';'));
}

// Read the header then ascend the offset to the start of file
char	**read_header(int sock)
{
	char	**header;
	int		byte_left_header;

	byte_left_header = get_header_size(sock);
	header = gimme_last_header_part(sock, byte_left_header);
	return (header);
}

void	read2socket(int sock, int fd_out)
{
	int r;
	char buf[4096];

	while ((r = read(sock, buf, 4096)))
	{
		buf[r] = 0;
		ft_putstr_fd(buf, fd_out);
		if (buf[r-1] == '\0')
			break ;
	}
}
