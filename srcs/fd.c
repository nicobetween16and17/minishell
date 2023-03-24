/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:12:12 by niespana          #+#    #+#             */
/*   Updated: 2023/01/19 21:12:13 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishl.h"

/*
 * close fd if positive
 */
void	ft_close(int fd)
{
	if (fd >= 0)
		close(fd);
}

/*
 * replace the standard inputs with the copy of the original ones to
 * reset to status qo
 */
void	reset_std(t_shell *sh)
{
	dup2(sh->in, 0);
	dup2(sh->out, 1);
}

/*
 * close the file descriptors
 */
void	close_fds(t_shell *sh)
{
	ft_close(sh->infile);
	ft_close(sh->outfile);
}

/*
 * reset the file descriptors
 */
void	reset_fds(t_shell *sh)
{
	sh->infile = 0;
	sh->outfile = 1;
}
