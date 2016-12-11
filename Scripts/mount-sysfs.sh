DEST=$1

if [ ! $# == 1 ];
then
    echo "Usage: mount-sysfs CHROOT"
    exit 1
fi

sudo mount -t proc proc $DEST/proc/
sudo mount --rbind /dev $DEST/dev/
sudo mount --rbind /sys $DEST/sys/
sudo mount --make-rslave $DEST/dev/
sudo mount --make-rslave $DEST/sys/
