#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/bank.h"
#include "../inc/network.h"
static const char* g_svrip = NULL;
void menu_loop(int (*menu)(void),int (*on_menu[])(void),size_t size){
    for(;;){
        int id = menu();//显示菜单并获取用户选项id
        if(id < 0 || size <= id){
            printf("无效选择!\n");
        }
        else if(on_menu[id]() == -1){
            break;//继续菜单循环
        }
    }
}
int main_menu(){
    printf("------\n");
    printf("网络银行\n");
    printf("------\n");
    printf("[1] 开户\n");
    printf("[2] 清户\n");
    printf("[3] 存款\n");
    printf("[4] 取款\n");
    printf("[5] 查询\n");
    printf("[6] 转账\n");
    printf("[0] 退出\n");
    printf("------\n");
    printf("请选择:");
    int id = -1;
    scanf("%d",&id);
    scanf("%*[^\n]");
    scanf("%*c");
    return id;
}
int on_quit(){
    printf("谢谢使用，再见!\n");
    return -1;
}
int on_open(){
    printf("开户\n");
    OPEN_REQUEST req;//不需要交易类型和pid了
    printf("户名:");
    scanf("%s",req.name);
    printf("密码:");
    scanf("%s",req.passwd);
    printf("金额:");
    scanf("%lf",&req.balance);
    int sockfd = sndreq(g_svrip,TYPE_OPEN,&req,sizeof(req));
    printf("sockfd = %d\n",sockfd);
    if(sockfd == -1){
        return 0;
    }
    OPEN_RESPOND res;
    if(rcvres(sockfd,&res,sizeof(res)) == -1){
        printf("client recres -1\n");
        return 0;
    }
    if(strlen(res.error)){
        printf("%s\n",res.error);
        return 0;
    }
    printf("账号:%d\n",res.id);
    return 0;
}
int on_close(){
    printf("清户\n");
    return 0;
}
int on_save(){
    printf("存款\n");
    return 0;
}
int on_withdraw(){
    printf("取款\n");
    return 0;
}
int on_query(){
    QUERY_REQUEST req;
    printf("账号:");
    scanf("%d",&req.id);
    printf("户名:");
    scanf("%s",req.name);
    printf("密码:");
    scanf("%s",req.passwd);
    int sockfd = sndreq(g_svrip,TYPE_QUERY,&req,sizeof(req));
    if(sockfd == -1){
        return 0;
    }
    QUERY_RESPOND res;
    if(rcvres(sockfd,&res,sizeof(res)) == -1){
        return 0;
    }
    if(strlen(res.error)){
        printf("%s\n",res.error);
        return 0;
    }
    printf("余额:%.2lf\n",res.balance);
    printf("查询\n");
    return 0;
}
int on_transfer(){
    printf("转账\n");
    return 0;
}
int main(int argc,char* argv[]){
    if(argc < 2){
        printf("用法:%s <服务器IP地址>\n",argv[0]);
        return -1;
    }
    g_svrip = argv[1];
    int (*on_menu[])() = {
            on_quit,
            on_open,
            on_close,
            on_save,
            on_withdraw,
            on_query,
            on_transfer};
    menu_loop(main_menu,on_menu,sizeof(on_menu)/sizeof(on_menu[0]));
    return 0;
}
