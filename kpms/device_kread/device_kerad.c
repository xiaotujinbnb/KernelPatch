#include <compiler.h>
#include <kpmodule.h>
#include <linux/printk.h>
//#include <linux/uio.h>
#include <uapi/asm-generic/unistd.h>
#include <linux/uaccess.h>
#include <linux/mm_types.h>
#include <linux/errno.h>
#include <linux/sched/mm.h>
#include <linux/sched.h> //task
#include <linux/err.h>
#include <hook.h>
#include <ktypes.h>
#include <ctype.h>
#include <linux/kallsyms.h>
#include <linux/fs.h>
#include <stdarg.h>

#include "device_kerad.h"

KPM_NAME("kpmdevice");
KPM_VERSION("1.0.0");
KPM_LICENSE("GPL v2");
KPM_AUTHOR("tuzi");
KPM_DESCRIPTION("kpm create device \n");

#define GET_MAJOR(version) (((version) >> 16) & 0xFF)
#define GET_MINOR(version) (((version) >> 8) & 0xFF)
#define GET_PATCH(version) ((version) & 0xFF)
#define bits(n, high, low) (((n) << (63u - (high))) >> (63u - (high) + (low)))


#define CMD_IOCTL 226  // 定义一个 ioctl 命令



#define DEVICE_NAME "tuzi_misc_device"




#ifdef MODULE
 struct module __this_module;
#define THIS_MODULE (&__this_module)
#else
#define THIS_MODULE ((struct module *)0)
#endif


struct miscdevice  {
	int minor;  // 设备的次设备号，用于标识该设备。通常使用 MISC_DYNAMIC_MINOR 动态分配。
	const char *name;  // 设备名称，该名称用于在 /dev 目录下创建对应的设备节点。
	const struct file_operations *fops;  // 指向该设备的文件操作函数集，用于处理打开、读取、写入等操作。
	struct list_head list;  // 用于将该设备插入到杂项设备列表中的链表节点。
	struct device *parent;  // 设备的父设备指针（如果有父设备），通常用于设备层级关系的组织。
	struct device *this_device;  // 指向表示该设备的内核设备结构体 `struct device`，用于表示该设备的属性。
	const struct attribute_group **groups;  // 该设备的属性组指针数组，用于 sysfs 中的设备属性配置。
	const char *nodename;  // 设备节点的名称。如果不为 NULL，设备的节点名将基于这个字段而不是 `name` 字段。
	umode_t mode;  // 设备节点的文件权限模式（如读、写权限），类似于 Unix 文件系统中的权限。
};




typedef struct task_struct *(*find_task_by_vpid_t)(pid_t pid);
typedef struct mm_struct *(*get_task_mm_t)(struct task_struct *task);
typedef void (*mmput_ptr)(struct mm_struct *mm);

find_task_by_vpid_t find_task_by_vpid_func;
get_task_mm_t get_task_mm_func;
mmput_ptr mmput_func;





// 打开设备
static int my_misc_open(struct inode *inode, struct file *file)
{
    logkd("my_misc_device: open \n");
    return 0;
}

// 释放设备
static int my_misc_release(struct inode *inode, struct file *file)
{
    logkd("my_misc_device: release\n");
    return 0;
}


long dispatch_ioctl(struct file * file, unsigned int  cmd, unsigned long  arg)
{
	
    switch (cmd)
    {
    case /* constant-expression */CMD_IOCTL :
        /* code */ 
        logkd("my_misc_device: received CMD_IOCTL_1\n");
        break;
    
    default:
        break;
    }
	
	
	return 0;
}




// 控制函数
static long syscall_hook_control0(const char *args, char *__user out_msg, int outlen) 
{


    return 0;
}

// 函数指针类型定义
typedef int (*misc_register_t)(struct miscdevice *misc);
typedef void (*misc_deregister_t)(struct miscdevice *misc);

misc_register_t misc_register_func;
misc_deregister_t misc_deregister_func;


// 设备文件操作结构体
  struct file_operations my_fops = {
    .owner = THIS_MODULE,
    .open = my_misc_open,
    .release = my_misc_release,
    .unlocked_ioctl = dispatch_ioctl,
    //.compat_ioctl = dispatch_ioctl,
};

//杂项设备结构体
 struct miscdevice my_misc_device = {
    .minor = 255,                  // 动态分配次设备号
    .name = DEVICE_NAME,          // 设备名称
    .fops = &my_fops,             // 文件操作结构体
    //.mode = 0666,                 // 设备文件权限
};








static long syscall_hook_demo_init(const char *args, const char *event, void *__user reserved)
{
   

    misc_register_func = (misc_register_t)kallsyms_lookup_name("misc_register");
    misc_deregister_func = (misc_deregister_t)kallsyms_lookup_name("misc_deregister");


    if (misc_register_func == NULL || misc_deregister_func == NULL) {
        logkd("Failed to find misc_register or misc_deregister function\n");
        return -1;
    }


    int ret;

    ret = misc_register_func(&my_misc_device);
    if (ret < 0) {
        logkd("Failed to register misc device\n");
        return ret;
    }

    logkd("my_misc_device: registered with minor number %d\n", my_misc_device.minor);

   
 

    return 0;
}

static long syscall_hook_demo_exit(void *__user reserved)
{

    misc_deregister_func(&my_misc_device);
   

    logkd("my_misc_device: deregistered\n");
    return 0;
}

KPM_INIT(syscall_hook_demo_init);
KPM_CTL0(syscall_hook_control0);
KPM_EXIT(syscall_hook_demo_exit);