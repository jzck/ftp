/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_server.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 15:56:59 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/01 19:23:02 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_SERVER
# define FTP_SERVER

# include "libft.h"
# include <stdio.h>
# include <sys/mman.h>
# include <limits.h>
# include <pwd.h>

# include <arpa/inet.h>

# include "ftp.h"

# define FTP_SERVER_USAGE	"%s <port>"

typedef struct s_ftp		t_ftp;
typedef struct s_ftp_cmd	t_ftp_cmd;

struct		s_ftp
{
	struct sockaddr_in	data_sin;
	int					data_sock;
	int					cmd_sock;
};

struct		s_ftp_cmd
{
	char	*name;
	int		(*f)();
};


extern char			**g_av;
extern int			g_debug;
extern char			g_rootdir[PATH_MAX];

int			ftp_send(t_ftp *ftp, char *msg, ...);
int			ftp_recv(t_ftp *ftp, char **msg);
int			console_msg(int level, char *str, ...);

int			ftp_login(t_ftp *ftp);
int			cmd_pwd(t_ftp *ftp, char **av);
int			cmd_port(t_ftp *ftp, char **av);
int			cmd_type(t_ftp *ftp, char **av);
int			cmd_list(t_ftp *ftp, char **av);

#endif
