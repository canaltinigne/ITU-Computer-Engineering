/*
    FUSE: Filesystem in Userspace
    Copyright (C) 2001-2005  Miklos Szeredi <miklos@szeredi.hu>

    This program can be distributed under the terms of the GNU GPL.
    See the file COPYING.
*/

#define FUSE_USE_VERSION 26

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/xattr.h>
#include <dirent.h>
#include <unistd.h>
#include <fuse.h>
#include <gdbm.h>

GDBM_FILE file_database;

static int hello_getattr(const char *path, struct stat *stbuf){

    int res = 0;

    memset(stbuf, 0, sizeof(struct stat));

    if(strcmp(path, "/") == 0){
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
    } else {

        datum key;
        key.dptr = (char *) path;
        key.dsize = strlen(path) + 1;

        datum val = gdbm_fetch(file_database, key);

        if(val.dptr == NULL){
            return -ENOENT;
        } else {
            stbuf->st_mode = S_IFREG | 0444;
            stbuf->st_nlink = 1;
            stbuf->st_size = strlen(val.dptr)+1;
            return 0;
        }
    }

    return 0;
}

static int hello_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi){

    (void) offset;
    (void) fi;

    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);

    datum key = gdbm_firstkey(file_database);

    while(key.dptr != NULL){
        key.dptr[key.dsize-1] = '\0';
        int rc = filler(buf, key.dptr+1, NULL, 0);
        datum nextkey = gdbm_nextkey(file_database, key);
        key = nextkey;
    }

    return 0;
}

static int hello_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi){

    size_t len;
    (void) fi;

    datum key;
    key.dptr = (char*)path;
    key.dsize = strlen(path)+1;
    datum val = gdbm_fetch(file_database, key);

    if (!val.dptr)
        return -ENOENT;

    len = strlen(val.dptr)+1;
    if (offset < len) {
        if (offset + size > len)
            size = len - offset;
        memcpy(buf, val.dptr + offset, size);
    } else
        size = 0;

    return size;
}

static int hello_mknod(const char *path, mode_t mode, dev_t dev){

    datum key;
    key.dptr = malloc(sizeof(char)*(strlen(path)+1));
    strcpy(key.dptr, path);
    key.dsize = strlen(key.dptr)+1;

    datum val = { .dptr = "", .dsize = 2 };

    int rc = gdbm_store(file_database, key, val, GDBM_INSERT);

    if(rc == 0){
        printf("\ngdbm_store successful");
        return 0;
    } else if(rc == 1){
        printf("\ngdbm_store already exists");
        return 0;
    } else {
        printf("\ngdbm_store returned error");
        return -EIO;
    }
}

static int hello_fsync(const char *path, int dataonly, struct fuse_file_info *fi){
    return 0;
}

static int hello_open(const char *path, struct fuse_file_info *fi){
    datum key;
    key.dptr = malloc(sizeof(char)*(strlen(path)+1));
    strcpy(key.dptr, path);
    key.dsize = strlen(key.dptr)+1;

    datum val = gdbm_fetch(file_database, key);
    free(key.dptr);

    if(val.dptr == NULL){
        return -ENOENT;
    }

    return 0;
}

static int hello_write(const char *path, const char *srcbuf, size_t cnt, off_t offset, struct fuse_file_info *fi){
    datum key;
    key.dptr = malloc(sizeof(char)*(strlen(path)+1));
    strcpy(key.dptr, path);
    key.dsize = strlen(key.dptr)+1;

    datum val = gdbm_fetch(file_database, key);
    val.dptr = malloc((strlen(srcbuf)+1)*sizeof(char));
    strcpy(val.dptr, srcbuf);
    val.dsize = strlen(val.dptr)+1;

    gdbm_store(file_database, key, val, GDBM_REPLACE);

    free(key.dptr);
    free(val.dptr);

    return val.dsize-1;
}

static int hello_unlink(const char *path)
{
    datum key;
    key.dptr = (char*)path;
    key.dsize = strlen(path)+1;

    int rc = gdbm_delete(file_database, key);

    if(rc == -1){
        return -ENOENT;
    } else {
        return 0;
    }
}

static struct fuse_operations hello_oper = {
    .getattr	= hello_getattr,
    .readdir	= hello_readdir,
    .open	= hello_open,
    .read	= hello_read,
    .mknod = hello_mknod,
    .fsync = hello_fsync,
    .unlink = hello_unlink,
    .write = hello_write,
    .open = hello_open
};

int main(int argc, char *argv[])
{
    file_database = gdbm_open("gdbmfs.db", 0, GDBM_WRCREAT, S_IRUSR|S_IWUSR, NULL);

    if(file_database == NULL){
        fprintf(stderr, "Error: database not opened");
        return -1;
    }

    fuse_main(argc, argv, &hello_oper, NULL);

    gdbm_close(file_database);

    return 0;
}
