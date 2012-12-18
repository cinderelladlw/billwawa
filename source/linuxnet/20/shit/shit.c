#include <linux/kernel.h> /* printk()在这个文件里 */
#include <linux/init.h> 
#include <linux/module.h> 

MODULE_LICENSE("Dual BSD/GPL"); 
    
static char *book_name="Dissecting Linux Device Driber"; 
static int num=4000; 

static int __init book_init(void) 
{ 
    printk(KERN_INFO"book name :%s\n",book_name); 
    printk(KERN_INFO"book num :%d\n",num); 
    return 0; 
} 

static void __exit book_exit(void) 
{ 
    printk(KERN_INFO"Book module exit\n"); 
} 

module_init(book_init); 
module_exit(book_exit); 

module_param(num,int,S_IRUGO); 
module_param(book_name,charp,S_IRUGO); 

MODULE_AUTHOR("chenbaihu"); 
MODULE_VERSION("v1.0"); 
MODULE_DESCRIPTION("A simple Module for testing module params"); 

