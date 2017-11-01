/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_client.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 15:50:56 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/01 17:12:03 by jhalford         ###   ########.fr       */
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

int			cli_do_sh(int sock, char **av);
int			cli_do_get(int sock, char **av);
int			cli_do_put(int sock, char **av);
int			cli_do_cd(int sock, char **av);

int			cli_do_help(int sock, char **av);
int			cli_do_debug(int sock, char **av);
int			cli_do_local(int sock, char **av);

#endif
