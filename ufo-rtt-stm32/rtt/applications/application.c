/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

/**
 * @addtogroup STM32
 */
/*@{*/

#include <board.h>
#include <rtthread.h>

#ifdef RT_USING_DFS
/* dfs init */
#include <dfs_init.h>
/* dfs filesystem:ELM filesystem init */
#include <dfs_elm.h>
/* dfs Filesystem APIs */
#include <dfs_fs.h>
#endif

#ifdef RT_USING_LWIP
#include <lwip/sys.h>
#include <lwip/api.h>
#include <netif/ethernetif.h>
#endif

void rt_init_thread_entry(void* parameter)
{
/* Filesystem Initialization */
#ifdef RT_USING_DFS
	{
		/* init the device filesystem */
		dfs_init();

#ifdef RT_USING_DFS_ELMFAT
		/* init the elm chan FatFs filesystam*/
		elm_init();

		rt_hw_sdcard_init();

		/* mount sd card fat partition 1 as root directory */
		if (dfs_mount("spi0", "/", "elm", 0, 0) == 0)
		{
			rt_kprintf("File System initialized!\n");
		}
		else
        {
			rt_kprintf("File System initialzation failed!\n");
        }
#endif
	}
#endif

#if 0
/* LwIP Initialization */
#ifdef RT_USING_LWIP
	{
		extern void lwip_sys_init(void);
		/* register ethernetif device */
		eth_system_device_init();

		// rt_hw_wlan_dev_init();

		/* init lwip system */
		lwip_sys_init();
		rt_kprintf("TCP/IP initialized!\n");
	}
#endif
#endif
}

int rt_application_init()
{
	rt_thread_t tid;
  extern void led_thread_init(void);
  extern void ahrs_thread_init(void);
	tid = rt_thread_create("init",
								rt_init_thread_entry, RT_NULL,
								2048, RT_THREAD_PRIORITY_MAX/3, 20);

	if (tid != RT_NULL)
		rt_thread_startup(tid);

    //led_thread_init();
    ahrs_thread_init();
	return 0;
}

/*@}*/
