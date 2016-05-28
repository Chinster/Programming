#!/bin/sh
# Script installs arch linux.
# TODO: Install yaourt.
#  -makepkg requires non-root user. As a result we must install dependencies
#  -as root, run makepkg as the nobody user, then install the resulting package.
#  -Somehow we must link the dependencies to the AUR package in pacman's database.

ARCH_TARGET_DIR=$2
OTHER_PKGS="git vim wpa_supplicant alsa-utils"
EXTRA_PKGS="sway rxvt-unicode firefox"

# Check for root
if [[ $EUID -ne 0 ]]; then
    echo "This script must be run as root"
    exit 1
fi

# Check for directory as program argument
if [ ! $# == 1 ] || [ ! -d $ARCH_TARGET_DIR ];
then
    echo "Usage: arch-installer PARTITION MOUNT-DIR"
    exit 2
fi

# Ensure a partition is mounted at directory.
cd $ARCH_TARGET_DIR
ABS_PATH=`pwd`
cd -

if [[ $? -ne 0 ]]
then
    echo "Mount your partition at $ARCH_TARGET_DIR"
    exit 3
fi

read -p "Hostname? " -r; echo
HOSTNAME=$REPLY

cd $ARCH_TARGET_DIR
pacstrap $ARCH_TARGET_DIR base base-devel
genfstab -p $ARCH_TARGET_DIR >> $ARCH_TARGET_DIR/etc/fstab
echo $HOSTNAME > $ARCH_TARGET_DIR/hostname
sed s/#en_US/en_US/ -i $ARCH_TARGET_DIR/etc/locale.gen

# creating an in-chroot script to run
# We can not run commands in chroot from this script.
echo "export PS1='chroot'
rm /chroot-script.sh
ln -s /usr/share/zoneinfo/America/New_York /etc/localtime
locale-gen
echo LANG=en_US.UTF-8 > /etc/locale.conf
pacman -Syyyyyyyyyyyyyyyyyyyuuuuuuuuuuuuuuuuuuuuuuuu --noconfirm
pacman -S $OTHER_PKGS --noconfirm
pacman -S $EXTRA_PKGS --noconfirm
exit
" > $ARCH_TARGET_DIR/chroot-script.sh

chmod a+x $ARCH_TARGET_DIR/chroot-script.sh

arch-chroot $ARCH_TARGET_DIR /chroot-script.sh

echo "Don't forget to setup your bootloader!"
