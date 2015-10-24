/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/23 02:26:10 by y0ja              #+#    #+#             */
/*   Updated: 2015/07/26 01:04:55 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static int		create_client(char *addr, int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	struct hostent		*hostinfo = NULL;

	hostinfo = gethostbyname(addr);
	if (hostinfo == NULL)
		ft_error(HOSTBYNAME);
	if (!(proto = getprotobyname("tcp")))
		return (-1);
	if ((sock = socket(AF_INET, SOCK_STREAM, proto->p_proto)) == -1)
		ft_error(SOCKET);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr = *(struct in_addr *) hostinfo->h_addr;
	if (connect(sock, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
		ft_error(CONNECT);
	return (sock);
}

static void	init_cmd_handlers(t_all *all)
{
	t_cmd_handler static_handlers[] = {
		{"cd", &cmd_change_dir},
		{"lcd", &cmd_local_cd},
		{"pwd", &cmd_pwd},
		{"ls", &cmd_list_files},
		{"lls", &cmd_local_list_files},
		{"get", &cmd_get_file},
		{"put", &cmd_put_file},
		{"quit", &cmd_quit},
		{NULL, NULL},
	};

	all->handlers = (t_cmd_handler *)malloc(sizeof(t_cmd_handler) * 9);
	if (all->handlers == NULL)
		ft_error(MALLOC);
	memmove(all->handlers, static_handlers, sizeof(static_handlers));
}

void		sig_handler(int sig)
{
	display_prompt();
}

static void	init_signal(void)
{
	signal(SIGINT, sig_handler);
}

int			init_all(t_all *all, char *addr, int port)
{
	all->sock = create_client(addr, port);
	init_cmd_handlers(all);
	init_signal();
}

