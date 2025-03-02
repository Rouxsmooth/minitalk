/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:18:46 by mzaian            #+#    #+#             */
/*   Updated: 2025/03/02 17:10:02 by mzaian           ###   ########.fr       */
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
	//printf("len %d, has_sig %d\n", g_serv.len, g_serv.has_signature);
	if (g_serv.sigcount == g_serv.maxbits)
		return (ft_printf("'%s'\n", g_serv.msg), init_g_serv());
}
// si le nombre de bits recu total est inferieur et on a (?) arrete de recevoir des signaux, on reset

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
   +---------------------------------------------+\n\
   | __  __ ___ _   _ ___ _____  _    _     _  __|\n\
   ||  \\/  |_ _| \\ | |_ _|_   _|/ \\  | |   | |/ /|\n\
   || |\\/| || ||  \\| || |  | | / _ \\ | |   | ' / |\n\
   || |  | || || |\\  || |  | |/ ___ \\| |___| . \\ |\n\
   ||_|  |_|___|_| \\_|___| |_/_/   \\_\\_____|_|\\_\\|\n\
   |                                             |\n\
   |            SO WE CAN COMMUNICATE            |\n\
   +---------------------------------------------+\n\n\
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
