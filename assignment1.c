#include <linux/module.h>
#include<linux/netlink.h>
#include<net/sock.h>

static struct sock *nl_socket = NULL;
static struct nlmsghdr *nlmsghdr_sachin;

#define NETLINK_TEST 31

static void netlink_recv_msg_fn(struct sk_buff *skb_in){
	printk(KERN_INFO" userspace message received");
}

static struct netlink_kernel_cfg cfg = {
	.input = netlink_recv_msg_fn,
};

static void nlmsg_dump(struct nlmsghdr *nlh){

	printk(KERN_INFO " nlmsg_dump : nlmsg_len nlmsg_type " \
			"nlmsg_flags  nlmsg_seq nlmsg_pid ");

}
static int __init sachin_init(void){

	printk(KERN_INFO "sachin_init inserted");

	nlmsg_dump(nlmsghdr_sachin);

	nl_socket = netlink_kernel_create(&init_net, NETLINK_TEST, &cfg);

	if(!nl_socket){
		printk(KERN_ERR "kernel socket not created");
		return -ENOMEM;
	}

	printk(KERN_INFO " Netlink socket created");

	return 0;
}

static void __exit sachin_close(void){
	printk(KERN_INFO" sachin_close module removed");
	netlink_kernel_release(nl_socket);
	nl_socket = NULL;
}


module_init(sachin_init);
module_exit(sachin_close);

MODULE_AUTHOR("Sachin");
MODULE_DESCRIPTION("Udemy netlink assignment");
MODULE_LICENSE("GPL");
