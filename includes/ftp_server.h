/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_server.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 15:56:59 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/02 16:33:37 by jhalford         ###   ########.fr       */
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

# define REPOPATH "data/"

# define FTP_SERVER_USAGE	"%s <port>"
# define ftp_ret(ftp, ...)	ftp_send((ftp)->cmd_sock, ##__VA_ARGS__)

typedef struct s_ftp		t_ftp;
typedef struct s_ftp_cmd	t_ftp_cmd;

struct		s_ftp
{
	int					cmd_sock;
	struct sockaddr_in	data_sin;
	char				username[100];
	char				path[100];
	int					state;
};

enum		e_state
{
	IDLE,
	LOGGED_IN,
};

struct		s_ftp_cmd
{
	char	*name;
	int		(*f)();
	int		statelock;
};


extern char			**g_av;
extern int			g_debug;
extern char			g_rootdir[PATH_MAX];

int			ftp_send(int sock, char *msg, ...);
int			ftp_recv(int sock, char **msg);
int			ftp_dataconn(t_ftp *ftp);
int			console_msg(int level, char *str, ...);

int			ftp_login(t_ftp *ftp);
int			cmd_user(t_ftp *ftp, char **av);
int			cmd_quit(t_ftp *ftp, char **av);
int			cmd_retr(t_ftp *ftp, char **av);
int			cmd_stor(t_ftp *ftp, char **av);
int			cmd_cwd(t_ftp *ftp, char **av);
int			cmd_pwd(t_ftp *ftp, char **av);
int			cmd_port(t_ftp *ftp, char **av);
int			cmd_type(t_ftp *ftp, char **av);
int			cmd_list(t_ftp *ftp, char **av);

#endif
