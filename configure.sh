if [ ! $# -eq 1 ]
  then
    echo "please input  plat name"
    exit 1
fi

PLAT_NAME=$1

cp configs/${PLAT_NAME}/defconfig .config
cp configs/${PLAT_NAME}/flashdog.sh  flashdog.sh
cp configs/${PLAT_NAME}/memmap    memmap
