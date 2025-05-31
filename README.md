# OP-TEE Trusted OS
This git contains source code for the secure side implementation of OP-TEE
project.

All official OP-TEE documentation has moved to http://optee.readthedocs.io.

// OP-TEE core maintainers

## RISC-V test combinations

Combination:

* CFG_DYN_CONFIG
* CFG_DYN_STACK_CONFIG
* CFG_RISCV_MMU_MODE=39,48,57
* CFG_CORE_ASLR
* CFG_CORE_ASLR_SEED
* CFG_TA_ASLR

### Test Set 1

- Fix: TA_ASLR=n|CORE_ASLR=n
- Toggle: DYN_CONFIG

| No. | Sv57 | Sv48 | Sv39 | TA_ASLR | CORE_ASLR | high seed | low seed | DYN_CONFIG |
| --- | ---- | ---- | ---- | ------- | --------- | --------- | -------- | ---------- |
| 000 |    0 |    0 |    1 |       0 |         0 |         - |        - |          0 |
| 001 |    0 |    0 |    1 |       0 |         0 |         - |        - |          1 |
| 002 |    0 |    1 |    0 |       0 |         0 |         - |        - |          0 |
| 003 |    0 |    1 |    0 |       0 |         0 |         - |        - |          1 |
| 004 |    1 |    0 |    0 |       0 |         0 |         - |        - |          0 |
| 005 |    1 |    0 |    0 |       0 |         0 |         - |        - |          1 |

### Test Set 2

high seed: CFG_CORE_ASLR_SEED=0xffffffff00005678
low seed:  CFG_CORE_ASLR_SEED=0x0000000012345678

| No. | Sv57 | Sv48 | Sv39 | TA_ASLR | CORE_ASLR | high seed | low seed | DYN_CONFIG |
| --- | ---- | ---- | ---- | ------- | --------- | --------- | -------- | ---------- |
| 006 |    0 |    0 |    1 |       0 |         1 |         0 |        1 |          0 |
| 007 |    0 |    0 |    1 |       0 |         1 |         0 |        1 |          1 |
| 008 |    0 |    1 |    0 |       0 |         1 |         0 |        1 |          0 |
| 009 |    0 |    1 |    0 |       0 |         1 |         0 |        1 |          1 |
| 010 |    1 |    0 |    0 |       0 |         1 |         0 |        1 |          0 |
| 011 |    1 |    0 |    0 |       0 |         1 |         0 |        1 |          1 |
| 012 |    0 |    0 |    1 |       0 |         1 |         1 |        0 |          0 |
| 013 |    0 |    0 |    1 |       0 |         1 |         1 |        0 |          1 |
| 014 |    0 |    1 |    0 |       0 |         1 |         1 |        0 |          0 |
| 015 |    0 |    1 |    0 |       0 |         1 |         1 |        0 |          1 |
| 016 |    1 |    0 |    0 |       0 |         1 |         1 |        0 |          0 |
| 017 |    1 |    0 |    0 |       0 |         1 |         1 |        0 |          1 |

### Test Set 3

Random seed w/ Sv36/48/57

| No. | Sv57 | Sv48 | Sv39 | TA_ASLR | CORE_ASLR | high seed | low seed | DYN_CONFIG |
| --- | ---- | ---- | ---- | ------- | --------- | --------- | -------- | ---------- |
| 018 |    0 |    0 |    1 |       0 |         1 |         - |        - |          0 |
| 019 |    0 |    1 |    0 |       0 |         1 |         - |        - |          0 |
| 020 |    1 |    0 |    0 |       0 |         1 |         - |        - |          0 |

### Test Set 4

Random seed w/ Sv36/48/57
CFG_DYN_{STACK_}CONFIG on/off

| No. | Sv57 | Sv48 | Sv39 | TA_ASLR | CORE_ASLR | high seed | low seed | DYN_CONFIG | DYN_STACK_CONFIG |
| --- | ---- | ---- | ---- | ------- | --------- | --------- | -------- | ---------- | ---------------- |
| 021 |    0 |    0 |    1 |       0 |         1 |         - |        - |          0 |                0 |
| 022 |    0 |    0 |    1 |       0 |         1 |         - |        - |          1 |                1 |
| 023 |    0 |    1 |    0 |       0 |         1 |         - |        - |          0 |                0 |
| 024 |    0 |    1 |    0 |       0 |         1 |         - |        - |          1 |                1 |
| 025 |    1 |    0 |    0 |       0 |         1 |         - |        - |          0 |                0 |
| 026 |    1 |    0 |    0 |       0 |         1 |         - |        - |          1 |                1 |

### Test Set 5

Random seed w/ Sv36/48/57
CFG_DYN_{STACK_}CONFIG on/off
TA_ASLR on

| No. | Sv57 | Sv48 | Sv39 | TA_ASLR | CORE_ASLR | high seed | low seed | DYN_CONFIG | DYN_STACK_CONFIG |
| --- | ---- | ---- | ---- | ------- | --------- | --------- | -------- | ---------- | ---------------- |
| 027 |    0 |    0 |    1 |       1 |         1 |         - |        - |          0 |                0 |
| 028 |    0 |    0 |    1 |       1 |         1 |         - |        - |          1 |                1 |
| 029 |    0 |    1 |    0 |       1 |         1 |         - |        - |          0 |                0 |
| 030 |    0 |    1 |    0 |       1 |         1 |         - |        - |          1 |                1 |
| 031 |    1 |    0 |    0 |       1 |         1 |         - |        - |          0 |                0 |
| 032 |    1 |    0 |    0 |       1 |         1 |         - |        - |          1 |                1 |
