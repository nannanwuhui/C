#ifndef _NETWORK_H
#define _NETWORK_H
#include <sys/types.h>
//服务端
int init(unsigned short type);
void deinit(int sockfd);
int accreq(int sockfd);
int rcvreq(int connfd,void* req,size_t len);
int sndres(int connfd, const void* res, size_t len);
//客户端
int sndreq(const char* server,unsigned short type,const void* req,size_t len);
int rcvres(int sockfd,void* res,size_t len);
#endif //_NETWORK_H
