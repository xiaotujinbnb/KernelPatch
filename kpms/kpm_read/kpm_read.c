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

#include "kpm_read.h"

KPM_NAME("kpm_read");
KPM_VERSION(DKF_VERSION);
KPM_LICENSE("GPL v2");
KPM_AUTHOR("tuzi");
KPM_DESCRIPTION("kpm_read");

#define GET_MAJOR(version) (((version) >> 16) & 0xFF)
#define GET_MINOR(version) (((version) >> 8) & 0xFF)
#define GET_PATCH(version) ((version) & 0xFF)
#define bits(n, high, low) (((n) << (63u - (high))) >> (63u - (high) + (low)))




// 控制函数
static long kpm_read_control0(const char *args, char *__user out_msg, int outlen)
{


    return 0;
}

static long kpm_read_init(const char *args, const char *event, void *__user reserved)
{

    return 0;
}

static long kpm_read_exit(void *__user reserved)
{

    return 0;
}

KPM_INIT(kpm_read_init);
KPM_CTL0(kpm_read_control0);
KPM_EXIT(kpm_read_exit);