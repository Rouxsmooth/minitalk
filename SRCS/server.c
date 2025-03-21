/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:18:46 by mzaian            #+#    #+#             */
/*   Updated: 2025/03/14 16:57:47 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

int	reception_ack(pid_t pid, int sig)
{
	if (kill(pid, sig) == -1)
		return (display_error("bit sending error"));
	return (0);
}

void	handle_sigusr(int sig, siginfo_t *info, void *context)
{
	int		bit;
	pid_t	sender_pid;

	(void) context;
	sender_pid = info->si_pid;
	bit = bit_couting(sig);
	if (g_serv.sigcount > g_serv.maxbits)
		return (init_g_serv());
	if (g_serv.current_bit < 8)
	{
		g_serv.mask |= (bit << (7 - g_serv.current_bit));
		g_serv.current_bit++;
	}
	if (g_serv.current_bit == 8)
	{
		set_char();
		if (!g_serv.len && !g_serv.has_signature)
			return ;
	}
	reception_ack(sender_pid, sig);
	if (g_serv.sigcount == g_serv.maxbits)
		return (ft_printf("%s", g_serv.msg), init_g_serv());
	return ;
}
	//printf("len %d, has_sig %d\n", g_serv.len, g_serv.has_signature);

int	init_server(void)
{
	struct sigaction	sa;

	init_g_serv();
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_sigusr;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (display_error("failed to set up signal handlers.\n"), -1);
	return (ft_printf("\e[31;1m\n\
  +-----------------------------------------------+\n\
  | __  __ ___ _   _ ___ ____  _____ ______     __|\n\
  ||  \\/  |_ _| \\ | |_ _/ ___|| ____|  _ \\ \\   / /|\n\
  || |\\/| || ||  \\| || |\\___ \\|  _| | |_) \\ \\ / / |\n\
  || |  | || || |\\  || | ___) | |___|  _ < \\ V /  |\n\
  ||_|  |_|___|_| \\_|___|____/|_____|_| \\_\\ \\_/   |\n\
  |                                               |\n\
  |             SO WE CAN COMMUNICATE             |\n\
  +-----------------------------------------------+\n\n\
	\e[32;1mServer's PID : %d\e[0m\n", getpid()));
}

int	main(void)
{
	if (init_server() == -1)
		return (1);
	while (1)
		pause();
	return (0);
}
