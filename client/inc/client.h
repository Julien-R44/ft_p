/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/27 02:11:44 by jripoute          #+#    #+#             */
/*   Updated: 2015/07/26 01:02:06 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>

# include "libft.h"

# define ERROR 0

typedef enum		s_error
{
	FORK,
	SOCKET,
	MALLOC,
	CONNECT,
	HOSTBYNAME,
}					t_error;

typedef enum		s_usage
{
	CLIENT,
	GET,
	PUT,
}					t_usage;

typedef struct		s_request
{
	char			*buf;
	char			**args;
}					t_request;

typedef struct		s_cmd_handler
{
	char			*cmd;
	int				(*f)(t_request *req, int sock);
}					t_cmd_handler;

typedef struct		s_all
{
	int				sock;
	t_cmd_handler	*handlers;
}					t_all;

// init.c
int					init_all(t_all *all, char *addr, int port);

// receipter.c
char				**read_header(int sock);
void				read2socket(int sock, int fd_out);

// cmd.c
int					cmd_get_file(t_request *req, int sock);
int					cmd_put_file(t_request *req, int sock);

// cmd2.c
int					cmd_list_files(t_request *req, int sock);
int					cmd_change_dir(t_request *req, int sock);
int					cmd_pwd(t_request *req, int sock);
int					cmd_quit(t_request *req, int sock);

// cmd_local.c
int					cmd_local_list_files(t_request *req, int sock);
int					cmd_local_cd(t_request *req, int sock);

// misc.c
pid_t				secure_fork(void);
void				ft_error(int er);
int					usage(int cmd);
char				*get_field_value_header(char *str);
int					ft_protocol_error(int sock, int er);

#endif
