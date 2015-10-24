/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/26 05:53:00 by jripoute          #+#    #+#             */
/*   Updated: 2015/07/25 03:34:56 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <sys/types.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/resource.h>
# include <sys/socket.h>
# include <sys/wait.h>
# include <time.h>
# include <limits.h>

# include "libft.h"

# define MAX_QUEUE 42

/* Protocol :
	Each data exchange is null terminated to indicate the end of transmission.

	Header is sent for each file request. Informations are separated by ';'
	like HEADER_SIZE=40;ERROR=100;FILE_SIZE=4096;
	Available informations are :
			- ERROR,
	You can know its the end of the header by using the header_size

	Error availaibles:
		550 : No such file or permission denied.
		420 : Is A Directory
*/

typedef enum			s_error
{
	SOCKET,
	MALLOC,
	BIND,
	FORK,
	EXECVE,
	DUP,
	LISTEN,
	NO_FILE,
}						t_error;

typedef struct			s_request
{
	char				dir_cur[PATH_MAX];
	char				*dir_root;
	char				**args;
}						t_request;

typedef struct			s_cmd_handler
{
	char				*cmd;
	int					(*f)(t_request *req, int sock);
}						t_cmd_handler;

typedef struct			s_client
{
	char				*ip;
	struct sockaddr_in	csin;
	unsigned int		cslen;
	int					sock;
}						t_client;

typedef struct			s_sess
{
	int					sock;
	char				*dir_root;
	t_client			client;
	t_cmd_handler		*handlers;
}						t_sess;

// init.c
void					init_all(t_sess *sess, int port);

// sender.c
void					send_header(int sock, char *error);
void					send_file(int cs, int fd);
int						file_is_valid(int fd);

// cmd.c
int						cmd_put_file(t_request *req, int sock);
int						cmd_get_file(t_request *req, int sock);
int						cmd_pwd(t_request *req, int sock);
int						cmd_list_files(t_request *req, int sock);
int						cmd_change_dir(t_request *req, int sock);

// misc.c
void					usage(char *bin);
void					ft_error(int er);
pid_t					secure_fork(void);
void					display_hour(void);

#endif
