# SENTSOR Core Board 328P
## Introduction
<img src="https://github.com/adamalfath/sentsor-core-328p/blob/master/media/core328p-img0.jpg" width="600">  

Seberapa sering kalian menghadapi kebutuhan untuk pengambilan data/datalogging? monitoring peralatan industri? daya, vibrasi, environment, dll. Atau data praktikum/skripsi? pengukuran temperatur, arus, tegangan, massa, dll. Terlepas dari apa kebutuhannya, proses datalogging selalu memiliki 3 komponen utama yaitu waktu (timestamp), media penyimpanan/pengolahan, dan data yang diambil itu sendiri (biasanya dari sensor atau instrumen pengukuran). Lalu sudah berapa kali kalian mengambil 3 board berbeda untuk kebutuhan ini? Mikrokontroller, modul RTC dan modul memory card adapter, 3 komponen yang selalu hadir dalam project datalogging. Tentu sangat membantu bukan jika ada sebuah development board yang memiliki ke tiga fungsi tersebut?

SENTSOR Core Board 328P hadir sebagai development board yang dioptimasi untuk keperluan datalogging. Dalam board mungil berukuran sekitar 6x4cm, SENSOR Core Board 328P mengemas MCU ATmega328P, RTC presisi DS3231 dengan akurasi ±3.5ppm, adapter memory card untuk ukuran MicroSD, serta chip UART-to-USB FT232RL untuk menghandle keperluan koneksi via USB tanpa lagi mengkhawatirkan kompabilitas driver. Pinout dari board ini disusun sedemikian rupa untuk memudahkan manajemen koneksi untuk sensor atau GPIO yang akan digunakan. Koneksi IO dapat dilakukan menggunakan header 2.45mm (male/female) ataupun castellated holes untuk mounting board-to-board, memudahkan untuk meng-embed SENTSOR Core Board 328P ini pada setiap project datalogging kalian.

## Features
<img src="https://github.com/adamalfath/sentsor-core-328p/blob/master/media/core328p-pinoutposter.jpg" width="600">  

- **Compact & powerful**, 58.42x40.64mm (2300x1600mil) dengan MCU+RTC+uSD onboard.
- **2x18P pinout layout, pitch 2.54mm (100mil)**, dengan susunan 1 sisi untuk peripheral (power, programming, communication) dan 1 sisi untuk GPIO, mempermudah manajemen jalur/kabel yang akan digunakan.
- **Castellated holes & pin header**, pilihan koneksi untuk mempermudah pengaplikasian board SENTSOR Core pada setiap kebutuhan.
- **ATmega328P-AU** @16MHz support bootloader Arduino (default Nano 3.x).
- **FT232RL Serial UART to USB**, koneksi data ke USB tanpa install driver tambahan.
- **DS3231 Extremely Accurate RTC**, terhubung via I2C pada alamat 0x68.
- **MicroSD socket**, terhubung via SPI dengan slave select (SS) pada pin D10.
- **Built-in LED**, terhubung pada pin D2, konfigurasi active-high.
- **22 pin GPIO** @5V level: 1xUART, 1xSPI, 1xI2C, 10bit ADC (A6-A7 hanya dapat digunakan sebagai input). Silahkan lihat gambar diatas untuk lebih lanjut.
- **AMS1117 5V regulator**, tegangan input (VIN) 6.5-12V.  
  Penggunaan arus +5V via USB <= 500mA, arus +5V via input VIN <= 1A, arus +3V3 <= 50mA. Silahkan lihat skematik untuk mempelajari lebih lanjut.

## How to Use
Secara default SENTSOR Core Board 328P memiliki bootloader Arduino Nano 3.0 (update dari versi Nano old bootloader). Pilih board tersebut pada opsi board di Arduino IDE atau sejenis, pilih port yang sesuai, dan Core Board 328P sudah siap digunakan.

File example yang disediakan memiliki library dependency terkait RTC dan akses memory card, yaitu:
- RTCLib https://github.com/adafruit/RTClib
- SdFat https://github.com/greiman/SdFat  

Silahkan install library tersebut jika dibutuhkan dalam program yang akan kalian buat.

## Bill of Materials
|Designator|Qty|Name/Value|Footprint|
|-|-|-|-|
|U1|1|ATMEGA328P-AU|TQFP-32_7X7X08P|
|U2|1|FT232RL|SSOP-28_208MIL|
|U3|1|LM1117MPX-5.0|SOT-223|
|U4|1|74VHC125MTCX|TSSOP-14|
|U5|1|DS3231SN#|SOIC-16_300MIL|
|R3,R13,R4,R5,R2,R6,R1|7|1k|R0603|
|R10,R7,R8,R9|4|3.3k|R0603|
|R11,R12|2|4.7k|R0603|
|C10,C1|2|1u|C0603|
|C4,C11,C3,C8,C7,C6,C9|7|100n|C0603|
|C2,C5|2|4.7u 16V|CASE-A_3216|
|D1|1|MBR0520|SOD-123|
|LED2,LED1|2|Blue|LED0603|
|LED4,LED3|2|White|LED0603|
|X1|1|16MHz|OSC-SMD_3P-3.2x1.3|
|SW1|1|Tact Switch|3X6X2.5_SMD|
|CN1|1|MiniUSB B|MINI-USB-B-SMD_5P|
|CARD1|1|MicroSD|TF-115K_SMD|
|B1|1|CR1220|BAT_CR1220_SMD|

## Design 
<img src="https://github.com/adamalfath/sentsor-core-328p/blob/master/media/core328p-pcb-ss.png" width="600">  

SENTSOR Core Board 328P merupakan open source hardware, silahkan dimanfaatkan secara bijaksana.  

Link: https://easyeda.com/sentsor-project/sentsor-core-328p

## Gallery
<img src="https://github.com/adamalfath/sentsor-core-328p/blob/master/media/core328p-img1.jpg" width="400"> <img src="https://github.com/adamalfath/sentsor-core-328p/blob/master/media/core328p-img2.jpg" width="400">  
<img src="https://github.com/adamalfath/sentsor-core-328p/blob/master/media/core328p-img3.jpg" width="400"> <img src="https://github.com/adamalfath/sentsor-core-328p/blob/master/media/core328p-img4.jpg" width="400">  
<img src="https://github.com/adamalfath/sentsor-core-328p/blob/master/media/core328p-img5.jpg" width="400"> <img src="https://github.com/adamalfath/sentsor-core-328p/blob/master/media/core328p-img6.jpg" width="400">  
<img src="https://github.com/adamalfath/sentsor-core-328p/blob/master/media/core328p-img7.jpg" width="400"> <img src="https://github.com/adamalfath/sentsor-core-328p/blob/master/media/core328p-img8.jpg" width="400">

## Support Open-Source Hardware & SENTSOR!
Bila kalian tertarik dengan produk-produk SENTSOR, kalian bisa cek marketplace ataupun memberikan donasi pada link berikut:  

[![Store](https://img.shields.io/badge/marketplace-Tokopedia-brightgreen.svg)](https://www.tokopedia.com/gerai-sagalarupa/etalase/sentsor-product)  [![Donate](https://img.shields.io/badge/donate-PayPal-blue.svg)](https://www.paypal.me/adamalfath)  

Support kalian akan sangat membantu untuk pengembangan open-source hardware dari SENTSOR selanjutnya.

## Information
SENTSOR  
Author: Adam Alfath  
Contact: adam.alfath23@gmail.com  
Web: [sentsor.net](http://www.sentsor.net)  
Repo: [SENTSOR Main Repo](http://github.com/adamalfath/sentsor)

<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">SENTSOR Core Board 328P</span> is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.
