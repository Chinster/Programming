#!/bin/sh

if [ $# -lt 2 ]; then
    echo "./chroot-import [CHROOT-DIR] [BIN]...";
    exit;
fi

cd $1;
for bin in "${@:2}"; do
    bin_abs_path=`which $bin`;
    for line in $(ldd $bin_abs_path); do
        # if absolute path
        if [[ ${line:0:1} == "/" ]]; then
            # Copy shared library
            dir_lib="`dirname $line`";
            rel_lib=${dir_lib:1};
            mkdir -p $rel_lib;
            echo "copying $line to $rel_lib";
            cp -n $line $rel_lib;
        fi
    done;
    # Copy bin
    dir_bin="`dirname $bin_abs_path`";
    rel_bin=${dir_bin:1};
    mkdir -p $rel_bin;
    echo "copying $bin_abs_path to $rel_bin";
    cp -n $bin_abs_path $rel_bin;

done;
cd ..;
