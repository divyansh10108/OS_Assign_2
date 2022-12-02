# #! /bin/sh

cd kernel_compiler
tar -xvJf linux-5.10.155.tar.xz
cd ..
cp config-rev-9-gold ./kernel_compiler/linux-5.10.155
cd kernel_compiler/linux-5.10.155
mv config-rev-9-gold .config
make mrproper
make olddefconfig

make -j2
make modules
ake modules_install
echo "compiled"
