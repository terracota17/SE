/*
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A 
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR 
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION 
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE 
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO 
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO 
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE 
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY 
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#include <stdio.h>
#include "xparameters.h"
#include "xil_cache.h"
#include "xbasic_types.h"
#include "xbram.h"
#include "bram_header.h"
#include "xbasic_types.h"
#include "xgpio.h"
#include "gpio_header.h"
#include "leds_rgb.h"
#include "banner.h"
#include <xstatus.h>
#include "xutil.h"
#include "keypad.h"
#include <stdbool.h>
#include <ctype.h>

#define XPAR_RS232_UART_1_BASEADDR 0x84000000
#define RGB_BASEADRRESS 0xC7200000
#define BANNER_BASEADRRESS 0xC5800000
#define KEYPAD_BASEADDRESS 0xC9600000

#define N 3


int getNumber (){

	Xuint8 byte;
	Xuint8 uartBuffer[16];
	Xboolean validNumber;
	int digitIndex;
	int digit,sign;
	Xuint32 number;
	int c;

	while(1){
		byte = 0x00;
		digit = 0;
		digitIndex = 0;
		number = 0;
		validNumber = XTRUE;

		//get bytes from uart until RETURN is entered

		while(byte != 0x0d && byte != 0x0A){
			byte = XUartLite_RecvByte(XPAR_RS232_UART_1_BASEADDR);
			uartBuffer[digitIndex] = byte;
			XUartLite_SendByte(XPAR_RS232_UART_1_BASEADDR,byte);
			digitIndex++;
		}

		//calculate number from string of digits

		for(c = 0; c < (digitIndex - 1); c++){
			if(c == 0){
				//check if first byte is a "-"
				if(uartBuffer[c] == 0x2D){
					sign = -1;
					digit = 0;
				}
				//check if first byte is a digit
				else if((uartBuffer[c] >> 4) == 0x03){
					sign = 1;
					digit = (uartBuffer[c] & 0x0F);
				}
				else
					validNumber = XFALSE;
			}
			else{
				//check byte is a digit
				if((uartBuffer[c] >> 4) == 0x03){
					digit = (uartBuffer[c] & 0x0F);
				}
				else
					validNumber = XFALSE;
			}
			number = (number * 10) + digit;
		}
		number *= sign;
		if(validNumber == XTRUE){
			return number;
		}
		print("This is not a valid number.\n\r");
	}
}


const int cero[7] = {0x1F,0x11,0x11,0x11,0x11,0x11,0x1F};
const int uno[7] = {0x04,0x0C,0x04,0x04,0x04,0x04,0x0E};
const int dos[7] = {0x0E,0x11,0x01,0x02,0x04,0x08,0x1F};
const int tres[7] = {0x1F,0x02,0x04,0x02,0x01,0x11,0x0E};
const int cuatro[7] = {0x02,0x06,0x0A,0x12,0x1F,0x02,0x02};
const int cinco[7] = {0x1F,0x10,0x1E,0x01,0x01,0x11,0x0E};
const int seis[7] = {0x06,0x08,0x10,0x1E,0x11,0x11,0x0E};
const int siete[7] = {0x1F,0x01,0x02,0x04,0x08,0x08,0x08};
const int ocho[7] = {0x0E,0x11,0x11,0x0E,0x11,0x11,0x0E};
const int nueve[7] = {0x0E,0x11,0x11,0x0F,0x01,0x02,0x0C};


//y letras
const int A[7] = {0x1F,0x11,0x11,0x1F,0x11,0x11,0x11};
const int B[7] = {0x10,0x10,0x10,0x1F,0x11,0x11,0x1F};
const int C[7] = {0x1F,0x10,0x10,0x10,0x10,0x10,0x1F};
const int D[7] = {0x01,0x01,0x01,0x1F,0x11,0x11,0x1F};
const int E[7] = {0x1F,0x11,0x11,0x1F,0x10,0x10,0x1F};
const int F[7] = {0x1F,0x10,0x10,0x1F,0x10,0x10,0x10};



//bem-vindo
const int hola[8][7] = {		{0x0A,0x12, 0x0C, 0x10, 0x1E, 0x0A, 0x04, 0x00},
								{0x00,0x12, 0x12, 0x10, 0x12, 0x0A, 0x02, 0x00},
								{0x0A,0x12, 0x12, 0x10, 0x12, 0x0A, 0x09, 0x00},
								{0x0A,0x1E, 0x12, 0x10, 0x1E, 0x0A, 0x01, 0x00},
								{0x0A,0x12, 0x12, 0x10, 0x12, 0x0A, 0x09, 0x00},
								{0x0A,0x12, 0x12, 0x10, 0x12, 0x00, 0x02, 0x00},
								{0x0A,0x12, 0x0C, 0x1E, 0x12, 0x0A, 0x04, 0x00}};

void BANNER_inicializa(){
	Xuint32 dato,fila,columna,data;
	dato=0x0;
	for(fila = 0; fila < 7; fila++){
			for(columna = 0; columna < 8; columna++){
				data = (( fila & 0xff ) << (31 -7)) +  (( columna & 0xff ) << (31 -15)) + (( dato & 0xff ) << (31 -23));
				BANNER_mWriteToFIFO( BANNER_BASEADRRESS , 0, data );
			}
	}
}

void BANNER_resetea(){
	Xuint32 dato,fila,columna,data;
		dato=0x0;
		for(fila = 0; fila < 7; fila++){
				for(columna = 0; columna < 8; columna++){
					data = (( fila & 0xff ) << (31 -7)) +  (( columna & 0xff ) << (31 -15)) + (( dato & 0xff ) << (31 -23));
					BANNER_mWriteToFIFO( BANNER_BASEADRRESS , 0, data );
				}
		}
}

void BANNER_enviarDato(Xuint32 col, Xuint32 fil,Xuint32 dato){

	while(BANNER_mWriteFIFOFull(BANNER_BASEADRRESS)){}
	Xuint32 data;
	data = ((fil & 0xff)<< (31-7)) + ((col & 0xff) << (31-15)) + ((dato & 0xff)<< (31-23));

	BANNER_mWriteToFIFO(BANNER_BASEADRRESS,0,data);

}


void BANNER_welcome(){
	Xuint32 fila,columna;
			for(fila = 0; fila < 7; fila++){
					for(columna = 0; columna < 8; columna++){
						BANNER_enviarDato(columna,fila, (Xuint32) hola[fila][columna]);
					}
			}
}




void ZUMBADOR_inicializa(XGpio* Gpio_zumbador, Xuint32 zumbador) {
	Xuint32 status;

	// Configuración de la GPIO para el zumbador de la placa de expansión
	status = XGpio_Initialize(Gpio_zumbador, zumbador);

	if (status != XST_SUCCESS)
		xil_printf("Error en la inicializacion\r\n");
	else{
		XGpio_SetDataDirection(Gpio_zumbador, 1, 0x00);
		xil_printf("Inicializado con exito\r\n");
	}
}

void ZUMBADOR_suena(XGpio* Gpio_zumbador) {
	XGpio_DiscreteWrite(Gpio_zumbador, 1, (u8)0);
}

void ZUMBADOR_calla(XGpio *Gpio_zumbador) {
	XGpio_DiscreteWrite(Gpio_zumbador, 1, (u8)1);
}


void suenaZumbadorEleccionEscogida(XGpio *Gpio_zumbador){
	ZUMBADOR_suena(Gpio_zumbador);

	int i;
	for(i = 0; i < 0x00070000; i++){} // retardo

	ZUMBADOR_calla(Gpio_zumbador);
}



int intensidad;
char key;
bool op = false;
char modo;


/*
 * 	Funcion para leer el dato del keypad y codificarlo en entero
 * */
