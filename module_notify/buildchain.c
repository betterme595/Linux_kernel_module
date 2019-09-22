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

/*
* RAW_NOTIFIER_HEAD是定义一个通知链的头部结点，
* 通过这个头部结点可以找到这个链中的其它所有的notifier_block
*/
static RAW_NOTIFIER_HEAD(test_chain);	


/*
* 自定义的注册函数，将notifier_block节点加到刚刚定义的test_chain这个链表中来
* raw_notifier_chain_register会调用notifier_chain_register
*/
int register_test_notifier(struct notifier_block *nb)
{
  return raw_notifier_chain_register(&test_chain, nb);
}
EXPORT_SYMBOL(register_test_notifier);

int unregister_test_notifier(struct notifier_block *nb)
{
  return raw_notifier_chain_unregister(&test_chain, nb);
}
EXPORT_SYMBOL(unregister_test_notifier);

/*
* 自定义的通知链表的函数，即通知test_chain指向的链表中的所有节点执行相应的函数
*/
int test_notifier_call_chain(unsigned long val, void *v)
{
  return raw_notifier_call_chain(&test_chain, val, v);
}
EXPORT_SYMBOL(test_notifier_call_chain);


static int __init build_notify_init(void)
{
	int ret = 0;
	printk("[%s]-[%d]\n",__func__,__LINE__);
	return ret;
}

static void __exit build_notify_exit(void)
{
	printk("[%s]-[%d]\n",__func__,__LINE__);
}


module_init(build_notify_init);
module_exit(build_notify_exit);

MODULE_DESCRIPTION("build notify test driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Luyj595");
