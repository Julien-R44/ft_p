/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_local.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/24 17:23:52 by y0ja              #+#    #+#             */
/*   Updated: 2015/07/25 02:41:56 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int		cmd_local_list_files(t_request *req, int sock)
{
	pid_t		child;

	child = secure_fork();
	if (child == 0)
		execve("/bin/ls", req->args, NULL);
	else
		waitpid(child, NULL, 0);
	return (1);
}

int		cmd_local_cd(t_request *req, int sock)
{
	if (chdir(req->args[1]) == -1)
		printf("ERROR\n");
	return (0);
}
