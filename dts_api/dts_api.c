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
#include <linux/of_device.h>

#include <linux/platform_device.h>	//platform总线头文件



static int dts_probe(struct platform_device *pdev)
{
	struct resource *io, *irq;
	struct device *dev = &pdev->dev;
	struct device_node *node = dev->of_node;		//设备树节点
	/*自定义节点变量*/
	const char *my_string;
	u32 my_num = -1;
	u8 my_array_u8[5] = {0};
	u16 my_array_u16[5] = {0};
	int temp = 0;

	/*子节点变量*/
	struct fwnode_handle *child;
	int child_node_count = -1;
	const char *child_string;
	
	//int ret = -1;
	
	printk("[%s]-[%d] start\n",__func__,__LINE__);

	/*#######################获取MEM资源########################################*/		
	io =  platform_get_resource(pdev, IORESOURCE_MEM, 0);	//获取dts中，reg = <0x11112222 0x1000>; 
															//如果是arm64,那么reg<0x10 0x11112222 0x00 0x1000>代表：start:0x1011112222，size:0x1000
	if( io != NULL){
		printk("io->name:[%s] \n", io->name);
		printk("io->start:[0x%x] io->end:[0x%x]\n", io->start, io->end);
		printk("io size:[0x%x] \n", resource_size(io));		//使用resource_size获取资源的长度：0x1000

		//p->base = devm_ioremap_nocache(dev, io->start, resource_size(io)); //正常获取到资源后都用于申请内存，或内存映射
	}else{
		printk("[%s]-[%d] Not found IORESOURCE_MEM resource\n",__func__,__LINE__);
	}	
	
	io =  platform_get_resource(pdev, IORESOURCE_MEM, 1);	//获取dts中，reg = <0x11112222 0x1000>; 
	if( io != NULL){
		printk("io->start:[0x%x] io->end:[0x%x]\n", io->start, io->end);
		printk("io size:[0x%x] \n", resource_size(io));	
	}else{
		printk("[%s]-[%d] Not found IORESOURCE_MEM resource\n",__func__,__LINE__);
	}																

	

	/*########################获取IRQ资源#######################################*/		
	irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if(irq != NULL){
		printk("irq->name:[%s] \n", io->name);
		printk("irq->start:[0x%x] irq->end:[0x%x]\n", irq->start, irq->end);
	}else{
		printk("[%s]-[%d] Not found IORESOURCE_IRQ resource\n",__func__,__LINE__);
	}	


	/*########################获取string资源#######################################*/		
	if (of_property_read_string(node, "my_string", &my_string) == 0 ){
		printk("my_string:[%s] \n", my_string);
	}else{
		printk("[%s]-[%d] Not found 'my_string' resource\n",__func__,__LINE__);
	}
		

	/*########################获取int资源#######################################*/		
	if (of_property_read_u32(node, "my_num", &my_num) == 0 ){
		printk("my_num:[%d] \n", my_num);
		temp = my_num;
	}else{
		printk("[%s]-[%d] Not found 'my_num' resource\n",__func__,__LINE__);
	}
		

	/*########################获取array资源#######################################*/			
	if (of_property_read_u8_array(node, "my_array_u8", my_array_u8, my_num) == 0 ){
		for(;temp > 0; temp--){
			printk("my_array_u8[%d]:[0x%x] \n", temp-1, my_array_u8[temp-1]);
		}		
	}else{
		printk("[%s]-[%d] Not found 'my_array_u8' resource\n",__func__,__LINE__);
	}

	if (of_property_read_u16_array(node, "my_array_u16", my_array_u16, my_num) == 0 ){
		temp = my_num;
		for(;temp > 0; temp--){
			printk("my_array_u16[%d]:[0x%x] \n", temp-1, my_array_u16[temp-1]);
		}		
	}else{
		printk("[%s]-[%d] Not found 'my_array_u16' resource\n",__func__,__LINE__);
	}

	/*#######################获取子节点个数########################################*/		
	child_node_count = device_get_child_node_count(dev);
	printk("child_node_count:[%d] \n", child_node_count);
	/*遍历子节点数据*/
	device_for_each_child_node(dev, child) {
		if(fwnode_property_read_string(child, "m_string", &child_string) ==0 ){
			printk("m_string[%s]\n", child_string);
		}else{
			printk("[%s]-[%d] Not found 'my_array_u16' resource\n",__func__,__LINE__);
		}		
	}
	
	printk("[%s]-[%d] end\n",__func__,__LINE__);


		
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

