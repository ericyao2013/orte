/*
 *  $Id: compat.h,v 0.0.0.1             2004/11/14
 *
 *  AUTHOR: Jan Kiszka                  jan.kiszka@web.de
 *
 *  ORTE - OCERA Real-Time Ethernet     http://www.ocera.org/
 *  --------------------------------------------------------------------
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 */

#include "defines.h"  //macro MALLOC

/* This should become a bit more generic for all platforms... */
#define rtl_printf  rt_printk
#define printf      rt_printk /* catch some probably forgotten printf's */
#define malloc      rt_malloc
#define free        rt_free

typedef __u32 in_addr_t;

static inline in_addr_t inet_addr(const char *cp)
{
    return rt_inet_aton(cp);
}


static char inet_ntoa_buf[16];

static inline char *inet_ntoa(struct in_addr in)
{
    unsigned char *octet;

    octet = (unsigned char *)&(in.s_addr);
    sprintf(inet_ntoa_buf, "%u.%u.%u.%u", octet[0], octet[1], octet[2], octet[3]);

    return inet_ntoa_buf;
}


#define CLOCK_REALTIME  0

static inline void clock_gettime(int dummy, struct timespec *time)
{
    count2timespec(rt_get_time(), time);
}


static inline int atoi(const char* nptr)
{
    return simple_strtol(nptr, (char **)NULL, 10);
}


static inline char *strdup(const char *s)
{
    size_t len = strlen(s)+1;
    char *new_s;

    new_s = MALLOC(len);
    if (new_s == NULL)
        return NULL;

    memcpy(new_s, s, len);
    return new_s;
}

#define pthread_rwlock_init         pthread_rwlock_init_rt
#define pthread_rwlock_rdlock       pthread_rwlock_rdlock_rt
#define pthread_rwlock_wrlock       pthread_rwlock_wrlock_rt
#define pthread_rwlock_unlock       pthread_rwlock_unlock_rt
#define pthread_rwlock_destroy      pthread_rwlock_destroy_rt

#define pthread_mutex_init          pthread_mutex_init_rt
#define pthread_mutex_lock          pthread_mutex_lock_rt
#define pthread_mutex_timedlock     pthread_mutex_timedlock_rt
#define pthread_mutex_unlock        pthread_mutex_unlock_rt
#define pthread_mutex_destroy       pthread_mutex_destroy_rt

#define pthread_create              pthread_create_rt
#define pthread_join                pthread_join_rt
#define pthread_exit                pthread_exit_rt


#define socket                      rt_socket
#define close                       rt_socket_close
#define setsockopt                  rt_socket_setsockopt
#define getsockopt(a, b, c, d, e)   -1
#define ioctl                       rt_socket_ioctl
#define bind                        rt_socket_bind
#define getsockname                 rt_socket_getsockname
#define recvfrom                    rt_socket_recvfrom
#define sendto                      rt_socket_sendto
