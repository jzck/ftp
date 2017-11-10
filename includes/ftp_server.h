/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_server.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 15:56:59 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/10 19:39:47 by jhalford         ###   ########.fr       */
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

# define REPOPATH "data/"

# define FTP_SERVER_USAGE	"%s <port>"
# define ftp_ret(ftp, ...)	ftp_send((ftp)->cmd_sock, ##__VA_ARGS__)

typedef struct s_ftp		t_ftp;
typedef struct s_ftp_cmd	t_ftp_cmd;

enum					e_dstate
{
	DATA_NONE,
	DATA_PASV,
	DATA_ACTV,
};

enum					e_lstate
{
	LOG_NONE,
	LOG_YES,
};

struct					s_ftp
{
	int					cmd_sock;
	enum e_lstate		log_state;
	char				username[100];
	char				path[100];
	enum e_dstate		data_state;
	union {
		struct sockaddr_in	sin;
		int					sock;
	}					dconn;
	int					d_sock;
};

struct					s_ftp_cmd
{
	char				*name;
	int					(*f)();
	enum e_lstate		statelock;
};


extern char			**g_av;
extern int			g_debug;
extern char			g_rootdir[PATH_MAX];

int			ftp_send(int sock, char *msg, ...);
int			ftp_recv(int sock, char **msg);
int			ftp_recvraw(int sock, char **msg);
int			dconn_open(t_ftp *ftp);
int			dconn_close(t_ftp *ftp);
int			console_msg(int level, char *str, ...);

int			cmd_user(t_ftp *ftp, char **av);
int			cmd_quit(t_ftp *ftp, char **av);
int			cmd_retr(t_ftp *ftp, char **av);
int			cmd_stor(t_ftp *ftp, char **av);
int			cmd_cwd(t_ftp *ftp, char **av);
int			cmd_pwd(t_ftp *ftp, char **av);
int			cmd_pasv(t_ftp *ftp, char **av);
int			cmd_port(t_ftp *ftp, char **av);
int			cmd_type(t_ftp *ftp, char **av);
int			cmd_list(t_ftp *ftp, char **av);
int			cmd_mkd(t_ftp *ftp, char **av);
int			cmd_mkd(t_ftp *ftp, char **av);
int			cmd_mkd(t_ftp *ftp, char **av);
int			cmd_rmd(t_ftp *ftp, char **av);
int			cmd_dele(t_ftp *ftp, char **av);

#endif
