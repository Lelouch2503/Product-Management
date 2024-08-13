# Product-Management
Description:
  - This project focused on managing the product using RFID technology
  - This system is built around S32K144, which comunicates with module RC522(SPI protocol), LCD1602(I2C protocol).
The MCU S32K144 comunicates with ESP32 via UART protocol then update data on mongodb using HTTP.
  - A restful-api is deployed as a server for updating data.

Hardware: Esp32, S32K144.
Database: Mongodb.
Programming language: C, C++, Python



