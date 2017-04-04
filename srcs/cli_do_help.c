#include "ft_p.h"

int		cli_do_help(int sock, char **av)
{
	int			i;
	t_cmd_map	*cmd;

	(void)sock;
	(void)av;
	i = 0;
	while (av[++i])
	{
		if (!(cmd = get_cmd(av[i])))
			console_msg(-1, "?Invalid ? command `%s'", av[i]);
		else
			console_msg(0, "%s\t%s", cmd->key, cmd->help);
	}
	if (i == 1)
	{
		console_msg(0, "Commands are:");
		i = -1;
		while (g_cli_cmd[++i].key)
			console_msg(0, "%s\n", g_cli_cmd[i].key);
	}
	return (0);
}
