#include <linux/netlink.h>
#include <linux/skbuff.h>
#include <linux/net.h>              // 用于网络结构
#include <linux/socket.h>           // 用于套接字操作
#include <net/net_namespace.h>      // 用于网络命名空间
#include <net/netlink.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>


#define NETLINK_MY_MODULE 30
#define USER_PORT 1

static struct sock *netlink_sock = NULL;

static int send_netlink_message(char *msg, uint16_t len) {
    struct sk_buff *skbuffer;
    struct nlmsghdr *nlhdr;

    skbuffer = nlmsg_new(len, GFP_ATOMIC);
    if (!skbuffer) {
        printk(KERN_ERR "netlink alloc failure.\n");
        return -1;
    }

    nlhdr = nlmsg_put(skbuffer, 0, 0, NLMSG_DONE, len, 0);
    if (!nlhdr) {
        printk(KERN_ERR "nlmsg_put failure.\n");
        nlmsg_free(skbuffer);
        return -1;
    }

    memcpy(nlmsg_data(nlhdr), msg, len);
    return netlink_unicast(netlink_sock, skbuffer, USER_PORT, MSG_DONTWAIT);
}

static int __init my_module_init(void) {
    struct netlink_kernel_cfg cfg = {
        .input = NULL,
    };

    netlink_sock = netlink_kernel_create(&init_net, NETLINK_MY_MODULE, &cfg);
    if (!netlink_sock) {
        printk(KERN_ERR "Failed to create netlink socket.\n");
        return -1;
    }

    printk(KERN_INFO "Netlink socket created.\n");
    return 0;
}

static void __exit my_module_exit(void) {
    netlink_kernel_release(netlink_sock);
    printk(KERN_INFO "Netlink socket released.\n");
}

module_init(my_module_init);
module_exit(my_module_exit);
MODULE_AUTHOR("Linux");
MODULE_DESCRIPTION("Linux default module");
MODULE_LICENSE("GPL");
