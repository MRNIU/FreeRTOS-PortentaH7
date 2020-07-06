
# This file is a part of MRNIU/FreeRTOS-PortentaH7 (https://github.com/MRNIU/FreeRTOS-PortentaH7).
#
# receive.sh for MRNIU/FreeRTOS-PortentaH7.

stty -f /dev/cu.usbmodem2003645000002 raw speed 9600 min 0 time 10
while [ 1 -eq 1 ]
do
    cat /dev/cu.usbmodem2003645000002 >> "recv.log"
done