char getNumberKeypad(){


	Xuint32 value,dato,oldValue;
	char num = ' ';

	value = KEYPAD_mReadReg(KEYPAD_BASEADDRESS,0);

	dato = (value>>28) & 0xF;

	KEYPAD_mWriteReg(KEYPAD_BASEADDRESS,0,value);
	KEYPAD_mWriteReg(KEYPAD_BASEADDRESS,0,0);
	oldValue = dato;

	print("\t\t Esperando a que el usuario pulse un tecla...\n");
	while(dato == 0){
	   if(value != oldValue){
		   dato = (value>>28) & 0xF;
		   oldValue = value;
	   }
	   value = KEYPAD_mReadReg(KEYPAD_BASEADDRESS,0);

	   KEYPAD_mWriteReg(KEYPAD_BASEADDRESS,0,0);
	}

	switch ( dato ) {
		case 0x0:
			num = '0';
			break;
		case 0x1:
			num = '1';
			break;
		case 0x2:
			num = '2';
			break;
		case 0x3:
			num = '3';
			break;
		case 0x4:
			num = '4';
			break;
		case 0x5:
			num = '5';
			break;
		case 0x6:
			num = '6';
			break;
		case 0x7:
			num = '7';
			break;
		case 0x8:
			num = '8';
			break;
		case 0x9:
			num = '9';
			break;
		case 0xA:
			num = 'A';
			break;
		case 0xB:
			num = 'B';
			break;
		case 0xC:
			num = 'C';
			break;
		case 0xD:
			num = 'D';
			break;
		case 0xE:
			num = 'E';
			break;
		case 0xF:
			num = 'F';
			break;
		default:
			num = 'R';
	}

	value = KEYPAD_mReadReg(KEYPAD_BASEADDRESS,0);
	KEYPAD_mWriteReg(KEYPAD_BASEADDRESS,0,0);

	return num;
}

