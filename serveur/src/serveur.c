/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/26 05:53:13 by jripoute          #+#    #+#             */
/*   Updated: 2015/07/25 03:34:49 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

int		get_index_handler(t_sess *sess, char *cmd)
{
	int i;

	i = 0;
	while (sess->handlers[i].cmd != NULL)
	{
		if (ft_strequ(cmd, sess->handlers[i].cmd))
			return (i);
		i++;
	}
	return (-1);
}

int 	session_start(char *dir_root, t_sess *sess)
{
	t_request	req;
	int			index;
	char		*input;

	memmove(req.dir_cur, dir_root, ft_strlen(dir_root));
	memmove(req.dir_root, dir_root, ft_strlen(dir_root));
	while (get_next_line(sess->client.sock, &input) != 0)
	{
		req.args = ft_strsplit(input, ' ');
		index = get_index_handler(sess, req.args[0]);
		if (index != -1)
			sess->handlers[index].f(&req, sess->client.sock);
		else
			printf("[%s] : Cmd not found.\n", input);
		ft_2dchardel(&req.args);
		free(input);
	}
	display_hour();
	printf("\nDeconnection from : %s\n", sess->client.ip);
}

extern char **environ;

int		main(int ac, char **av, char **env)
{
	t_sess	server;
	pid_t	child;

	if (ac != 2)
		usage(av[0]);
	init_all(&server, atoi(av[1]));
	while (77)
	{
		server.client.sock = accept(server.sock, \
			(struct sockaddr*)&server.client.csin, &server.client.cslen);
		child = secure_fork();
		if (child == 0)
		{
			server.client.ip = inet_ntoa(server.client.csin.sin_addr);
			display_hour();
			printf("\nConnection from : %s\n", server.client.ip);
			session_start(server.dir_root, &server);
		}
	}
	close(server.client.sock);
	close(server.sock);
	return (0);
}
