#ifndef LINUX_PERFORMANCESTAT_H
#define LINUX_PERFORMANCESTAT_H

#include <linux/types.h>
#include <linux/ioctl.h>

#define FRAME_SYNC _IOW('p', 7, int)
#define AUDIO_SYNC _IOW('p', 8, int)
#define THREAD_ACCELERATE _IOW('p', 9, int)

#endif