//write numbers
void BANNER_write0(){
	int i;
	for(i = 0; i < 7; i++){
		BANNER_enviarDato(0,i,cero[i]);
	}
}

void BANNER_write1(){
	int i;
	for(i = 0; i < 7; i++){
		BANNER_enviarDato(0,i,uno[i]);
	}
}


void BANNER_write2(){
	int i;
	for(i = 0; i < 7; i++){
		BANNER_enviarDato(0,i,dos[i]);
	}
}


void BANNER_write3(){
	int i;
	for(i = 0; i < 7; i++){
		BANNER_enviarDato(0,i,tres[i]);
	}
}


void BANNER_write4(){
	int i;
	for(i = 0; i < 7; i++){
		BANNER_enviarDato(0,i,cuatro[i]);
	}
}


void BANNER_write5(){
	int i;
	for(i = 0; i < 7; i++){
		BANNER_enviarDato(0,i,cinco[i]);
	}
}

void BANNER_write6(){
	int i;
	for(i = 0; i < 7; i++){
		BANNER_enviarDato(0,i,seis[i]);
	}
}
void BANNER_write7(){

	int i;
	for(i = 0; i < 7; i++){
		BANNER_enviarDato(0,i,siete[i]);
	}

}
void BANNER_write8(){
	int i;
	for(i = 0; i < 7; i++){
		BANNER_enviarDato(0,i,ocho[i]);
	}

}
void BANNER_write9(){
	int i;
	for(i = 0; i < 7; i++){
		BANNER_enviarDato(0,i,nueve[i]);
	}
}

//write letras

void BANNER_writeLetterA(){
	int i;
	for(i = 0; i < 7; i++){
		BANNER_enviarDato(0,i,A[i]);
	}
}


void BANNER_writeLetterB(){
	int i;
	for(i = 0; i < 7; i++){
		BANNER_enviarDato(0,i,B[i]);
	}
}

void BANNER_writeLetterC(){
	int i;
	for(i = 0; i < 7; i++){
		BANNER_enviarDato(0,i,C[i]);
	}
}


void BANNER_writeLetterD(){
	int i;
	for(i = 0; i < 7; i++){
		BANNER_enviarDato(0,i,D[i]);
	}
}


void BANNER_writeLetterE(){
	int i;
	for(i = 0; i < 7; i++){
		BANNER_enviarDato(0,i,E[i]);
	}
}

void BANNER_writeLetterF(){
	int i;
	for(i = 0; i < 7; i++){
		BANNER_enviarDato(0,i,F[i]);
	}
}

void BANNER_mostrarLetraONumero(char letra_o_numero){

	if(letra_o_numero == '0'){
		BANNER_write0();
	}else if(letra_o_numero == '1'){
		BANNER_write1();
	}else if(letra_o_numero == '2'){
		BANNER_write2();
	}else if(letra_o_numero == '3'){
		BANNER_write3();
	}else if(letra_o_numero == '4'){
		BANNER_write4();
	}else if(letra_o_numero == '5'){
		BANNER_write5();
	}else if(letra_o_numero == '6'){
		BANNER_write6();
	}else if(letra_o_numero == '7'){
		BANNER_write7();
	}else if(letra_o_numero == '8'){
		BANNER_write8();
	}else if(letra_o_numero == '9'){
		BANNER_write9();
	}else if(letra_o_numero == 'A'){
		BANNER_writeLetterA();
	}else if(letra_o_numero == 'B'){
		BANNER_writeLetterB();
	}else if(letra_o_numero == 'C'){
		BANNER_writeLetterC();
	}else if(letra_o_numero == 'D'){
		BANNER_writeLetterD();
	}else if(letra_o_numero == 'E'){
		BANNER_writeLetterE();
	}else if(letra_o_numero == 'F'){
		BANNER_writeLetterF();
	}
}




