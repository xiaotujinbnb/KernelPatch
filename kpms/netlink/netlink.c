/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright (C) 2024 bmax121. All Rights Reserved.
 */

/*   SPDX-License-Identifier: GPL-3.0-only   */
/*
 * Copyright (C) 2024 Nep-Timeline. All Rights Reserved.
 * Copyright (C) 2024 lzghzr. All Rights Reserved.
 */
#include <compiler.h>
#include <hook.h>
#include <kpmodule.h>
#include <kputils.h>
#include <taskext.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/printk.h>
#include <linux/string.h>
#include <asm/atomic.h>

#ifdef CONFIG_DEBUG
#include <uapi/linux/limits.h>
#endif /* CONFIG_DEBUG */

#include "netlink.h"
#include "nt_utils.h"

KPM_NAME("re_kernel");
KPM_VERSION("6.0.10");
KPM_LICENSE("GPL v3");
KPM_AUTHOR("Nep-Timeline, lzghzr");
KPM_DESCRIPTION("Re:Kernel, support 4.4 ~ 6.1");

#define NETLINK_REKERNEL_MAX 26
#define NETLINK_REKERNEL_MIN 22



#define UZERO (1UL << 0x20)


// start_rekernel_server
static struct net kvar_def(init_net);
struct sock* kfunc_def(__netlink_kernel_create)(struct net* net, int unit, struct module* module, struct netlink_kernel_cfg* cfg);




// 创建 netlink 服务
static struct sock* rekernel_netlink;
static unsigned long rekernel_netlink_unit = UZERO;

static int start_rekernel_server(void) {
  if (rekernel_netlink_unit != UZERO) {
    return 0;
  }
  struct netlink_kernel_cfg rekernel_cfg = {};



    rekernel_netlink = netlink_kernel_create(kvar(init_net), rekernel_netlink_unit, &rekernel_cfg);
 
  

  return 0;
}
// 发送 netlink 消息




static long inline_hook_control0(const char* ctl_args, char* __user out_msg, int outlen) {
  char msg[64];
  snprintf(msg, sizeof(msg), "_(._.)_");
  compat_copy_to_user(out_msg, msg, sizeof(msg));
  return 0;
}





static long inline_hook_init(const char* args, const char* event, void* __user reserved) {



  kvar_lookup_name(init_net);
  kfunc_lookup_name(__netlink_kernel_create);
  

  return 0;
}

static long inline_hook_exit(void* __user reserved) {
 


  return 0;
}

KPM_INIT(inline_hook_init);
KPM_CTL0(inline_hook_control0);
KPM_EXIT(inline_hook_exit);
