/*
 * FAN.c
 * 
 * Copyright 2023  <pi@raspberrypi>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <wiringPi.h>
#include "wiringPiI2C.h"
char LED = 25;
char iic_hand;
char slave_addr=0x0b;
char null=0x00;
char start_cmd=0x01;
char getMode_cmd=0x02;
char sendTemp_cmd=0x03;
int temp;
float getCPUtemperture()
{
	
    FILE *temperatureFile;
    double T;
    temperatureFile = fopen ("/sys/class/thermal/thermal_zone0/temp", "r");
    if (temperatureFile == NULL); //print some message
    fscanf (temperatureFile, "%lf", &T);
    T /= 1000;
    printf ("The temperature is %6.3f C.\n", T);
    fclose (temperatureFile);
	return T;
}

char IIC_start(char fd,char cmd,char data)
{
	wiringPiI2CWriteReg8(fd,cmd,data);
	return wiringPiI2CRead(fd);
}

void get_Mode(char fd,char cmd,char data)
{
	char mode;
	wiringPiI2CWriteReg8(fd,cmd,data);
	mode=wiringPiI2CRead(fd);
	if(mode==1)
	printf("Mode:Auto_mode\n");
	if(mode==2)
	printf("Mode:Manu_mode\n");
}

void trans_temp(char fd,char cmd,int data)
 {	

	 data=(int)getCPUtemperture();
	 wiringPiI2CWriteReg8(fd,cmd,data);
 }
int main(void)
{
	
	if(wiringPiSetup() !=-1)
	{
		printf("ok\n");	
	}
	iic_hand=wiringPiI2CSetup(slave_addr);
	if(IIC_start(iic_hand,start_cmd,null)==null)
	{
		
		while(1)
		{
			trans_temp(iic_hand,sendTemp_cmd,temp);
			delay(500);
			//get_Mode(iic_hand,getMode_cmd,null);
		}
	}

}

