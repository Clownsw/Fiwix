/*
 * fiwix/include/fiwix/mm.h
 *
 * Copyright 2018-2022, Jordi Sanfeliu. All rights reserved.
 * Distributed under the terms of the Fiwix License.
 */

#ifndef _FIWIX_MEMORY_H
#define _FIWIX_MEMORY_H

#include <fiwix/types.h>
#include <fiwix/segments.h>
#include <fiwix/process.h>

/*
 * Convert only from physical to virtual the addresses below PAGE_OFFSET
 * (formerly 0xC0000000).
 */
#define P2V(addr)		(addr < PAGE_OFFSET ? addr + PAGE_OFFSET : addr)

#define V2P(addr)		(addr - PAGE_OFFSET)

#define PAGE_SIZE		4096
#define PAGE_SHIFT		0x0C
#define PAGE_MASK		~(PAGE_SIZE - 1)	/* 0xFFFFF000 */
#define PAGE_ALIGN(addr)	(((addr) + (PAGE_SIZE - 1)) & PAGE_MASK)
#define PT_ENTRIES		(PAGE_SIZE / sizeof(unsigned int))
#define PD_ENTRIES		(PAGE_SIZE / sizeof(unsigned int))

#define PAGE_PRESENT		0x001	/* Present */
#define PAGE_RW			0x002	/* Read/Write */
#define PAGE_USER		0x004	/* User */

#define PAGE_LOCKED		0x001
#define PAGE_RESERVED		0x100	/* kernel, BIOS address, ... */
#define PAGE_COW		0x200	/* marked for Copy-On-Write */

#define PFAULT_V		0x01	/* protection violation */
#define PFAULT_W		0x02	/* during write */
#define PFAULT_U		0x04	/* in user mode */

#define GET_PGDIR(address)	((unsigned int)((address) >> 22) & 0x3FF)
#define GET_PGTBL(address)	((unsigned int)((address) >> 12) & 0x3FF)

struct page {
	int page;		/* page number */
	int count;		/* usage counter */
	int flags;
	__ino_t inode;		/* inode of the file */
	__off_t offset;		/* file offset */
	__dev_t dev;		/* device where file resides */
	char *data;		/* page contents */
	struct page *prev_hash;
	struct page *next_hash;
	struct page *prev_free;
	struct page *next_free;
};

extern struct page *page_table;
extern struct page **page_hash_table;

/* values to be determined during system startup */
extern unsigned int page_table_size;		/* size in bytes */
extern unsigned int page_hash_table_size;	/* size in bytes */

extern unsigned int *kpage_dir;

/* buddy_low.c */
unsigned int kmalloc2(__size_t);
void kfree2(unsigned int);
void buddy_low_init(void);

/* alloc.c */
unsigned int kmalloc(void);
void kfree(unsigned int);

/* page.c */
void page_lock(struct page *);
void page_unlock(struct page *);
struct page *get_free_page(void);
struct page *search_page_hash(struct inode *, __off_t);
void release_page(int);
int is_valid_page(int);
void update_page_cache(struct inode *, __off_t, const char *, int);
int write_page(struct page *, struct inode *, __off_t, unsigned int);
int bread_page(struct page *, struct inode *, __off_t, char, char);
int file_read(struct inode *, struct fd *, char *, __size_t);
void page_init(int);

/* memory.c */
unsigned int map_kaddr(unsigned int, unsigned int, unsigned int, int);
void bss_init(void);
unsigned int setup_minmem(void);
unsigned int get_mapped_addr(struct proc *, unsigned int);
int clone_pages(struct proc *);
int free_page_tables(struct proc *);
unsigned int map_page(struct proc *, unsigned int, unsigned int, unsigned int);
int unmap_page(unsigned int);
void mem_init(void);
void mem_stats(void);

/* swapper.c */
int kswapd(void);

#endif /* _FIWIX_MEMORY_H */
