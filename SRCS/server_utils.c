/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:42:43 by mzaian            #+#    #+#             */
/*   Updated: 2025/03/02 17:05:53 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

void	init_g_serv(void)
{
	g_serv.current_bit = 0;
	g_serv.mask = 0;
	g_serv.msglen = 0;
	g_serv.maxbits = 89;
	g_serv.sigcount = 0;
	g_serv.has_signature = 0;
	g_serv.len = 0;
	ft_del(g_serv.msg);
	g_serv.msg = NULL;
}

void	get_signature(void)
{
	ft_printf("mask %c\n", g_serv.mask);
	if (g_serv.mask == 'S')
	{
		if (!g_serv.len)
			return (start_colored_output(1, colorcode_by_str("magenta")),
				ft_putstr_fd("message length not received", 1),
				close_colored_output(1), (void) NULL);
		g_serv.sigcount = 0;
		g_serv.has_signature = 1;
		g_serv.maxbits = g_serv.len * 8;
		g_serv.msg = (char *) ft_calloc(g_serv.len + 1, sizeof(char));
	}
	else
	{
		g_serv.len *= 10;
		g_serv.len += g_serv.mask - 48;
	}
}

int	bit_couting(int sig)
{
	g_serv.sigcount++;
	return (sig == SIGUSR2);
}

void	set_char(void)
{
	if (!g_serv.has_signature)
		get_signature();
	else
		g_serv.msg[g_serv.msglen++] = g_serv.mask;
	g_serv.current_bit = 0;
	g_serv.mask = 0;
}
