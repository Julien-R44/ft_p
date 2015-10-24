/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/25 01:35:41 by jripoute          #+#    #+#             */
/*   Updated: 2015/07/25 01:11:38 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int		get_index_handler(t_cmd_handler *handlers, char *cmd)
{
	int i;

	i = 0;
	while (handlers[i].cmd != NULL)
	{
		if (ft_strequ(cmd, handlers[i].cmd))
			return (i);
		i++;
	}
	return (-1);
}

void	display_prompt(void)
{
	ft_putstr("\n$> ");
}

void	main_loop(int sock, t_cmd_handler *handlers)
{
	t_request	req;
	int			index;
	int			r;

	while (get_next_line(2, &req.buf) != 0)
	{
		req.args = ft_strsplit(req.buf, ' ');
		index = get_index_handler(handlers, req.args[0]);
		if (index != -1)
			r = handlers[index].f(&req, sock);
		else
			printf("[%s] : Command not found\n", req.args[0]);
		ft_2dchardel(&req.args);
		free(req.buf);
		display_prompt();
	}
}

int		main(int ac, char **av)
{
	t_all			all;

	if (ac != 3)
		return (usage(CLIENT));
	init_all(&all, av[1], atoi(av[2]));
	printf("Connected to %s:%s\n", av[1], av[2]);
	display_prompt();
	main_loop(all.sock, all.handlers);
	printf("Bye bye...\n");
	close(all.sock);
	return (0);
}
