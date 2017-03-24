#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

#include <linux/kernel.h>	/* printk() */
#include <linux/slab.h>		/* kmalloc() */
#include <linux/fs.h>		/* everything... */
#include <linux/errno.h>	/* error codes */
#include <linux/types.h>	/* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h>	/* O_ACCMODE */
#include <linux/seq_file.h>
#include <linux/cdev.h>
#include <linux/random.h>   /* get random bytes */

#include <asm/switch_to.h>		/* cli(), *_flags */
#include <asm/uaccess.h>	/* copy_*_user */

#include "clumsy.h"

#define CLUMSY_MAJOR 0
#define CLUMSY_NR_DEVS 1
#define DATA_STORAGE_CAPACITY 4000

int clumsy_major = CLUMSY_MAJOR;
int clumsy_minor = 0;
int clumsy_nr_devs = CLUMSY_NR_DEVS;
int storage_capacity = DATA_STORAGE_CAPACITY;

module_param(clumsy_major, int, S_IRUGO);
module_param(clumsy_minor, int, S_IRUGO);
module_param(clumsy_nr_devs, int, S_IRUGO);
module_param(storage_capacity, int, S_IRUGO);

MODULE_AUTHOR("Ozan Ata, Can Yilmaz Altinigne");
MODULE_LICENSE("Dual BSD/GPL");


struct clumsy_dev {
    char *data;
    unsigned long storage_capacity;
    int regularOrRandom;
    int dropped_char_index;
    long int new_index;
    struct semaphore sem;
    struct cdev cdev;
};

struct clumsy_dev *clumsy_device;

int clumsy_trim(struct clumsy_dev *dev)
{
    kfree(dev->data);
    dev->data = NULL;
    dev->storage_capacity = 0;
    dev->new_index = 0;
    printk(KERN_INFO "clumsy: trim function\n");

    return 0;
}

int clumsy_open(struct inode *inode, struct file *filp)
{
    struct clumsy_dev *dev;

    dev = container_of(inode->i_cdev, struct clumsy_dev, cdev);
    filp->private_data = dev;

    printk(KERN_INFO "clumsy: open function\n");

    return 0;
}

int clumsy_release(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "clumsy: close function\n");
    return 0;
}

ssize_t clumsy_read(struct file *filp, char __user *buf, size_t count,
                   loff_t *f_pos)
{
    struct clumsy_dev *dev = filp->private_data;
    int clumsy_pos;
    long i = count;
    long int tmp2 = 0;
    long int tmp3 = 0;
    int storage = dev->storage_capacity;
    ssize_t retval = 0;
    printk(KERN_INFO "clumsy: read function\n");
    printk(KERN_INFO "clumsy: read file position:%ld\n", (long)*f_pos);

    if (down_interruptible(&dev->sem)){
        printk(KERN_INFO "clumsy: 1 function\n");
        return -ERESTARTSYS;
    }

    if (*f_pos <= 0)
        goto out;


    if (count > dev->storage_capacity)
        count = dev->storage_capacity;

    clumsy_pos = 0;

    if (dev->data == NULL){
        printk(KERN_INFO "clumsy: 3 function\n");
        goto out;
    }

    /* read only up to the end of this quantum */
    if (count > storage - clumsy_pos)
        count = storage - clumsy_pos;

        printk(KERN_INFO "clumsy_pos:%d  count: %d\n", clumsy_pos, count);


    if ( dev->regularOrRandom == 1 ){
        int k = 0;
        int n_times;
        get_random_bytes(&n_times, sizeof(n_times));
        for( k = 0; k < n_times % (count+1); k++){
            int j;
            get_random_bytes(&j, sizeof(j));
            j = j % (count+1);
            *(dev->data+j) = ' ';
        }
    } else if ( dev->regularOrRandom == 0 ){
        int k = 0;
        while (k < count){
            if ( k % dev->dropped_char_index == 0)
                *(dev->data+k) = ' ';
            k++;
        }
    }

    if (copy_to_user(buf, dev->data, count)) {
        retval = -EFAULT;
        goto out;
    }

    i = count;

    if(*(dev->data + count) != 0){

        for(tmp2 = count; tmp2 < *f_pos; tmp2++){
            *(dev->data + tmp3) = *(dev->data + tmp2);
            tmp3++;
        }

    }

    *f_pos -= count;

    memset(dev->data + *f_pos, 0, (storage - *f_pos) * sizeof(char));

    retval = count;


  out:
    up(&dev->sem);
    return retval;
}

