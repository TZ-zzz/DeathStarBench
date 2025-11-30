#ifndef TRACING_MAGIC_H
#define TRACING_MAGIC_H

// Replace these with the actual Assembly for your specific simulator (Gem5/SST/QEMU)
// For now, we define them as memory barriers so the compiler doesn't reorder them.

// #define MAGIC_START_WORKLOAD()  __asm__ __volatile__ ("xchg %%r10, %%r10" : : : "r10"); 
// #define MAGIC_END_WORKLOAD()    __asm__ __volatile__ ("xchg %%r11, %%r11" : : : "r11");

// // Define more magic instructions For PostCompose workload
// #define MAGIC_TEXT_SEND()      __asm__ __volatile__ ("xchg %%r12, %%r12" : : : "r12");
// #define MAGIC_TEXT_RETURN()    __asm__ __volatile__ ("xchg %%r13, %%r13" : : : "r13");
// #define MAGIC_USER_SEND()      __asm__ __volatile__ ("xchg %%r14, %%r14" : : : "r14");
// #define MAGIC_USER_RETURN()    __asm__ __volatile__ ("xchg %%r15, %%r15" : : : "r15");
// #define MAGIC_HOME_TIMELINE_SEND()  __asm__ __volatile__ ("xchg %%r8, %%r8" : : : "r8");
// #define MAGIC_HOME_TIMELINE_RETURN()  __asm__ __volatile__ ("xchg %%r9, %%r9" : : : "r9");
// #define MAGIC_USER_TIMELINE_SEND()  __asm__ __volatile__ ("xchg %%rsi, %%rsi" : : : "rsi");
// #define MAGIC_USER_TIMELINE_RETURN()  __asm__ __volatile__ ("xchg %%rdi, %%rdi" : : : "rdi");
#define MAGIC_START_WORKLOAD()  printf("start_workload\n"); 
#define MAGIC_END_WORKLOAD()    printf("end_workload\n");

// Define more magic instructions For PostCompose workload
#define MAGIC_TEXT_SEND()      printf("text_send\n");
#define MAGIC_TEXT_RETURN()    printf("text_return\n");
#define MAGIC_USER_SEND()      printf("user_send\n");
#define MAGIC_USER_RETURN()    printf("user_return\n");
#define MAGIC_HOME_TIMELINE_SEND()  printf("home_timeline_send\n");
#define MAGIC_HOME_TIMELINE_RETURN()  printf("home_timeline_return\n");
#define MAGIC_USER_TIMELINE_SEND()  printf("user_timeline_send\n");
#define MAGIC_USER_TIMELINE_RETURN()  printf("user_timeline_return\n");

#endif