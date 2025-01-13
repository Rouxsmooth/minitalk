/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:18:46 by mzaian            #+#    #+#             */
/*   Updated: 2025/01/13 18:38:02 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

#include <stdio.h>
static t_server g_serv;

int	reception_ack(pid_t sender_pid, int sig)
{
	// printf("sent to %d\n", sender_pid);
	if (kill(sender_pid, sig) == -1)
		return (display_error("bit sending error"));
	return (0);
}

// void printmaskbin(unsigned int mask)
// {
// 	int i;

// 	i = 7;
// 	ft_printf("Binary mask: ");
// 	while (i >= 0)
// 	{
// 		ft_printf("%d", (mask >> i) & 1);
// 		i--;
// 	}
// 	ft_printf("\n");
// }

int	check_signature(pid_t sender_pid)
{
	int	i;
	int	nbr;

	i = g_serv.msglen - 3;
	nbr = 0;
	if (g_serv.mask = '*' && g_serv.msg[g_serv.msglen - 2] == '@')
	{
		while (ft_isdigit(g_serv.msg[i]))
			i--;
		if (g_serv.msg[i] == '@' && g_serv.msg[i - 1] == '*')
		{
			while (ft_isdigit(g_serv.msg[++i]))
				nbr = (nbr * 10) + (g_serv.msg[i] - 48);
			while (nbr > 9)
			{
				g_serv.amountlen++;
				nbr /= 10;
			}
			return (kill(sender_pid, SIGUSR2), 1);
		}
	}
	return (0);
}

void	handle_sigusr(int sig, siginfo_t *info, void *context)
{
	int 	bit;
	pid_t sender_pid;
	
	sender_pid = info->si_pid;
	bit = (sig == SIGUSR2);
	printf("%d\n", bit);
	// ft_printf("Received bit: %d\n", bit);
	reception_ack(sender_pid, sig);
	if (g_serv.current_bit < 8)
	{
		g_serv.mask |= (bit << (7 - g_serv.current_bit));
		g_serv.current_bit++;
	}
	if (g_serv.current_bit == 8)
	{
		// printmaskbin(g_serv.mask);
		if (g_serv.msglen == 0)
			g_serv.msg[0] = g_serv.mask;
		else
		{
			g_serv.msg = (char *) realloc(g_serv.msg, g_serv.msglen + 1);
			g_serv.msg[g_serv.msglen] = g_serv.mask;
			if (check_signature(sender_pid))
				g_serv.keep = 1;
		}
		g_serv.msglen++;
		// printf("mask: %c | full msg: \"%s\" | msglen: %d | actuallen: %d\n", g_serv.mask, g_serv.msg, (int) g_serv.msglen, (int) ft_strlen(g_serv.msg));
		g_serv.current_bit = 0;
		g_serv.mask = 0;
	}
	if (g_serv.keep)
		write(1, g_serv.msg, g_serv.msglen - 4 - g_serv.amountlen);
}

int init_server(void)
{
	struct sigaction sa;

	g_serv.current_bit = 0;
	g_serv.mask = 0;
	g_serv.msglen = 0;
	g_serv.keep = 0;
	g_serv.amountlen = 0;
	g_serv.msg = ft_calloc(1, sizeof(char));
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

int main(void)
{
	if (init_server() == -1)
		return (1);
	while (g_serv.keep)
		pause();
	return (0);
}
