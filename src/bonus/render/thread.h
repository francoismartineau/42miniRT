/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 22:26:17 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/06/19 10:04:23 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include <pthread.h>

# define THREADS 12

typedef struct s_context	t_context;
typedef struct s_region		t_region;
typedef pthread_mutex_t		t_mutex;

typedef struct s_rstate
{
	size_t	x;
	size_t	y;
	size_t	threadindex;
	size_t	samples;
	size_t	depth;
	size_t	regsize;
	t_mutex	indexmutex;
}	t_rstate;

t_rstate	*getstate(void);
void		*renderthread(void *arg);
void		transferimg(t_context *ctx, const t_region *region);

#endif
