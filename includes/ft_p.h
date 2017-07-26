/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 19:18:58 by jhalford          #+#    #+#             */
/*   Updated: 2017/04/03 18:42:28 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_H
# define FT_P_H

# define FTP_SERVER_USAGE	"%s <port>"
# define FTP_CLIENT_USAGE	"%s <addr> <port>"

# define MAXLINE		256

# include "libft.h"
# include <stdio.h>
# include <termios.h>
# include <readline/readline.h>

# include <sys/mman.h>
# include <sys/wait.h>
# include <limits.h>

typedef struct s_cmd_map	t_cmd_map;

struct	s_cmd_map
{
	char	*key;
	int		(*f)();
	char	*help;
};

enum	e_ftp
{
	REQUEST_FILE = 100,
	REQUEST_PUT,
	REQUEST_SH,
	REQUEST_CD,
	CMD_NOT_SUPPORTED = 150,
	CMD_SUPPORTED = 160,
	FILENAME_OK = 700,
	NO_SUCH_FILE,
	TRANSFER_START,
	CD_DIR_NOT_FOUND,
	CD_RESTRICTED_DIR,
	ABORT = 800,
	ERR_READ,
	ERR_STAT,
	ERR_MMAP,
	CMD_SUCCESS = 900,
	CMD_FAIL,
};

extern char			**g_av;
extern int			g_debug;
extern t_cmd_map	g_cli_cmd[];
extern char			g_rootdir[PATH_MAX];


int			ftp_daemon(int sock);
int			ftp_spawn(int sock);
int			ftp_cmd(int sock, int req);

int			serv_do_get(int sock);
int			serv_do_put(int sock);
int			serv_do_sh(int sock);
int			serv_do_cd(int sock);

int			read_req(int sock);
t_cmd_map	*get_cmd(char *cmd);
int			console_msg(int level, char *str, ...);

int			cli_do_sh(int sock, char **av);
int			cli_do_get(int sock, char **av);
int			cli_do_put(int sock, char **av);
int			cli_do_cd(int sock, char **av);

int			cli_do_help(int sock, char **av);
int			cli_do_debug(int sock, char **av);
int			cli_do_local(int sock, char **av);

int			req_init(int sock, int req);

#endif
