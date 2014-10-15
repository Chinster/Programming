#!/bin/bash
# Script installs arch linux, grub, and wireless tools on a device.
set -e
# Aborts script when command fail

ARCH_TARGET_DEV=$1
ARCH_TARGET_DIR=$2
HOSTNAME="themep"
ROOT_UID=0
GRUB_DEV=""
INSTALL_GRUB=0

if [[ $EUID -ne $ROOT_UID ]]; then
    echo "This script must be run as root"
    exit $E_NOTROOT
fi
if [ ! $# == 2 ] || [ ! -b $ARCH_TARGET_DEV ] || [ ! -d $ARCH_TARGET_DIR ]; then
    echo "Usage: arch-installer [device] [mount-dir]"
    exit 1
fi

GRUB_DEV=${ARCH_TARGET_DEV%%[0-9]}
read -p "Do you want to install grub on "$GRUB_DEV"? [y/n] " -n 1 -r; echo
if [[ $REPLY =~ ^[Yy]$ ]]; then
    INSTALL_GRUB=1
fi

read -p "Do you want to format "$ARCH_TARGET_DEV" to ext4? All data will be lost. [y/n] " -n 1 -r; echo
if [[ $REPLY =~ ^[Yy]$ ]]; then
    mkfs.ext4 -F $ARCH_TARGET_DEV
fi

mount $ARCH_TARGET_DEV $ARCH_TARGET_DIR
cd $ARCH_TARGET_DIR
pacstrap $ARCH_TARGET_DIR base base-devel
genfstab -p $ARCH_TARGET_DIR >> $ARCH_TARGET_DIR/etc/fstab
# These mounts seem to fail. Used arch-chroot instead.
#mount -t proc proc $ARCH_TARGET_DIR/proc/
#mount --rbind /sys $ARCH_TARGET_DIR/sys/
#mount --rbind /dev $ARCH_TARGET_DIR/dev/
cp /etc/resolv.conf $ARCH_TARGET_DIR/etc/resolv.conf

# creating an in-chroot script to run
#pacman -S iw vim git --noconfirm
echo 'export PS1="chroot"
    echo '$HOSTNAME' > /etc/hostname
    ln -s /usr/share/zoneinfo/US/Eastern /etc/localtime
    sed s/#en_US/en_US/ -i /etc/locale.gen
    locale-gen
    echo LANG=en_US.UTF-8 > /etc/locale.conf
    pacman -Syuu --noconfirm
    mkinitcpio -p linux
    rm /chroot-script.sh
' > $ARCH_TARGET_DIR/chroot-script.sh
if [ $INSTALL_GRUB -e 1 ]; then
    echo 'pacman -S grub --noconfirm
        grub-mkconfig -o /boot/grub/grub.cfg
    ' >> $ARCH_TARGET_DIR/chroot-script.sh
    echo 'grub-install --target=i386-pc '$GRUB_DEV >> $ARCH_TARGET_DIR/chroot-script.sh
fi
chmod a+x $ARCH_TARGET_DIR/chroot-script.sh

#chroot $ARCH_TARGET_DIR /chroot-script.sh
arch-chroot $ARCH_TARGET_DIR /chroot-script.sh
# Caps to control
dumpkeys | sed s/Caps_Lock/Control/ | gzip > $ARCH_TARGET_DIR/usr/share/kbd/keymaps/i386/qwerty/caps2ctrl.map.gz
echo 'KEYMAP=caps2ctrl' > $ARCH_TARGET_DIR/etc/vconsole.conf


# Clear up file
rm -f $ARCH_TARGET_DIR/chroot-script.sh
cd
umount $ARCH_TARGET_DIR
echo -e "\n\n-------\nIf installing to usb edit mkinitcpio to load block right after udev.\n"
if [ $INSTALL_GRUB -e 0 ]; then
    echo -e "Grub was not installed.\n-------\n"
fi
