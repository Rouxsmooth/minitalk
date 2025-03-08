/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientflags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 02:48:45 by mzaian            #+#    #+#             */
/*   Updated: 2025/03/08 02:52:42 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

void	help(void)
{
	ft_printf("USAGE : [OPTION].. [PID] [MESSAGE]\nOPTIONS:\n");
	ft_printf("\t-h, --help\t\t: Shows this help message.\n");
	ft_printf("\t-i, --interactive\t: Keeps the client open for \
multiple messages. In interactive mode, type a message and press \
Enter to send. Type `exit` to close the client or hit CTRL+D.\n\n");
	ft_printf("\t-n, --newline\t\t: Changes whether the messages sent \
are printed with a newline after each message. If enabled, each message \
will be printed on a new line. Otherwise, messages will be printed \
consecutively without line breaks.\n");
}

int	right_argcount(t_clientflags flag, int argc)
{
	if (!flag.count)
	{
		if (argc == 3)
			return (1);
		return (display_error("Try ./client [OPTION].. [PID] [MESSAGE]"), 0);
	}
	if (flag.i)
	{
		if (flag.n && argc != 4)
			return (display_error("Try ./client -i -n [PID]"), 0);
		else if (!flag.n && argc != 3)
			return (display_error("Try ./client -i [PID]"), 0);
		return (1);
	}
	if (flag.n && argc != 4)
		return (display_error("Try ./client -n [PID] [MESSAGE]"), 0);
	return (1);
}

t_clientflags	has_flags(int argc, char **argv)
{
	static t_clientflags	flag = {0, 0, 0};

	if (argc < 2)
		return (display_error("Try ./client [OPTION].. [PID] [MESSAGE]"), flag);
	if (*argv[1] == '-')
	{
		if (!ft_strcmp(argv[1], "-h") || !ft_strcmp(argv[1], "--help"))
			return (help(), flag);
		if (argc < 3)
			return (display_error("Too few arguments."), flag);
		if (!ft_strcmp(argv[1], "-i") || !ft_strcmp(argv[1], "--interactive"))
		{
			flag.i = 1;
			flag.count++;
		}
		if (!ft_strcmp(argv[1 + flag.count], "-n")
			|| !ft_strcmp(argv[1 + flag.count], "--newline"))
		{
			flag.n = 1;
			flag.count++;
		}
		if (!flag.count)
			return (display_error("Flag not recognized. Try --help"), flag);
	}
	return (flag);
}