ssize_t clumsy_write(struct file *filp, const char __user *buf, size_t count,
                    loff_t *f_pos)
{
    struct clumsy_dev *dev = filp->private_data;
    int storage = dev->storage_capacity;
    ssize_t retval = -ENOMEM;
    int clumsy_pos;
    printk(KERN_INFO "clumsy: write function\n");

    if (down_interruptible(&dev->sem))
        return -ERESTARTSYS;

    if (*f_pos >= storage) {
        retval = 0;
        printk(KERN_INFO "clumsy: not enough space\n");
        goto out;
    }

    clumsy_pos = (long) *f_pos;

    if (!dev->data) {
        dev->data = kmalloc(storage * sizeof(char), GFP_KERNEL);
        if (!dev->data)
            goto out;
        memset(dev->data, 0, storage * sizeof(char));
    }

    printk(KERN_INFO "clumsy: write file position:%d\n", (int)*f_pos);

    /* write only up to the end of this quantum */
    if (count > storage - clumsy_pos)
        count = storage - clumsy_pos;



    if (copy_from_user(dev->data + clumsy_pos, buf, count)) {
        retval = -EFAULT;
        goto out;
    }

    *f_pos += count;
    printk(KERN_INFO "clumsy: write file position increased:%ld\n", (long)*f_pos);
    retval = count;

    if (dev->storage_capacity < *f_pos)
        dev->storage_capacity = *f_pos;

out:
    up(&dev->sem);
    return retval;
}

long clumsy_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{

    struct clumsy_dev *dev = filp->private_data;

	int err = 0;
	int retval = 0;

	/*
	 * extract the type and number bitfields, and don't decode
	 * wrong cmds: return ENOTTY (inappropriate ioctl) before access_ok()
	 */
	if (_IOC_TYPE(cmd) != CLUMSY_IOC_MAGIC) return -ENOTTY;
	if (_IOC_NR(cmd) > CLUMSY_IOC_MAXNR) return -ENOTTY;

	/*
	 * the direction is a bitmask, and VERIFY_WRITE catches R/W
	 * transfers. `Type' is user-oriented, while
	 * access_ok is kernel-oriented, so the concept of "read" and
	 * "write" is reversed
	 */
	if (_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		err =  !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
	if (err) return -EFAULT;

	switch(cmd) {
	  case CLUMSY_SET_RANDOM_MODE:
		dev->regularOrRandom = 1;
		break;

	  case CLUMSY_SET_REGULAR_MODE: /* Set: arg points to the value */
		dev->regularOrRandom = 0;
		dev->dropped_char_index = (int)arg;
		break;

	  default:  /* redundant, as cmd was checked against MAXNR */
		return -ENOTTY;
	}
	return retval;
}

loff_t clumsy_llseek(struct file *filp, loff_t off, int whence)
{
    return -EPERM;
}

struct file_operations clumsy_fops = {
    .owner =    THIS_MODULE,
    .read =     clumsy_read,
    .unlocked_ioctl = clumsy_ioctl,
    .open =     clumsy_open,
    .release =  clumsy_release,
    .write = clumsy_write,
    .llseek = clumsy_llseek
};


void clumsy_cleanup_module(void){

    dev_t devno = MKDEV(clumsy_major, clumsy_minor);

    if (clumsy_device) {
        clumsy_trim(clumsy_device);
        cdev_del(&clumsy_device[0].cdev);
        kfree(clumsy_device);
    }

    unregister_chrdev_region(devno, 1);
}

int clumsy_init_module(void){

    int result;
    int err;
    dev_t devno = 0;
    struct clumsy_dev *dev;

    if (clumsy_major) {
        devno = MKDEV(clumsy_major, clumsy_minor);
        result = register_chrdev_region(devno, 1, "clumsy");
    } else {
        result = alloc_chrdev_region(&devno, clumsy_minor, 1, "clumsy");
        clumsy_major = MAJOR(devno);
    }

    if (result < 0) {
        printk(KERN_WARNING "clumsy: can't get major %d\n", clumsy_major);
        return result;
    }

    printk(KERN_INFO "clumsy: major number = %d\n", clumsy_major);

    clumsy_device = kmalloc(sizeof(struct clumsy_dev), GFP_KERNEL);

    if(!clumsy_device){
        result = -ENOMEM;
        goto fail;
    }

    memset(clumsy_device, 0, sizeof(struct clumsy_dev));

    dev = clumsy_device;
    dev->storage_capacity = storage_capacity;
    dev->new_index = 0;
    sema_init(&dev->sem,1);
    devno = MKDEV(clumsy_major, clumsy_minor);
    cdev_init(&dev->cdev, &clumsy_fops);
    dev->cdev.owner = THIS_MODULE;
    dev->cdev.ops = &clumsy_fops;

    err = cdev_add(&dev->cdev, devno, 1);

    if (err)
        printk(KERN_NOTICE "Error %d adding clumsy%d", err, 0);

    return 0; /* succeed */

fail:
    clumsy_cleanup_module();
    return result;
}

module_init(clumsy_init_module);
module_exit(clumsy_cleanup_module);
