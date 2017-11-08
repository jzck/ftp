/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_client.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 15:50:56 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/08 13:48:11 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_CLIENT
# define FTP_CLIENT

# include "libft.h"
# include <stdio.h>
# include <termios.h>
# include <readline/readline.h>
# include <sys/mman.h>
# include <sys/wait.h>
# include <limits.h>
# include "ftp.h"

# define FTP_CLIENT_USAGE	"%s <addr> <port>"

typedef struct s_cmd_map	t_cmd_map;

struct		s_cmd_map
{
	char	*key;
	int		(*f)();
	char	*help;
};

extern t_cmd_map	g_cli_cmd[];

t_cmd_map	*get_cmd(char *cmd);

int			cli_ls(int sock, char **av);
int			cli_sh(int sock, char **av);
int			cli_get(int sock, char **av);
int			cli_put(int sock, char **av);
int			cli_cd(int sock, char **av);

int			cli_help(int sock, char **av);
int			cli_debug(int sock, char **av);
int			cli_local(int sock, char **av);

#endif
