#! /bin/sh


#echo "ram ram 2"
cd kernel_compiler2
tar -xvJf linux-5.10.155.tar.xz
cd ..
cp config-rev-9-gold ./kernel_compiler2/linux-5.10.155
cd kernel_compiler2/linux-5.10.155
mv config-rev-9-gold .config
make mrproper
make olddefconfig

make -j2
make modules
make modules_install
echo "compiled2"
