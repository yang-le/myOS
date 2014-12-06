#! /bin/sh

IMG_SIZE=`wc -c < $2`
NUM=`expr $IMG_SIZE / 1024 + 1`
dd if=$2 		of=$1 bs=1k 			count=$NUM
dd if=/dev/zero of=$1 bs=1k seek=$NUM 	count=`expr 1440 - $NUM`
