#ifndef SYSCALLS_H
#define SYSCALLS_H

/* Tasks */

static const unsigned int tcf_established_tasks_addrs[] = { 0x102F0C1C, 0x102F1348, 0x102F0688, 0x102F0E18 };
#define TCF_Established_Tasks SYSCALL_CUSTOM(tcf_established_tasks_addrs, unsigned, void)

static const unsigned int tcc_current_task_pointer_addrs[] = { 0x102EFBF4, 0x102F0320, 0x102EF660, 0x102EFDF0 };
#define TCC_Current_Task_Pointer SYSCALL_CUSTOM(tcc_current_task_pointer_addrs, void*, void)

static const unsigned int tcf_task_information_addrs[] = { 0x102F0D10, 0x102F143C, 0x102F077C, 0x102F0F0C };
#define TCF_Task_Information SYSCALL_CUSTOM(tcf_task_information_addrs, int, void*, char*, unsigned char*, unsigned*, unsigned char*, unsigned char*, unsigned*, void**, unsigned*, unsigned*)

static const unsigned int tcf_task_pointers_addrs[] = { 0x102F0E80, 0x102F15AC, 0x102F08EC, 0x102F107C };
#define TCF_Task_Pointers SYSCALL_CUSTOM(tcf_task_pointers_addrs, unsigned, void**, unsigned)

static const unsigned int tcc_terminate_task_addrs[] = { 0x102F06C0, 0x102F0DEC, 0x102F012C, 0x102F08BC };
#define TCC_Terminate_Task SYSCALL_CUSTOM(tcc_terminate_task_addrs, unsigned, void*)

/* Dynamic memory */

static const unsigned int dmf_established_memory_pools_addrs[] = { 0x10273948, 0x10274074, 0x102733B8, 0x10273B48 };
#define DMF_Established_Memory_Pools SYSCALL_CUSTOM(dmf_established_memory_pools_addrs, unsigned, void)

static const unsigned int dmf_memory_pool_information_addrs[] = { 0x10273960, 0x1027408C, 0x102733D0, 0x10273B60 };
#define DMF_Memory_Pool_Information SYSCALL_CUSTOM(dmf_memory_pool_information_addrs, unsigned, void*, char*, void**, unsigned*, unsigned*, unsigned*, unsigned char*, unsigned*, void*)

static const unsigned int dmf_memory_pool_pointers_addrs[] = { 0x10273A6C, 0x10274198, 0x102734DC, 0x10273C6C };
#define DMF_Memory_Pool_Pointers SYSCALL_CUSTOM(dmf_memory_pool_pointers_addrs, unsigned, void**, unsigned)

static const unsigned int dmc_delete_memory_pool_addrs[] = { 0x10277C28, 0x10278354, 0x10277698, 0x10277E28 };
#define DMC_Delete_Memory_Pool SYSCALL_CUSTOM(dmc_delete_memory_pool_addrs, unsigned, void*)

/* Event groups */

static const unsigned int evf_established_event_groups_addrs[] = { 0x103D0284, 0x103D09B4, 0x103CDB44, 0x103CE2D4 };
#define EVF_Established_Event_Groups SYSCALL_CUSTOM(evf_established_event_groups_addrs, unsigned, void)

static const unsigned int evf_event_group_information_addrs[] = { 0x103D029C, 0x103D09CC, 0x103CDB5C, 0x103CE2EC };
#define EVF_Event_Group_Information SYSCALL_CUSTOM(evf_event_group_information_addrs, unsigned, void*, char*, unsigned*, unsigned*, void**)

static const unsigned int evf_event_group_pointers_addrs[] = { 0x103D036C, 0x103D0A9C, 0x103CDC2C, 0x103CE3BC };
#define EVF_Event_Group_Pointers SYSCALL_CUSTOM(evf_event_group_pointers_addrs, unsigned, void**, unsigned)

