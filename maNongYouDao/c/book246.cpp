/* 
 *  此程序演示socket通信服务端
 *  作者：豫让 日期：20190601
*/
#include "_public.h"

// 初始化服务端的socket，port为通信端口
// 返回值：成功返回初始化的socket，失败返回-1。
int initserver(int port);

int main()
{
  int listenfd=initserver(5000);  // 服务端用于监听的socket
  if (listenfd<=0) { printf("服务端初始化失败，程序退出。\n"); return -1; }

  // 接受客户端的连接。
  int  clientfd;                  // 客户端的socket

  while (1)
  {
    if ( (clientfd=accept(listenfd,0,0)) <= 0) continue;

    printf("客户端已连接。\n");

    // 与客户端通信，接收客户端发过来的报文后，回复ok。
    char strbuffer[1024];

    while (1)
    {
      memset(strbuffer,0,sizeof(strbuffer));
      if (recv(clientfd,strbuffer,sizeof(strbuffer),0)<=0) break;
      printf("接收：%s\n",strbuffer);

      strcpy(strbuffer,"ok");
      if (send(clientfd,strbuffer,strlen(strbuffer),0)<=0) break;
      printf("发送：%s\n",strbuffer);
    }

    close(clientfd); 
    printf("客户端已断开连接。\n");
  }

  close(listenfd); // 关闭socket
}

// 初始化服务端的socket，port为通信端口
// 返回值：成功返回初始化的socket，失败返回-1。
int initserver(int port)
{
  int listenfd = socket(AF_INET,SOCK_STREAM,0);  // 创建服务端的socket

  // 把服务端用于通信的地址和端口绑定到socket上
  struct sockaddr_in servaddr;    // 服务端地址信息的数据结构
  memset(&servaddr,0,sizeof(servaddr));
  servaddr.sin_family = AF_INET;  // 协议族，在socket编程中只能是AF_INET
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);  // 本主机的任意ip地址
  servaddr.sin_port = htons(port);  // 绑定通信端口
  if (bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) != 0 )
  { perror("bind"); close(listenfd); return -1; }

  // 把socket设置为监听模式
  if (listen(listenfd,5) != 0 ) { perror("listen"); close(listenfd); return -1; }

  return listenfd;
}

