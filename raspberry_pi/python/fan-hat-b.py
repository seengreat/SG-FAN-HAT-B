import smbus
import os
import time
i=True

bus=smbus.SMBus(1)
slave_addr=0x0b
nul=0x00
def getCPUtemperature():
    res = os.popen('vcgencmd measure_temp').readline()
    return(res.replace("temp=","").replace("'C\n",""))

def IIC_start():
    bus.write_byte_data(slave_addr,0x01,nul)
    return bus.read_byte(slave_addr)

def get_Mode():
    bus.write_byte_data(slave_addr,0x02,nul)
    Mode=bus.read_byte(slave_addr)
    if Mode ==1:
        printf('Mode:Auto_mode')
    elif Mode==2:
        printf('Mode:Manu_mode')
        
def trans_temp():
    temp=getCPUtemperature()
    bus.write_byte_data(slave_addr,0x03,int(float(temp)))
    return temp

if IIC_start()==nul:
    while i:
        CPU_temp = trans_temp()
        print('CPU_temp='+CPU_temp)
        
        time.sleep(0.5)
    # = bus.read_byte(slave_addr)
    #print('value'+value)
    #time.sleep(0.5)