static const unsigned int evc_delete_event_group_addrs[] = { 0x10273E84, 0x102745B0, 0x102738F4, 0x10274084 };
#define EVC_Delete_Event_Group SYSCALL_CUSTOM(evc_delete_event_group_addrs, unsigned, void*)

/* Queues */

static const unsigned int quf_established_queues_addrs[] = { 0x1027685C, 0x10276F88, 0x102762CC, 0x10276A5C };
#define QUF_Established_Queues SYSCALL_CUSTOM(quf_established_queues_addrs, unsigned, void)

static const unsigned int quf_queue_information_addrs[] = { 0x10276874, 0x10276FA0, 0x102762E4, 0x10276A74 };
#define QUF_Queue_Information SYSCALL_CUSTOM(quf_queue_information_addrs, unsigned, void*, char*, void**, unsigned*, unsigned*, unsigned*, unsigned char*, unsigned*, unsigned char*, unsigned*, void**)

static const unsigned int quf_queue_pointers_addrs[] = { 0x102769AC, 0x102770D8, 0x1027641C, 0x10276BAC };
#define QUF_Queue_Pointers SYSCALL_CUSTOM(quf_queue_pointers_addrs, unsigned, void**, unsigned)

static const unsigned int quc_delete_queue_addrs[] = { 0x1027671C, 0x10276E48, 0x1027618C, 0x1027691C };
#define QUC_Delete_Queue SYSCALL_CUSTOM(quc_delete_queue_addrs, unsigned, void*)

static const unsigned int quc_receive_from_queue_addrs[] = { 0x10275AC0, 0x102761EC, 0x10275530, 0x10275CC0 };
#define QUC_Receive_From_Queue SYSCALL_CUSTOM(quc_receive_from_queue_addrs, unsigned, void*, void*, unsigned, unsigned*, unsigned)

/* Semaphores */

static const unsigned int smf_established_semaphores_addrs[] = { 0x103D15A4, 0x0, 0x0, 0x0 };
#define SMF_Established_Semaphores SYSCALL_CUSTOM(smf_established_semaphores_addrs, unsigned, void)

static const unsigned int smf_semaphore_information_addrs[] = { 0x103D15BC, 0x0, 0x0, 0x0 };
#define SMF_Semaphore_Information SYSCALL_CUSTOM(smf_semaphore_information_addrs, unsigned, void*, char*, unsigned*, unsigned char*, unsigned*, void**)

static const unsigned int smf_semaphore_pointers_addrs[] = { 0x103D16A8, 0x0, 0x0, 0x0 };
#define SMF_Semaphore_Pointers SYSCALL_CUSTOM(smf_semaphore_pointers_addrs, unsigned, void**, unsigned)

static const unsigned int smc_delete_semaphore_addrs[] = { 0x10276C50, 0x0, 0x0, 0x0 };
#define SMC_Delete_Semaphore SYSCALL_CUSTOM(smc_delete_semaphore_addrs, unsigned, void*)

/* Mailboxes */

static const unsigned int mbf_established_mailboxes_addrs[] = { 0x103D08F8, 0x0, 0x0, 0x0 };
#define MBF_Established_Mailboxes SYSCALL_CUSTOM(mbf_established_mailboxes_addrs, unsigned, void)

static const unsigned int mbf_mailbox_information_addrs[] = { 0x103D0910, 0x0, 0x0, 0x0 };
#define MBF_Mailbox_Information SYSCALL_CUSTOM(mbf_mailbox_information_addrs, unsigned, void*, char*, unsigned char*, unsigned char*, unsigned*, void**)

static const unsigned int mbf_mailbox_pointers_addrs[] = { 0x103D09FC, 0x0, 0x0, 0x0 };
#define MBF_Mailbox_Pointers SYSCALL_CUSTOM(mbf_mailbox_pointers_addrs, unsigned, void**, unsigned)

static const unsigned int mbc_delete_mailbox_addrs[] = { 0x103D0824, 0x0, 0x0, 0x0 };
#define MBC_Delete_Mailbox SYSCALL_CUSTOM(mbc_delete_mailbox_addrs, unsigned, void*)

#endif