/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:18:46 by mzaian            #+#    #+#             */
/*   Updated: 2025/01/18 22:03:53 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

#include <stdio.h>
static t_server g_serv;

int	reception_ack(pid_t pid, int sig)
{
	if (kill(pid, sig) == -1)
		return (display_error("bit sending error"));
	return (0);
}

void	init_g_serv(void)
{
	g_serv.current_bit = 0;
	g_serv.mask = 0;
	g_serv.msglen = 0;
	g_serv.keep = 0;
	g_serv.amountlen = 0;
	g_serv.sigcount = 0;
	g_serv.sentback = 0;
	g_serv.waiting_sig_confirm = 0;
	ft_del(&g_serv.msg);
	g_serv.msg = ft_calloc(1, sizeof(char));
}

int	found_signature()
{
	int	i;

	g_serv.waiting_sig_confirm = 0;
	usleep(1);
	while (!g_serv.waiting_sig_confirm)
	{
		if (i > 500)
			return (-1);
		usleep(1);
		i++;
	}
	return (1);
}

int	check_signature(pid_t sender_pid)
{
	int	i;
	int	nbr;
	int	temp;

	i = g_serv.msglen - 3;
	nbr = 0;
	//printf("g_serv.mask %c, g_serv.msg[g_serv.msglen - 2] %c\n", g_serv.mask, g_serv.msg[g_serv.msglen - 2]);
	if ((g_serv.mask = '*') && (g_serv.msg[g_serv.msglen - 2] == '@'))
	{
		while (ft_isdigit(g_serv.msg[i]))
			i--;
		i++;
		//printf("at i %c, at i -1 %c\n", g_serv.msg[i], g_serv.msg[i - 1]);
		if ((g_serv.msg[i] == '@') && (g_serv.msg[i - 1] == '*'))
		{
			while (ft_isdigit(g_serv.msg[++i]))
				nbr = (nbr * 10) + (g_serv.msg[i] - 48);
			temp = nbr;
			while (temp > 9)
			{
				g_serv.amountlen++;
				temp /= 10;
			}
			return (found_signature());
		}
	}
	return (0);
}

void	handle_sigusr(int sig, siginfo_t *info, void *context)
{
	int 	bit;
	pid_t sender_pid;
	
	(void) context;
	sender_pid = info->si_pid;
	bit = (sig == SIGUSR2);
	g_serv.sigcount++;
	reception_ack(sender_pid, sig);
	//printf("%d %d\n", g_serv.sigcount, g_serv.sentback);
	//printf("%d\n", bit);
	if (g_serv.current_bit < 8)
	{
		g_serv.mask |= (bit << (7 - g_serv.current_bit));
		g_serv.current_bit++;
	}
	if (g_serv.current_bit == 8)
	{
		//printmaskbin(g_serv.mask);
		if (g_serv.msglen == 0)
			g_serv.msg[0] = g_serv.mask;
		else
		{
			printf("len : %d\n", g_serv.msglen + 1);
			g_serv.msg = (char *) realloc(g_serv.msg, g_serv.msglen + 1);
			g_serv.msg[g_serv.msglen] = g_serv.mask;
			g_serv.good_signature = check_signature(sender_pid);
			if (g_serv.good_signature == -1)
				init_g_serv();
			else if (g_serv.good_signature == 1)
				g_serv.keep = 1;
		}
		//printf("\n");
		//printf("mask: %c | full msg: \"%s\" | msglen: %d | actuallen: %d\n", g_serv.mask, g_serv.msg, (int) g_serv.msglen, (int) ft_strlen(g_serv.msg));
		g_serv.msglen++;
		g_serv.current_bit = 0;
		g_serv.mask = 0;
	}
	if (g_serv.keep)
	{
		write(1, g_serv.msg, g_serv.msglen - 4 - g_serv.amountlen);
		write(1, "\n", 1);
		init_g_serv();
		//printf("mask %d, current bit %d, msg '%s'\n", g_serv.mask, g_serv.current_bit, g_serv.msg);
	}
}

int init_server(void)
{
	struct sigaction sa;

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

int main(void)
{
	if (init_server() == -1)
		return (1);
	while (1)
		pause();
	return (0);
}
