#include "ft_p.h"

int		cli_do_sh(int sock, char **av)
{
	char	*command;
	char	buf[MAXLINE];
	int		ret;

	command = ft_strsepjoin(av, ' ');

	if (req_init(sock, REQUEST_SH))
		return (1);

	console_msg(1, "sending '%s' to server", command);
	write(sock, command, ft_strlen(command));

	while ((ret = read(sock, &buf, MAXLINE)))
	{
		buf[ret] = 0;
		ft_printf("%s", buf);
		if (ret < MAXLINE)
			break ;
	}
	ft_strdel(&command);
	return (0);
}
