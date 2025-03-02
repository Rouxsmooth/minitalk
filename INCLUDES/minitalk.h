/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:06:57 by mzaian            #+#    #+#             */
/*   Updated: 2025/03/02 17:07:54 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <sys/types.h>
# include <signal.h>

//add libft to INCLUDES and change libft.h path
# include "../../libft/INCLUDES/libft.h"
# include "../../../../usr/include/x86_64-linux-gnu/bits/sigaction.h"

typedef struct s_server
{
	unsigned int	current_bit;
	unsigned char	mask;
	char			*msg;
	size_t			msglen;
	int				maxbits;
	int				has_signature;
	int				sigcount;
	unsigned int	len;
}	t_server;

typedef struct s_client
{
	unsigned int	current_bit;
	unsigned char	mask;
	unsigned int	ack;
	int				receive_sig;
	pid_t			pid;
	int				resend;
	int				retry;
}	t_client;

/* globals */
extern t_server	g_serv;
extern t_client	g_client;

/* client */
void	handle_ack(int sig);
void	pid_error(void);
void	sig_sending(int sig);
void	char_sending(char c);
void	msg_sending(char *msg);
void	signature_sending(char *msg);

/* server */
//int		reception_ack(pid_t pid, int sig);
void	init_g_serv(void);
void	get_signature(void);
int		bit_couting(int sig);
void	set_char(void);

#endif