/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/24 01:21:52 by y0ja              #+#    #+#             */
/*   Updated: 2015/07/25 01:42:07 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int		cmd_list_files(t_request *req, int sock)
{
	send_cmd2server(sock, req->buf);
	read2socket(sock, 2);
	return (0);
}

int		cmd_change_dir(t_request *req, int sock)
{
	send_cmd2server(sock, req->buf);
	read2socket(sock, 2);
	printf("\n");
	return (0);
}

int		cmd_pwd(t_request *req, int sock)
{
	send_cmd2server(sock, req->buf);
	read2socket(sock, 2);
	printf("\n");
	return (0);
}

int		cmd_quit(t_request *req, int sock)
{
	close(sock);
	exit(0);
}
