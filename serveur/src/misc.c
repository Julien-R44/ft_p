/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/22 19:47:56 by y0ja              #+#    #+#             */
/*   Updated: 2015/07/24 17:43:46 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void		display_hour(void)
{
	time_t		epoch_time;
	char		*str;
	int			i;

	i = 0;
	ft_putchar('\n');
	epoch_time = time(NULL);
	str = asctime(localtime(&epoch_time));
	while (i < 16)
	{
		ft_putchar(str[i]);
		i++;
	}
}

pid_t	secure_fork(void)
{
	pid_t child;

	if ((child = fork()) == -1)
		ft_error(FORK);
	return (child);
}

void	usage(char *bin)
{
	printf("Usage : %s <port>\n", bin);
	exit(0);
}

void	ft_error(int er)
{
	if (er == FORK)
		printf("Fork(2) error\n");
	if (er == BIND)
		printf("Bind(2) error\n");
	if (er == EXECVE)
		printf("Execve(2) error\n");
	if (er == SOCKET)
		printf("Socket(2) error\n");
	if (er == FORK)
		printf("Fork(2) error\n");
	if (er == DUP)
		printf("Dup(2) error\n");
	exit(-1);
}
