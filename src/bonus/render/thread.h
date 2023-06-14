/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 22:26:17 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/06/14 14:11:11 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include <pthread.h>

typedef struct s_context	t_context;
typedef struct s_region		t_region;
typedef pthread_mutex_t		t_mutex;

typedef struct s_rstate
{
	size_t	index;
	size_t	samples;
	size_t	depth;
	size_t	regionsize;
	t_mutex	indexmutex;
}	t_rstate;

t_rstate	*getstate(void);
void		*renderthread(void *arg);
void		transferimg(t_context *ctx, const t_region *region);

#endif
