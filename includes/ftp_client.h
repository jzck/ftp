/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_client.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 15:50:56 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/12 14:39:39 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_CLIENT_H
# define FTP_CLIENT_H

# include "libft.h"
# include <stdio.h>
# include <termios.h>
# include <readline/readline.h>
# include <sys/mman.h>
# include <sys/wait.h>
# include <limits.h>
# include <signal.h>

# define FTP_CLIENT_USAGE	"%s <addr> <port>"
# define FTP_CMD(ftp, ...)	ftp_send((ftp)->cmd_sock, ##__VA_ARGS__)

typedef struct s_cmd_map	t_cmd_map;
typedef struct s_ftp		t_ftp;

struct						s_cmd_map
{
	char					*key;
	int						(*f)();
	char					*help;
};

enum						e_dstate
{
	DATA_NONE,
	DATA_PASV,
	DATA_ACTV,
};

union						u_conn
{
	struct sockaddr_in		sin;
	int						sock;
};

struct						s_ftp
{
	int						cmd_sock;
	enum e_dstate			data_state;
	union u_conn			dconn;
	int						d_sock;
};

extern t_cmd_map			g_cli_cmd[];
extern int					g_debug;

t_cmd_map					*get_cmd(char *cmd);

int							ftp_msg(t_ftp *ftp, char **msg);
int							ftp_code(t_ftp *ftp);

int							ftp_send(int sock, char *msg, ...);
int							ftp_recv(int sock, char **msg);
int							ftp_recvraw(int sock, char **msg);

int							dconn_init(t_ftp *ftp);
int							dconn_open(t_ftp *ftp);
int							dconn_close(t_ftp *ftp);
int							console_msg(int level, char *str, ...);

int							cli_debug(t_ftp *ftp, char **av);
int							cli_user(t_ftp *ftp, char **av);
int							cli_ls(t_ftp *ftp, char **av);
int							cli_pwd(t_ftp *ftp, char **av);
int							cli_sh(t_ftp *ftp, char **av);
int							cli_get(t_ftp *ftp, char **av);
int							cli_put(t_ftp *ftp, char **av);
int							cli_cd(t_ftp *ftp, char **av);
int							cli_help(t_ftp *ftp, char **av);
int							cli_debug(t_ftp *ftp, char **av);
int							cli_local(t_ftp *ftp, char **av);
int							cli_rmd(t_ftp *ftp, char **av);
int							cli_mkd(t_ftp *ftp, char **av);
int							cli_dele(t_ftp *ftp, char **av);

int							cli_pasv(t_ftp *ftp);

#endif
