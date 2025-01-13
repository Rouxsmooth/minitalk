/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:18:46 by mzaian            #+#    #+#             */
/*   Updated: 2025/01/13 11:07:01 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

#include <stdio.h>
static t_server g_serv;
/*
void printmaskbin(unsigned int mask)
{
	int i;

	i = 7;
	ft_printf("Binary mask: ");
	while (i >= 0)
	{
		ft_printf("%d", (mask >> i) & 1);
		i--;
	}
	ft_printf("\n");
}
*/
void handle_sigusr(int sig)
{
	int 	bit;
	bit = (sig == SIGUSR2);
	//ft_printf("Received bit: %d\n", bit);
	if (g_serv.current_bit < 8)
	{
		g_serv.mask |= (bit << (7 - g_serv.current_bit));
		g_serv.current_bit++;
	}
	if (g_serv.current_bit == 8)
	{
		if (g_serv.msglen == 0)
			g_serv.msg[0] = g_serv.mask;
		else
		{
			g_serv.msg = (char *) ft_realloc(g_serv.msg, g_serv.msglen + 1);
			g_serv.msg[g_serv.msglen] = g_serv.mask;
		}
		printf("mask: %c | full msg: \"%s\" | msglen: %d | supposedlen: %d\n", g_serv.mask, g_serv.msg, (int) g_serv.msglen, (int) ft_strlen(g_serv.msg));
		g_serv.msglen++;
		g_serv.current_bit = 0;
		g_serv.mask = 0;
	}
	//printmaskbin(g_serv.mask);
}

int	reception_ack(siginfo_t *info, int sig)
{
	pid_t	sendingpid;
	int		i;

	sendingpid = info->si_pid;
	if (kill(sendingpid, sig) == -1)
		return (display_error("message sending error"));
	
}

int init_server(void)
{
	struct sigaction sa;

	g_serv.current_bit = 0;
	g_serv.mask = 0;
	g_serv.msglen = 0;
	g_serv.msg = ft_calloc(1, sizeof(char));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handle_sigusr;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (ft_printf("Failed to set up signal handlers.\n"), -1);
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
		return (display_error("Error: signal assignation error."), 1);
	while (1)
		pause();
	return (0);
}
