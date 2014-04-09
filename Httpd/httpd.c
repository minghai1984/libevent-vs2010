#include <stdio.h>  
  
#define WIN32_LEAN_AND_MEAN  
#include <windows.h>  
#include <winsock2.h>  
  
#include <event.h>  
#include <evhttp.h>  
  
void root_handler(struct evhttp_request *req, void *arg)  
{  
    struct evbuffer *buf = evbuffer_new();  
    if(!buf){  
        puts("failed to create response buffer");  
        return;  
    }  
  
    evbuffer_add_printf(buf, "Hello: %s\n", evhttp_request_uri(req));  
    evhttp_send_reply(req, HTTP_OK, "OK", buf);  
}  
  
void generic_handler(struct evhttp_request *req, void *arg)  
{  
    struct evbuffer *buf = evbuffer_new();  
    if(!buf){  
        puts("failed to create response buffer");  
        return;  
    }  
  
    evbuffer_add_printf(buf, "Requested: %s\n", evhttp_request_uri(req));  
    evhttp_send_reply(req, HTTP_OK, "OK", buf);  
}  
  
int main(int argc, wchar_t* argv[])  
{  
  struct evhttp *httpd;  
  
  WSADATA wsaData;  
  DWORD Ret;  
  if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)  {  
    printf("WSAStartup failed with error %d\n", Ret);  
    return -1;  
  }  
  
    event_init();  
  
    httpd = evhttp_start("0.0.0.0", 8505);  
    if(!httpd){  
    return 1;  
  }  
  
    evhttp_set_cb(httpd, "/", root_handler, NULL);  
    evhttp_set_gencb(httpd, generic_handler, NULL);  
  
  printf("httpd server start OK!\n");  
  
    event_dispatch();  
  
    evhttp_free(httpd);  
  
  WSACleanup();  
    return 0;  
}  