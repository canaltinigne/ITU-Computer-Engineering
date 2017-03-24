#ifndef __CLUMSY_H
#define __CLUMSY_H

#include <linux/ioctl.h> /* needed for the _IOW etc stuff used later */

#define CLUMSY_IOC_MAGIC  'k'

#define CLUMSY_SET_RANDOM_MODE    _IOW(CLUMSY_IOC_MAGIC, 0,int)
#define CLUMSY_SET_REGULAR_MODE    _IOW(CLUMSY_IOC_MAGIC, 1,int)

#define CLUMSY_IOC_MAXNR 1

#endif /* clumsy_h */
