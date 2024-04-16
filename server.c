/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:43:04 by ubazzane          #+#    #+#             */
/*   Updated: 2024/01/04 17:34:41 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	receive_bit(int signal);

int	main(void)
{
	struct sigaction	sig_act;

	ft_printf("Please copy this PID: %d\n", getpid());
	while (1)
	{
		sig_act.sa_handler = &receive_bit;
		sigaction(SIGUSR1, &sig_act, NULL);
		sigaction(SIGUSR2, &sig_act, NULL);
	}
	return (0);
}

/* For reference SIGUSR2 represents 0 and SIGUSR1 represents 1 */
static void	receive_bit(int signal)
{
	static int				i = 0;
	static unsigned char	c = 0;

	if (signal == SIGUSR2)
		c = c << 1;
	else if (signal == SIGUSR1)
		c = (c << 1) | 0b00000001;
	i++;
	if (i == 8)
	{
		ft_printf("%c", c);
		i = 0;
		c = 0;
	}
}
