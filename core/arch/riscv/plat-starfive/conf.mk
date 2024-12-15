$(call force,CFG_RV64_core,y)

# ISA extension flags
$(call force,CFG_RISCV_ISA_C,y)
$(call force,CFG_RISCV_ISA_ZBB,y)
$(call force,CFG_RISCV_FPU,y)

$(call force,CFG_CORE_LARGE_PHYS_ADDR,y)
$(call force,CFG_CORE_RESERVED_SHM,n)
$(call force,CFG_CORE_DYN_SHM,y)

CFG_DT ?= y

# Crypto flags
$(call force,CFG_WITH_SOFTWARE_PRNG,y)

# Protection flags
$(call force,CFG_CORE_ASLR,n)
$(call force,CFG_WITH_STACK_CANARIES,n)
$(call force,CFG_CORE_SANITIZE_KADDRESS,n)

# Hart-related flags
CFG_TEE_CORE_NB_CORE = 4
CFG_NUM_THREADS ?= 8
$(call force,CFG_BOOT_SYNC_CPU,n)

$(call force,CFG_RISCV_M_MODE,n)
$(call force,CFG_RISCV_S_MODE,y)
$(call force,CFG_RISCV_PLIC,n)
$(call force,CFG_RISCV_SBI_CONSOLE,y)
$(call force,CFG_16550_UART,n)
$(call force,CFG_RISCV_TIME_SOURCE_RDTIME,y)
CFG_RISCV_MTIME_RATE ?= 10000000
CFG_RISCV_SBI ?= y
CFG_RISCV_WITH_M_MODE_SM ?= y

# TA-related flags
supported-ta-targets = ta_rv64

# Memory layout flags
CFG_TDDRAM_START ?= 0x41000000
CFG_TDDRAM_SIZE  ?= 0x01000000
CFG_TEE_RAM_VA_SIZE ?= 0x00200000
