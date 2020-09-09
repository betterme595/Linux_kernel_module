/*
 *设备树接口使用
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/export.h>
#include <linux/notifier.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/of.h>				//设备树头文件
#include <linux/platform_device.h>	//platform总线头文件



static int dts_probe(struct platform_device *pdev)
{
	printk("[%s]-[%d]\n",__func__,__LINE__);
	return 0;
}

static int dts_remove(struct platform_device *pdev)
{
	printk("[%s]-[%d]\n",__func__,__LINE__);
	return 0;

}


/*使用设备树匹配*/
static const struct of_device_id rcar_dmac_of_ids[] = {
	{ .compatible = "zynq7010,dts-test", },
	{ /* Sentinel */ }
};
MODULE_DEVICE_TABLE(of, rcar_dmac_of_ids);


/*注册platform驱动*/
static struct platform_driver dts_driver = {
	.driver		= {
		.name	= "dts-test",
		.of_match_table = rcar_dmac_of_ids,
	},
	.probe		= dts_probe,
	.remove		= dts_remove,
};
		

static int __init dts_init(void)
{
	int ret = 0;
	printk("[%s]-[%d]\n",__func__,__LINE__);
	ret = platform_driver_register(&dts_driver);
	
	return ret;
}

static void __exit dts_exit(void)
{
	printk("[%s]-[%d]\n",__func__,__LINE__);
	platform_driver_unregister(&dts_driver);
}


module_init(dts_init);
module_exit(dts_exit);

MODULE_DESCRIPTION("dts api test driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Luyj595");

