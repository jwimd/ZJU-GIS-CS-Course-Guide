```c
RIvoid * const sys_call_table[451] = {
 [0 ... 451 - 1] = sys_ni_syscall,
# 1 "./arch/riscv/include/asm/unistd.h" 1
# 24 "./arch/riscv/include/asm/unistd.h"
# 1 "./arch/riscv/include/uapi/asm/unistd.h" 1
# 26 "./arch/riscv/include/uapi/asm/unistd.h"
# 1 "./include/uapi/asm-generic/unistd.h" 1
# 34 "./include/uapi/asm-generic/unistd.h"
[0] = (sys_io_setup),

[1] = (sys_io_destroy),

[2] = (sys_io_submit),

[3] = (sys_io_cancel),


[4] = (sys_io_getevents),




[5] = (sys_setxattr),

[6] = (sys_lsetxattr),

[7] = (sys_fsetxattr),

[8] = (sys_getxattr),

[9] = (sys_lgetxattr),

[10] = (sys_fgetxattr),

[11] = (sys_listxattr),

[12] = (sys_llistxattr),

[13] = (sys_flistxattr),

[14] = (sys_removexattr),

[15] = (sys_lremovexattr),

[16] = (sys_fremovexattr),



[17] = (sys_getcwd),



[18] = (sys_lookup_dcookie),



[19] = (sys_eventfd2),



[20] = (sys_epoll_create1),

[21] = (sys_epoll_ctl),

[22] = (sys_epoll_pwait),



[23] = (sys_dup),

[24] = (sys_dup3),

[25] = (sys_fcntl),



[26] = (sys_inotify_init1),

[27] = (sys_inotify_add_watch),

[28] = (sys_inotify_rm_watch),



[29] = (sys_ioctl),



[30] = (sys_ioprio_set),

[31] = (sys_ioprio_get),



[32] = (sys_flock),



[33] = (sys_mknodat),

[34] = (sys_mkdirat),

[35] = (sys_unlinkat),

[36] = (sys_symlinkat),

[37] = (sys_linkat),
# 141 "./include/uapi/asm-generic/unistd.h"
[39] = (sys_umount),

[40] = (sys_mount),

[41] = (sys_pivot_root),



[42] = (sys_ni_syscall),



[43] = (sys_statfs),


[44] = (sys_fstatfs),


[45] = (sys_truncate),


[46] = (sys_ftruncate),



[47] = (sys_fallocate),

[48] = (sys_faccessat),

[49] = (sys_chdir),

[50] = (sys_fchdir),

[51] = (sys_chroot),

[52] = (sys_fchmod),

[53] = (sys_fchmodat),

[54] = (sys_fchownat),

[55] = (sys_fchown),

[56] = (sys_openat),

[57] = (sys_close),

[58] = (sys_vhangup),



[59] = (sys_pipe2),



[60] = (sys_quotactl),



[61] = (sys_getdents64),



[62] = (sys_lseek),

[63] = (sys_read),

[64] = (sys_write),

[65] = (sys_readv),

[66] = (sys_writev),

[67] = (sys_pread64),

[68] = (sys_pwrite64),

[69] = (sys_preadv),

[70] = (sys_pwritev),



[71] = (sys_sendfile64),




[72] = (sys_pselect6),

[73] = (sys_ppoll),




[74] = (sys_signalfd4),



[75] = (sys_vmsplice),

[76] = (sys_splice),

[77] = (sys_tee),



[78] = (sys_readlinkat),


[79] = (sys_newfstatat),

[80] = (sys_newfstat),




[81] = (sys_sync),

[82] = (sys_fsync),

[83] = (sys_fdatasync),






[84] = (sys_sync_file_range),





[85] = (sys_timerfd_create),


[86] = (sys_timerfd_settime),


[87] = (sys_timerfd_gettime),






[88] = (sys_utimensat),




[89] = (sys_acct),



[90] = (sys_capget),

[91] = (sys_capset),



[92] = (sys_personality),



[93] = (sys_exit),

[94] = (sys_exit_group),

[95] = (sys_waitid),



[96] = (sys_set_tid_address),

[97] = (sys_unshare),




[98] = (sys_futex),


[99] = (sys_set_robust_list),


[100] = (sys_get_robust_list),





[101] = (sys_nanosleep),




[102] = (sys_getitimer),

[103] = (sys_setitimer),



[104] = (sys_kexec_load),



[105] = (sys_init_module),

[106] = (sys_delete_module),



[107] = (sys_timer_create),


[108] = (sys_timer_gettime),


[109] = (sys_timer_getoverrun),


[110] = (sys_timer_settime),


[111] = (sys_timer_delete),


[112] = (sys_clock_settime),

[113] = (sys_clock_gettime),

[114] = (sys_clock_getres),

[115] = (sys_clock_nanosleep),





[116] = (sys_syslog),



[117] = (sys_ptrace),



[118] = (sys_sched_setparam),

[119] = (sys_sched_setscheduler),

[120] = (sys_sched_getscheduler),

[121] = (sys_sched_getparam),

[122] = (sys_sched_setaffinity),


[123] = (sys_sched_getaffinity),


[124] = (sys_sched_yield),

[125] = (sys_sched_get_priority_max),

[126] = (sys_sched_get_priority_min),


[127] = (sys_sched_rr_get_interval),





[128] = (sys_restart_syscall),

[129] = (sys_kill),

[130] = (sys_tkill),

[131] = (sys_tgkill),

[132] = (sys_sigaltstack),

[133] = (sys_rt_sigsuspend),

[134] = (sys_rt_sigaction),

[135] = (sys_rt_sigprocmask),

[136] = (sys_rt_sigpending),


[137] = (sys_rt_sigtimedwait),



[138] = (sys_rt_sigqueueinfo),


[139] = (sys_rt_sigreturn),



[140] = (sys_setpriority),

[141] = (sys_getpriority),

[142] = (sys_reboot),

[143] = (sys_setregid),

[144] = (sys_setgid),

[145] = (sys_setreuid),

[146] = (sys_setuid),

[147] = (sys_setresuid),

[148] = (sys_getresuid),

[149] = (sys_setresgid),

[150] = (sys_getresgid),

[151] = (sys_setfsuid),

[152] = (sys_setfsgid),

[153] = (sys_times),

[154] = (sys_setpgid),

[155] = (sys_getpgid),

[156] = (sys_getsid),

[157] = (sys_setsid),

[158] = (sys_getgroups),

[159] = (sys_setgroups),

[160] = (sys_newuname),

[161] = (sys_sethostname),

[162] = (sys_setdomainname),




[163] = (sys_getrlimit),

[164] = (sys_setrlimit),



[165] = (sys_getrusage),

[166] = (sys_umask),

[167] = (sys_prctl),

[168] = (sys_getcpu),




[169] = (sys_gettimeofday),

[170] = (sys_settimeofday),

[171] = (sys_adjtimex),




[172] = (sys_getpid),

[173] = (sys_getppid),

[174] = (sys_getuid),

[175] = (sys_geteuid),

[176] = (sys_getgid),

[177] = (sys_getegid),

[178] = (sys_gettid),

[179] = (sys_sysinfo),



[180] = (sys_mq_open),

[181] = (sys_mq_unlink),


[182] = (sys_mq_timedsend),

[183] = (sys_mq_timedreceive),



[184] = (sys_mq_notify),

[185] = (sys_mq_getsetattr),



[186] = (sys_msgget),

[187] = (sys_msgctl),

[188] = (sys_msgrcv),

[189] = (sys_msgsnd),



[190] = (sys_semget),

[191] = (sys_semctl),


[192] = (sys_semtimedop),


[193] = (sys_semop),



[194] = (sys_shmget),

[195] = (sys_shmctl),

[196] = (sys_shmat),

[197] = (sys_shmdt),



[198] = (sys_socket),

[199] = (sys_socketpair),

[200] = (sys_bind),

[201] = (sys_listen),

[202] = (sys_accept),

[203] = (sys_connect),

[204] = (sys_getsockname),

[205] = (sys_getpeername),

[206] = (sys_sendto),

[207] = (sys_recvfrom),

[208] = (sys_setsockopt),

[209] = (sys_getsockopt),

[210] = (sys_shutdown),

[211] = (sys_sendmsg),

[212] = (sys_recvmsg),



[213] = (sys_readahead),



[214] = (sys_brk),

[215] = (sys_munmap),

[216] = (sys_mremap),



[217] = (sys_add_key),

[218] = (sys_request_key),

[219] = (sys_keyctl),



[220] = (sys_clone),

[221] = (sys_execve),


[222] = (sys_mmap),


[223] = (sys_fadvise64_64),




[224] = (sys_swapon),

[225] = (sys_swapoff),

[226] = (sys_mprotect),

[227] = (sys_msync),

[228] = (sys_mlock),

[229] = (sys_munlock),

[230] = (sys_mlockall),

[231] = (sys_munlockall),

[232] = (sys_mincore),

[233] = (sys_madvise),

[234] = (sys_remap_file_pages),

[235] = (sys_mbind),

[236] = (sys_get_mempolicy),

[237] = (sys_set_mempolicy),

[238] = (sys_migrate_pages),

[239] = (sys_move_pages),



[240] = (sys_rt_tgsigqueueinfo),


[241] = (sys_perf_event_open),

[242] = (sys_accept4),


[243] = (sys_recvmmsg),
# 707 "./include/uapi/asm-generic/unistd.h"
[260] = (sys_wait4),


[261] = (sys_prlimit64),

[262] = (sys_fanotify_init),

[263] = (sys_fanotify_mark),

[264] = (sys_name_to_handle_at),

[265] = (sys_open_by_handle_at),


[266] = (sys_clock_adjtime),


[267] = (sys_syncfs),

[268] = (sys_setns),

[269] = (sys_sendmmsg),

[270] = (sys_process_vm_readv),

[271] = (sys_process_vm_writev),

[272] = (sys_kcmp),

[273] = (sys_finit_module),

[274] = (sys_sched_setattr),

[275] = (sys_sched_getattr),

[276] = (sys_renameat2),

[277] = (sys_seccomp),

[278] = (sys_getrandom),

[279] = (sys_memfd_create),

[280] = (sys_bpf),

[281] = (sys_execveat),

[282] = (sys_userfaultfd),

[283] = (sys_membarrier),

[284] = (sys_mlock2),

[285] = (sys_copy_file_range),

[286] = (sys_preadv2),

[287] = (sys_pwritev2),

[288] = (sys_pkey_mprotect),

[289] = (sys_pkey_alloc),

[290] = (sys_pkey_free),

[291] = (sys_statx),


[292] = (sys_io_pgetevents),


[293] = (sys_rseq),

[294] = (sys_kexec_file_load),
# 826 "./include/uapi/asm-generic/unistd.h"
[424] = (sys_pidfd_send_signal),

[425] = (sys_io_uring_setup),

[426] = (sys_io_uring_enter),

[427] = (sys_io_uring_register),

[428] = (sys_open_tree),

[429] = (sys_move_mount),

[430] = (sys_fsopen),

[431] = (sys_fsconfig),

[432] = (sys_fsmount),

[433] = (sys_fspick),

[434] = (sys_pidfd_open),


[435] = (sys_clone3),


[436] = (sys_close_range),


[437] = (sys_openat2),

[438] = (sys_pidfd_getfd),

[439] = (sys_faccessat2),

[440] = (sys_process_madvise),

[441] = (sys_epoll_pwait2),

[442] = (sys_mount_setattr),

[443] = (sys_quotactl_fd),


[444] = (sys_landlock_create_ruleset),

[445] = (sys_landlock_add_rule),

[446] = (sys_landlock_restrict_self),



[447] = (sys_memfd_secret),


[448] = (sys_process_mrelease),


[449] = (sys_futex_waitv),


[450] = (sys_set_mempolicy_home_node),
# 27 "./arch/riscv/include/uapi/asm/unistd.h" 2
# 45 "./arch/riscv/include/uapi/asm/unistd.h"
[(244 + 15)] = (sys_riscv_flush_icache),
# 25 "./arch/riscv/include/asm/unistd.h" 2
# 18 "arch/riscv/kernel/syscall_table.c" 2
};

```

