#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>

static int hello_init(void){
   printk(KERN_ALERT "Hello TheLittleNaruto; it's your first driver which d    oes no shit :/\n");
   return 0;
}

static void hello_exit(void){
   printk(KERN_INFO "Goodbye TheLittleNaruto; No point in keeping this driv    er running.\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("hetal");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TheLittleNaruto's first driver with GPL licence.");
