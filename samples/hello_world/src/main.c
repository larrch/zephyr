/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "foo.h"

// #include <kernel.h>
// #include <sys/util.h>
// #include <sys/printk.h>

#include <stdlib.h> // malloc
#include <string.h> // memset memcpy
#include <stdio.h> // printf

uint8_t g_big[1000];

int main(void)
{
	uintptr_t src = 8;
	int *dst;

	printk("sizeof(void *) %dBytes\n", sizeof(uintptr_t));
	printk("sizeof(long) %dBytes\n", sizeof(long));

	printf("Support printf()\n");
	printk("Support printk()\n");

	memset(&src, 7, sizeof(src));
	printk("Support memset() %08lx\n", src);

	dst = (int *)(uintptr_t)&g_big;
	printk("Support global variant %08x\n", *dst);

	atomic_set_bit(dst, 4);
	printk("Support atomic_set_bit %08x\n", *dst);

	memcpy(dst, &src, sizeof(src));
	printk("Support memcpy() %08x\n", *dst);

#if (CONFIG_HEAP_MEM_POOL_SIZE > 0)
	printk("CONFIG_HEAP_MEM_POOL_SIZE=%d\n", CONFIG_HEAP_MEM_POOL_SIZE);
#endif

	dst = malloc(sizeof(*dst));
	printk("Support malloc() \n");
	free(dst);
	printk("Support free() \n");

	dst = calloc(1, sizeof(*dst));
	printk("Support calloc() \n");
	free(dst);

	dst = k_calloc(1, sizeof(int));
	printk("Support k_calloc() \n");
	free(dst);

	dst = k_malloc(sizeof(*dst));
	printk("Support k_malloc()\n");
	free(dst);

#ifdef FOO_EN
	foo(FOO_VAL);
#endif
	// ~/zephyrproject/zephyr-sdk-0.16.1/sysroots/x86_64-pokysdk-linux/usr/bin/qemu-system-i386
	//qemu-system-x86_64 -m 9 -cpu qemu32,+nx,+pae -device isa-debug-exit,iobase=0xf4,iosize=0x04 -no-reboot -nographic -net none -pidfile qemu.pid -chardev stdio,id=con,mux=on -serial chardev:con -mon chardev=con,mode=readline -icount shift=5,align=off,sleep=off -rtc clock=vm -kernel ~/zephyrproject/zephyr/build/zephyr/zephyr.elf
	//qemu-system-x86_64 -nographic -kernel ~/zephyrproject/zephyr/build/zephyr/zephyr.elf
	printf("Hello World! %s\n", CONFIG_BOARD);
	return 0;
}
