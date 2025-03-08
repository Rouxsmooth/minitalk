/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:26:19 by mzaian            #+#    #+#             */
/*   Updated: 2025/03/08 02:49:52 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

void	draw_client(void)
{
	ft_printf("\e[31;1m\n\
  +-------------------------------------------------------+\n\
  | __  __ ___ _   _ ___ ____ _     ___ _____ _   _ _____ |\n\
  ||  \\/  |_ _| \\ | |_ _/ ___| |   |_ _| ____| \\ | |_   _||\n\
  || |\\/| || ||  \\| || | |   | |    | ||  _| |  \\| | | |  |\n\
  || |  | || || |\\  || | |___| |___ | || |___| |\\  | | |  |\n\
  ||_|  |_|___|_| \\_|___\\____|_____|___|_____|_| \\_| |_|  |\n\
  |                                                       |\n\
  |                  SO WE CAN COMMUNICATE                |\n\
  +-------------------------------------------------------+\n\e[0m");
	return ;
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	t_clientflags		flag;

	sa.sa_handler = handle_ack;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (display_error("failed to set up signal handlers"));
	init_g_client();
	flag = has_flags(argc, argv);
	if (!right_argcount(flag, argc))
		return (0);
	g_client.pid = ft_atoi(argv[1 + flag.count]);
	if (g_client.pid < 1)
		return (display_error("Invalid server PID."));
	send(flag, argv);
	return (0);
}
