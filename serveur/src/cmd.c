/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/22 22:21:55 by y0ja              #+#    #+#             */
/*   Updated: 2015/07/26 01:14:47 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void	exec_binary(char **args, int sock)
{
	pid_t		child;

	child = secure_fork();
	if (child == 0)
	{
		if (dup2(sock, STDOUT_FILENO) == -1)
			ft_error(DUP);
		if (dup2(sock, STDERR_FILENO) == -1)
			ft_error(DUP);
		execve("/bin/ls", args, NULL);
	}
	else
	{
		waitpid(child, NULL, 0);
		write(sock, "\0", 1);
	}
}

int		cmd_get_file(t_request *req, int sock)
{
	int		fd;

	fd = open(req->args[1], O_RDONLY);
	if (fd == -1 || file_is_valid(fd) == -1)
		send_header(sock, "550");
	else
	{
		send_header(sock, "0");
		send_file(sock, fd);
	}
	write(sock, "\0", 1);
	return (0);
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

int		cmd_put_file(t_request *req, int sock)
{
	int fd;

	printf("PUT FILE\n");
	// fd = open(req->args[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IWGRP | S_IRGRP | S_IROTH);
	// if (fd == -1)
	// {
		// printf("ERROR FD\n");
		// return (-1);
	// }
	read2socket(sock, 2);
	// close(fd);
	printf("END PUT BRUH\n");
	return (0);
}

int		cmd_pwd(t_request *req, int sock)
{
	write(sock, req->dir_cur, ft_strlen(req->dir_cur));
	write(sock, "\0", 1);
	return (0);
}

int		cmd_list_files(t_request *req, int sock)
{
	exec_binary(req->args, sock);
}

int		permission_denied(t_request *req)
{
	char buf[PATH_MAX] = {0};

	getcwd(buf, sizeof(buf));
	if (ft_strncmp(req->dir_root, buf, ft_strlen(req->dir_root)) != 0)
		return (1);
	return (0);
}

int		cmd_change_dir(t_request *req, int sock)
{
	char	*go_to;
	char	*save;

	save = ft_strdup(req->dir_cur);
	go_to = req->args[1];
	if (chdir(go_to) == -1)
		write(sock, "ERROR", 6);
	else
	{
		if (permission_denied(req) == 1)
		{
			write(sock, "ERROR", 6);
			chdir(save);
			free(save);
			return (-1);
		}
		write(sock, "SUCESS", 7);
	}
	free(save);
	write(sock, "\0", 1);
	return (0);
}
