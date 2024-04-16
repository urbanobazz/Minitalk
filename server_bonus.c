/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:43:04 by ubazzane          #+#    #+#             */
/*   Updated: 2024/01/20 17:19:07 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	receive_bit(int sig, siginfo_t *info, void *content);

int	main(void)
{
	struct sigaction	sig_act;

	ft_printf("Please copy this PID: %d\n", getpid());
	sig_act.sa_sigaction = &receive_bit;
	sig_act.sa_flags = SA_SIGINFO;
	while (1)
	{
		sigaction(SIGUSR1, &sig_act, NULL);
		sigaction(SIGUSR2, &sig_act, NULL);
		pause();
	}
	return (0);
}

/* For reference SIGUSR2 represents 0 and SIGUSR1 represents 1 */
static void	receive_bit(int sig, siginfo_t *info, void *content)
{
	static int				bit = 0;
	static unsigned char	c = 0;

	(void)content;
	if (sig == SIGUSR2)
		c = c << 1;
	else if (sig == SIGUSR1)
		c = (c << 1) | 0b00000001;
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", c);
		bit = 0;
		c = 0;
		if (kill(info->si_pid, SIGUSR1) == -1)
			ft_putstr_fd("Unable to send confirmation\n", 2);
		return ;
	}
}
