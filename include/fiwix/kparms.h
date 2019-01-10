/*
 * fiwix/include/fiwix/kparms.h
 *
 * Copyright 2018, Jordi Sanfeliu. All rights reserved.
 * Distributed under the terms of the Fiwix License.
 */

#ifndef _FIWIX_KPARMS_H
#define _FIWIX_KPARMS_H

#define CMDL_ARG_LEN	25	/* max length of cmdline argument */
#define CMDL_NUM_VALUES	30	/* max values of cmdline parameter */

struct kparms {
	char *name;
	char *value[CMDL_NUM_VALUES];
	unsigned int sysval[CMDL_NUM_VALUES];
};

static struct kparms parm_table[] = {
	{ "root=",
	   { "/dev/ram0", "/dev/fd0", "/dev/fd1",
	     "/dev/hda", "/dev/hda1", "/dev/hda2", "/dev/hda3", "/dev/hda4",
	     "/dev/hdb", "/dev/hdb1", "/dev/hdb2", "/dev/hdb3", "/dev/hdb4",
	     "/dev/hdc", "/dev/hdc1", "/dev/hdc2", "/dev/hdc3", "/dev/hdc4",
	     "/dev/hdd", "/dev/hdd1", "/dev/hdd2", "/dev/hdd3", "/dev/hdd4",
	   },
	   { 0x100, 0x200, 0x201,
	     0x300, 0x301, 0x302, 0x303, 0x304,
	     0x340, 0x341, 0x342, 0x343, 0x344,
	     0x1600, 0x1601, 0x1602, 0x1603, 0x1604,
	     0x1640, 0x1641, 0x1642, 0x1643, 0x1644,
	   }
	},
	{ "noramdisk",
	   { NULL },
	   { NULL },
	},
	{ "ramdisksize=",
	   { NULL },
	   { NULL },
	},
	{ "initrd=",
	   { NULL },
	   { NULL },
	},
	{ "rootfstype=",
	   { "minix", "ext2", "iso9660" },
	   { 0, 0 }
	},
	{ "console=",
	   { "/dev/tty1", "/dev/tty2", "/dev/tty3", "/dev/tty4", "/dev/tty5",
	     "/dev/tty6", "/dev/tty7", "/dev/tty8", "/dev/tty9", "/dev/tty10",
	     "/dev/tty11", "/dev/tty12"
	   },
	   { 0x401, 0x402, 0x403, 0x404, 0x405,
	     0x406, 0x407, 0x408, 0x409, 0x410,
	     0x411, 0x412
	   }
	},

	{ NULL }
};

#endif /* _FIWIX_KPARMS_H */
