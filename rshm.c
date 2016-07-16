#include <stdio.h>
#include <time.h>
#include <sys/shm.h>
int shmstat(int shmid){
    struct shmid_ds shm;
    if(shmctl(shmid,IPC_STAT,&shm) == -1){
        perror("shmctl");
        return -1;
    }
    printf("键值:0x%08x\n",shm.shm_perm.__key);
    printf("有效属主:%u\n",shm.shm_perm.uid);
    printf("有效属组:%u\n",shm.shm_perm.gid);
    printf("创建者:%u\n",shm.shm_perm.cuid);
    printf("创建组:%u\n",shm.shm_perm.cgid);
    printf("权限字:%#o\n",shm.shm_perm.mode);
    printf("序列号:%u\n",shm.shm_perm.__seq);
    printf("大小:%lu\n",shm.shm_segsz);
    printf("最后加载时间:%s\n",ctime(&shm.shm_atime));
    printf("最后卸载时间:%s\n",ctime(&shm.shm_dtime));
    printf("最后改变时间:%s\n",ctime(&shm.shm_ctime));
    printf("创建者进程:%u\n",shm.shm_cpid);
    printf("最后加载/卸载进程:%u\n",shm.shm_lpid);
    printf("当前加载计数:%ld\n",shm.shm_nattch);
}
//消息队列，信号量都可以这么用，拿到信息，改变一下，然后设置回去
int shmset(int shmid){
    struct shmid_ds shm;
    if(shmctl(shmid,IPC_STAT,&shm) == -1){
        perror("shmctl");
        return -1;
    }
    shm.shm_perm.mode = 0600;
    shm.shm_segsz = 8192;//不可修改
    if(shmctl(shmid,IPC_SET,&shm) == -1){
        perror("shmctl");
        return -1;
    }
    return 0;
}
int main(){
    printf("获取共享内存...\n");
    key_t key = ftok(".",100);
    if(key == -1){
        perror("ftok");
        return -1;
    }
    int shmid = shmget(key,0,0);
    if(shmid  == -1){
        perror("shmget");
        return -1;
    }
    shmstat(shmid);
    printf("加载共享内存...\n");
    void* shmaddr = shmat(shmid,NULL,0);
    if(shmaddr == (void*)-1){
        perror("shmat");
        return -1;
    }
    shmstat(shmid);
    printf("读取共享内存...\n");
    //read为I/O型函数，没有数据则会阻塞
    printf("共享内存(0x%08x/%d):%s\n",key,shmid,(char*)shmaddr);
    printf("卸载共享内存...\n");
    if(shmdt(shmaddr) == -1){
        perror("shmdt");
        return -1;
    }
    shmstat(shmid);
    shmset(shmid);
    shmstat(shmid);
    printf("大功告成!\n");
    return 0;
}
#if 0
ipcs -m 命令其实就是从struct shmid_ds结构体里拿出来的信息
zn@zn-OptiPlex-9010:~/demo/071616$ ./rshm
获取共享内存...
键值:0x64062575
有效属主:1000
有效属组:1000
创建者:1000
创建组:1000
权限字:0644
序列号:440
大小:4096
最后加载时间:Sat Jul 16 14:35:16 2016

最后卸载时间:Thu Jan  1 08:00:00 1970

最后改变时间:Sat Jul 16 14:35:16 2016

创建者进程:12622
最后加载/卸载进程:12622
当前加载计数:1
加载共享内存...
键值:0x64062575
有效属主:1000
有效属组:1000
创建者:1000
创建组:1000
权限字:0644
序列号:440
大小:4096
最后加载时间:Sat Jul 16 14:35:22 2016

最后卸载时间:Thu Jan  1 08:00:00 1970

最后改变时间:Sat Jul 16 14:35:16 2016

创建者进程:12622
最后加载/卸载进程:12647
当前加载计数:2
读取共享内存...
共享内存(0x64062575/14417967):我是12622进程写入的数据.
卸载共享内存...
键值:0x64062575
有效属主:1000
有效属组:1000
创建者:1000
创建组:1000
权限字:0644
序列号:440
大小:4096
最后加载时间:Sat Jul 16 14:35:22 2016

最后卸载时间:Sat Jul 16 14:35:22 2016

最后改变时间:Sat Jul 16 14:35:16 2016

创建者进程:12622
最后加载/卸载进程:12647
当前加载计数:1
大功告成!
#endif
