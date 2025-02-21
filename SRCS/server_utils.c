/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:42:43 by mzaian            #+#    #+#             */
/*   Updated: 2025/02/21 16:14:16 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

void	init_g_serv(void)
{
	g_serv.current_bit = 0;
	g_serv.mask = 0;
	g_serv.msglen = 0;
	g_serv.maxbits = 41;
	g_serv.sigcount = 0;
	g_serv.has_signature = 0;
	g_serv.len = 0;
	ft_del(g_serv.msg);
	g_serv.msg = NULL;
}

void	get_signature(void)
{
	if (g_serv.mask == 'S' && g_serv.sigcount > 31)
	{
		g_serv.sigcount = 0;
		g_serv.has_signature = 1;
		g_serv.maxbits = g_serv.len * 8;
		g_serv.msg = (char *) ft_calloc(g_serv.len + 1, sizeof(char));
	}
	else if (g_serv.sigcount <= 32)
	{
		while (g_serv.current_bit--)
		{
			g_serv.len <<= 1;
			g_serv.len |= (g_serv.mask >> (32 - g_serv.sigcount + g_serv.current_bit) & 1);
		}
	}
}
