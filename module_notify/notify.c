/*
 *建立通知链
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/export.h>
#include <linux/notifier.h>
#include <linux/sched.h>
#include <linux/types.h>

#include "buildchain.h"

static int __init start_notify_init(void)
{
	int ret = 0;
	printk("[%s]-[%d]\n",__func__,__LINE__);

	printk("Begin to notify:\n");

	/*
	* 调用自定义的函数，向test_chain链发送消息
	*/
	printk("==============================\n");
	ret = test_notifier_call_chain(1, "hello");
	printk("==============================\n");
	if (ret)
	      printk("notifier_call_chain error\n");

	return ret;
}

static void __exit start_notify_exit(void)
{
	printk("[%s]-[%d]\n",__func__,__LINE__);
}


module_init(start_notify_init);
module_exit(start_notify_exit);

MODULE_DESCRIPTION("build notify test driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Luyj595");
