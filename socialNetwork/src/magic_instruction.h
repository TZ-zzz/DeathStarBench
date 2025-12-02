#ifndef TRACING_MAGIC_H
#define TRACING_MAGIC_H

#define MAGIC_START_WORKLOAD()  __asm__ __volatile__ ("xchg %%r10, %%r10" : : : "r10"); 
#define MAGIC_END_WORKLOAD()    __asm__ __volatile__ ("xchg %%r11, %%r11" : : : "r11");

// Define more magic instructions For PostCompose workload
#define MAGIC_SEND_REQUEST(int caller, int callee)  __asm__ __volatile__ ("mv %[id], %%r12" : : [id] "r" (callee) : "r12");
#define MAGIC_RECEIVE_RESPONSE(int caller, int callee)    __asm__ __volatile__ ("mv %[id], %%r13" : : [id] "r" (caller) : "r13");

#define social_graph_service 2
#define social_graph_mongodb 3
#define social_graph_redis 4
#define home_timeline_redis 5
#define compose_post_service 6
#define post_storage_service 7
#define post_storage_memcached 8
#define post_storage_mongodb 9
#define user_timeline_service 10
#define user_timeline_redis 11
#define user_timeline_mongodb 12
#define url_shorten_service 13
#define url_shorten_memcached 14
#define url_shorten_mongodb 15
#define user_service 16
#define user_memcached 17
#define user_mongodb 18
#define media_service 19
#define media_memcached 20
#define media_mongodb 21
#define text_service 22
#define unique_id_service 23
#define user_mention_service 24
#define home_timeline_service 25
#define nginx_thrift 26
#define media_frontend 27
#define jaeger_agent 28

#endif