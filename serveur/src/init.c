/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/22 22:27:54 by y0ja              #+#    #+#             */
/*   Updated: 2015/07/25 21:19:41 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

static void	init_cmd_handlers(t_sess *sess)
{
	t_cmd_handler handlers[] = {
		{"ls", &cmd_list_files},
		{"cd", &cmd_change_dir},
		{"pwd", &cmd_pwd},
		{"get", &cmd_get_file},
		{"put", &cmd_put_file},
		{NULL, NULL},
	};

	sess->handlers = (t_cmd_handler *)malloc(sizeof(t_cmd_handler) * 6);
	if (sess->handlers == NULL)
		ft_error(MALLOC);
	memmove(sess->handlers, handlers, sizeof(handlers));
}

static int	create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (!(proto = getprotobyname("TCP")))
		return (-1);
	if ((sock = socket(AF_INET, SOCK_STREAM, proto->p_proto)) == -1)
		ft_error(SOCKET);
	if (bind(sock, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
		ft_error(BIND);
	return (sock);
}

static void	init_fs_permissions(t_sess *sess)
{
	char buf[4096] = {0};

	sess->dir_root = getcwd(buf, sizeof(buf));
	printf("Root directory = %s\n", sess->dir_root);
}

void		init_all(t_sess *sess, int port)
{
	init_cmd_handlers(sess);
	init_fs_permissions(sess);
	sess->sock = create_server(port);
	if (listen(sess->sock, MAX_QUEUE) == -1)
		ft_error(LISTEN);
	printf("Server is listening on port %d.\n", port);
}
