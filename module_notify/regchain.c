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

/*
* 注册通知链
*/
extern int register_test_notifier(struct notifier_block*);
extern int unregister_test_notifier(struct notifier_block*);

static int test_event1(struct notifier_block *this, unsigned long event, void *ptr)
{
  printk("In Event 1: Event Number is [%ld], ptr:[%s]\n", event, ptr);
  return 0;
}

static int test_event2(struct notifier_block *this, unsigned long event, void *ptr)
{
  printk("In Event 2: Event Number is [%ld], ptr:[%s]\n", event, ptr);
  return 0;
}

static int test_event3(struct notifier_block *this, unsigned long event, void *ptr)
{
  printk("In Event 2: Event Number is [%ld], ptr:[%s]\n", event, ptr);
  return 0;
}

/*
* 事件1，该节点执行的函数为test_event1
*/
static struct notifier_block test_notifier1 =
{
    .notifier_call = test_event1,
};

/*
* 事件2，该节点执行的函数为test_event2
*/
static struct notifier_block test_notifier2 =
{
    .notifier_call = test_event2,
};

/*
* 事件3，该节点执行的函数为test_event2
*/
static struct notifier_block test_notifier3 =
{
    .notifier_call = test_event3,
};


/*
* 对这些事件进行注册
*/
static int __init reg_notify_init(void)
{
	int err = 0;
	printk("[%s]-[%d]\n",__func__,__LINE__);
	printk("Begin to register:\n");

	err = register_test_notifier(&test_notifier1);
	if (err){
		printk("register test_notifier1 error\n");
		return -1;
	}
	printk("register test_notifier1 completed\n");

	err = register_test_notifier(&test_notifier2);
	if (err){
		printk("register test_notifier2 error\n");
		return -1;
	}
	printk("register test_notifier2 completed\n");

	err = register_test_notifier(&test_notifier3);
	if (err){
		printk("register test_notifier3 error\n");
		return -1;
	}
	printk("register test_notifier3 completed\n");

	return err;
}

static void __exit reg_notify_exit(void)
{
	printk("[%s]-[%d]\n",__func__,__LINE__);
	printk("Begin to unregister\n");
	unregister_test_notifier(&test_notifier1);
	unregister_test_notifier(&test_notifier2);
	unregister_test_notifier(&test_notifier3);
	printk("Unregister finished\n");
}


module_init(reg_notify_init);
module_exit(reg_notify_exit);

MODULE_DESCRIPTION("notify test driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Luyj595");
