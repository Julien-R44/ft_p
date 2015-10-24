/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sender.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/23 19:18:12 by y0ja              #+#    #+#             */
/*   Updated: 2015/07/23 19:18:18 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void	send_header(int sock, char *error)
{
	char	*header;
	char	*header_size_str;

	header = ft_kebab("ERROR=", error, ";", NULL);
	header_size_str = ft_itoa(ft_strlen(header));
	free(header);
	header = ft_kebab("HEADER_SIZE=", header_size_str, ";", "ERROR=", error, ";", NULL);
	free(header_size_str);
	ft_putstr_fd(header, sock);
}

void	send_file(int cs, int fd)
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

int		file_is_valid(int fd)
{
	struct stat buf;

	if (fstat(fd, &buf) == -1)
		return (-1);
	if (S_ISREG(buf.st_mode))
		return (0);
	close(fd);
	return (-1);
}
