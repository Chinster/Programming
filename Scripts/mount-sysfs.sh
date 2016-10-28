DEST=/Downloads/gentoo
sudo mount -t proc proc $DEST/proc/
sudo mount --rbind /dev $DEST/dev/
sudo mount --rbind /sys $DEST/sys/
sudo mount --make-rslave $DEST/dev/
sudo mount --make-rslave $DEST/sys/