Xuint32 KEYPAD_recogerValorRGB(){

	print("Esperando que el usario digite un numero por la uart termite\n");

	Xuint32 num = (Xuint32) getNumber();

	xil_printf("numero codificado para los rgb : %d\n", num);

	return num;

}

Xuint32 intensidad_rojo = 0;
Xuint32 intensidad_verde = 0;
Xuint32 intensidad_azul = 0;


int main() 
{

   Xil_ICacheEnable();
   Xil_DCacheEnable();

   print("--- Proyecto SE --- Javier Maria Parra Gonzalez---\n\r");





   BANNER_welcome();

   XGpio Gpio_zumbador;
   Xuint32 zumbador = XPAR_ZUMBADOR_DEVICE_ID;

   ZUMBADOR_inicializa(&Gpio_zumbador, zumbador);

   while(!op){



	   print("Menu de opciones\r\n");
	   print("\t 1) Letras/numeros por medio del teclado matricial de la FPGA (se mostraran en el banner)\r\n");
	   print("\t 2) Seleccione color RGB\r\n");
	   print("\t F) Seleccione 'F' (a traves del teclado matricial) para salir del programa \r\n");

	   //conseguir modo
	   modo = getNumberKeypad();

	   suenaZumbadorEleccionEscogida(&Gpio_zumbador);

	   if(modo == '1'){
		   //coseguir letra o numero del keypad
		   print("Digite un letra o numero del keypad y se motrara en el banner\n");
		   char letra_o_numero = getNumberKeypad();

		   BANNER_resetea(); //reseteamos el banner para borrar  todo lo que estaba anteriormente en el banner

		   //mostrar letra escogida mediante termite y banner y si quieres 7 seg
		   BANNER_mostrarLetraONumero(letra_o_numero);

		   suenaZumbadorEleccionEscogida(&Gpio_zumbador);

	   }else if(modo == '2'){


		   //modo RGB modo 2

		   print("\t\t A) Introduce 'A' para seleccionar el color rojo por el termite\n");
		   print("\t\t D) Introduce 'D' para seleccionar el color verde por el termite\n");
		   print("\t\t B) Introduce 'B' para seleccionar el color azul por el termite\n");

		   //recoger letra
		   char letra = getNumberKeypad();

		   suenaZumbadorEleccionEscogida(&Gpio_zumbador);

		   if(letra == 'A'){
			   // letra A rojo
			   //coger el los numero que vaya metiendo el usario hasta un maximo de tres 128 ... 255 ... 144 por ejemplo
			   print("\t\t A) Introduce el el valor del canal rojo\n");
			   //lectura de intensidad
			   xil_printf("Intensidad rojo actual %d\n", intensidad_rojo);

			   intensidad_rojo =  KEYPAD_recogerValorRGB();

			   suenaZumbadorEleccionEscogida(&Gpio_zumbador);

			   LEDS_RGB_mWriteSlaveReg0(RGB_BASEADRRESS, 0, intensidad_rojo);

		   }else if(letra == 'D'){
			   //D verde

			   print("\t\t D) Introduce el el valor del canal verde\n");
			   //lectura de intensidad

			   suenaZumbadorEleccionEscogida(&Gpio_zumbador);

			   xil_printf("Intensidad verde actual %d\n", intensidad_verde);

			   intensidad_verde = KEYPAD_recogerValorRGB();

			   LEDS_RGB_mWriteSlaveReg1(RGB_BASEADRRESS, 0,  intensidad_verde);

		   }else if(letra == 'B'){
			   //B -- azul

			   //lectura de intensidad

			   print("\t\t B) Introduce el el valor del canal azul\n");

			   suenaZumbadorEleccionEscogida(&Gpio_zumbador);

			   xil_printf("Intensidad azul actual %d\n", intensidad_azul);

			   intensidad_azul = KEYPAD_recogerValorRGB();

			   LEDS_RGB_mWriteSlaveReg2(RGB_BASEADRRESS, 0,  intensidad_azul);

			   //Escribir el el banner el numero recien escogido

		   }else if(key == 'R')
			   print("Error en la lectura de la tecla de keypad \r\n");


	   }else if(modo == 'F'){
		   op = true;
	   }

   }

   print("---Exiting Proyecto SE---\n\r");

   Xil_DCacheDisable();
   Xil_ICacheDisable();

   return 0;
}

