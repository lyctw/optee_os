/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright 2022 NXP
 */

#ifndef __SBI_H
#define __SBI_H

#if defined(CFG_RISCV_SBI)

/* SBI return error codes */
#define SBI_SUCCESS			 0
#define SBI_ERR_FAILURE			-1
#define SBI_ERR_NOT_SUPPORTED		-2
#define SBI_ERR_INVALID_PARAM		-3
#define SBI_ERR_DENIED			-4
#define SBI_ERR_INVALID_ADDRESS		-5
#define SBI_ERR_ALREADY_AVAILABLE	-6
#define SBI_ERR_ALREADY_STARTED		-7
#define SBI_ERR_ALREADY_STOPPED		-8

/* SBI Extension IDs */
#define SBI_EXT_0_1_CONSOLE_PUTCHAR	0x01
#define SBI_EXT_BASE			0x10
#define SBI_EXT_HSM			0x48534D
#define SBI_EXT_DBCN			0x4442434E
#define SBI_EXT_TEE			0x544545
#define SBI_EXT_RPXY			0x52505859

#ifndef __ASSEMBLER__

/* SBI function IDs for Base extension */
enum sbi_ext_base_fid {
	SBI_EXT_BASE_GET_SPEC_VERSION = 0,
	SBI_EXT_BASE_GET_IMP_ID,
	SBI_EXT_BASE_GET_IMP_VERSION,
	SBI_EXT_BASE_PROBE_EXT,
	SBI_EXT_BASE_GET_MVENDORID,
	SBI_EXT_BASE_GET_MARCHID,
	SBI_EXT_BASE_GET_MIMPID,
};

/* SBI function IDs for HSM extension */
enum sbi_ext_hsm_fid {
	SBI_EXT_HSM_HART_START = 0,
	SBI_EXT_HSM_HART_STOP,
	SBI_EXT_HSM_HART_GET_STATUS,
	SBI_EXT_HSM_HART_SUSPEND,
};

/* SBI function IDs for Debug Console extension */
enum sbi_ext_dbcn_fid {
	SBI_EXT_DBCN_CONSOLE_WRITE = 0,
	SBI_EXT_DBCN_CONSOLE_READ = 1,
	SBI_EXT_DBCN_CONSOLE_WRITE_BYTE = 2,
};

enum sbi_ext_rpxy_fid {
	SBI_EXT_RPXY_PROBE = 0,
	SBI_EXT_RPXY_SETUP_SHMEM,
	SBI_EXT_RPXY_SEND_NORMAL_MSG,
	SBI_EXT_RPXY_SEND_POSTED_MSG,
	SBI_EXT_RPXY_GET_NOTIFICATIONS,
};

#include <compiler.h>
#include <encoding.h>
#include <stdint.h>
#include <sys/cdefs.h>
#include <types_ext.h>
#include <util.h>

struct sbiret {
	long error;
	long value;
};

#define _sbi_ecall(ext, fid, arg0, arg1, arg2, arg3, arg4, arg5, ...) ({  \
	register unsigned long a0 asm("a0") = (unsigned long)arg0; \
	register unsigned long a1 asm("a1") = (unsigned long)arg1; \
	register unsigned long a2 asm("a2") = (unsigned long)arg2; \
	register unsigned long a3 asm("a3") = (unsigned long)arg3; \
	register unsigned long a4 asm("a4") = (unsigned long)arg4; \
	register unsigned long a5 asm("a5") = (unsigned long)arg5; \
	register unsigned long a6 asm("a6") = (unsigned long)fid;  \
	register unsigned long a7 asm("a7") = (unsigned long)ext;  \
	asm volatile ("ecall" \
		: "+r" (a0), "+r" (a1) \
		: "r" (a2), "r" (a3), "r" (a4), "r" (a5), "r"(a6), "r"(a7) \
		: "memory"); \
	(struct sbiret){ .error = a0, .value = a1 }; \
})

#define sbi_ecall(...) _sbi_ecall(__VA_ARGS__, 0, 0, 0, 0, 0, 0, 0)

int sbi_probe_extension(int extid);
void sbi_console_putchar(int ch);
int sbi_dbcn_write_byte(unsigned char ch);
int sbi_hsm_hart_start(uint32_t hartid, paddr_t start_addr, unsigned long arg);

int sbi_rpxy_setup_shmem(unsigned int hartid);
vaddr_t sbi_rpxy_get_shmem(void);
int sbi_rpxy_send_normal_message(uint32_t transportid,
				 uint32_t srvgrpid, uint8_t srvid,
				 void *tx, unsigned long tx_msglen,
				 void *rx, unsigned long *rx_msglen);

void thread_return_to_udomain_by_rpxy(unsigned long arg0, unsigned long arg1,
				      unsigned long arg2, unsigned long arg3,
				      unsigned long arg4, unsigned long arg5);

#endif /*__ASSEMBLER__*/
#endif /*defined(CFG_RISCV_SBI)*/
#endif /*__SBI_H*/
