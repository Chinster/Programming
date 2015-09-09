#!/bin/sh
# Script installs arch linux.

ARCH_TARGET_DEV=$1
ARCH_TARGET_DIR=$2
HOSTNAME=""
ROOT_UID=0
GRUB_DEV=${ARCH_TARGET_DEV%%[0-9]}
TARGET_DEV_UUID=""
INSTALL_GRUB=0
OTHER_PKGS="git vim"
GRUB_CFG=""

if [[ $EUID -ne $ROOT_UID ]]; then
    echo "This script must be run as root"
    exit 1
fi
if [ ! $# == 2 ] || [ ! -b $ARCH_TARGET_DEV ] || [ ! -d $ARCH_TARGET_DIR ];
then
    echo "Usage: arch-installer PARTITION MOUNT-DIR"
    exit 1
fi

# awk returns UUID="<uuid>"
TARGET_DEV_UUID=$(blkid | grep $ARCH_TARGET_DEV \
    | awk '{print $2}' | tr -d "\"")

# read yes/no from:
# http://stackoverflow.com/questions/226703/how-do-i-prompt-for-input-in-a-linux-shell-script
read -p "Do you want to install grub on $GRUB_DEV? [y/n] " -n 1 -r; echo
if [[ $REPLY =~ ^[Yy]$ ]]; then
    INSTALL_GRUB=1
    OTHER_PKGS=$OTHER_PKGS" grub"

    # Make grub-config now
    # Vars ignore newline
    GRUB_CFG="set default=0
    set timeout=1
    insmod part_msdos
    insmod ext2

    menuentry \"Arch\" {
      set root=(hd0,msdos1)
      linux /boot/vmlinuz-linux root=$TARGET_DEV_UUID rw
      initrd /boot/initramfs-linux.img
    }
    "
fi

read -p "Do you want to format $ARCH_TARGET_DEV to ext4?
    All data will be lost. [y/n] " -n 1 -r; echo
if [[ $REPLY =~ ^[Yy]$ ]]; then
    mkfs.ext4 -F $ARCH_TARGET_DEV
fi

read -p "Hostname? " -r; echo
HOSTNAME=$REPLY

mount $ARCH_TARGET_DEV $ARCH_TARGET_DIR
cd $ARCH_TARGET_DIR
pacstrap $ARCH_TARGET_DIR base base-devel
genfstab -p $ARCH_TARGET_DIR >> $ARCH_TARGET_DIR/etc/fstab
sed s/"$TARGET_DEV"/UUID=$TARGET_DEV_UUID/ -i $ARCH_TARGET_DIR/etc/fstab

cp /etc/resolv.conf $ARCH_TARGET_DIR/etc/resolv.conf

# creating an in-chroot script to run
# We can not run commands in chroot from this script
# call to chroot is given a script to run
echo "export PS1='chroot'
    rm /chroot-script.sh
    echo $HOSTNAME > /etc/hostname
    ln -s /usr/share/zoneinfo/America/New_York /etc/localtime
    sed s/#en_US/en_US/ -i /etc/locale.gen
    locale-gen
    echo LANG=en_US.UTF-8 > /etc/locale.conf
    pacman -Syyyyyyyyyyyyyyyyyyyuuuuuuuuuuuuuuuuuuuuuuuu --noconfirm
    pacman -S $OTHER_PKGS --noconfirm
    " > $ARCH_TARGET_DIR/chroot-script.sh

# Install GRUB
if [[ $INSTALL_GRUB -eq 1 ]]; then
    echo "mkdir -p /boot/grub/
    echo '$GRUB_CFG' > /boot/grub/grub.cfg
    grub-install --target=i386-pc $GRUB_DEV
    " >> $ARCH_TARGET_DIR/chroot-script.sh
fi

# Leave chroot after script
echo 'exit' >> $ARCH_TARGET_DIR/chroot-script.sh

chmod a+x $ARCH_TARGET_DIR/chroot-script.sh

#chroot $ARCH_TARGET_DIR /chroot-script.sh
arch-chroot $ARCH_TARGET_DIR /chroot-script.sh

# Caps to control
dumpkeys | sed s/Caps_Lock/Control/ | gzip > $ARCH_TARGET_DIR/usr/share/kbd/keymaps/i386/qwerty/caps2ctrl.map.gz
echo 'KEYMAP=caps2ctrl' > $ARCH_TARGET_DIR/etc/vconsole.conf

# Clear up file
cd
umount $ARCH_TARGET_DIR
echo -e "\n\n-------\nIf installing to usb edit mkinitcpio to load block after udev.\n"
