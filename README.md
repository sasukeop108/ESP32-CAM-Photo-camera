# Introduction

One day, I was thinking about taking some pictures with my friends in school. But its not possible as i would get caught from sound from a cameras. If i bring a mobile, Its very hard too take a photo with it as i would get caught due to its size. So i thought why not build our own camera which is small,Portable and could take photos without being caught. I had a esp32 cam in my home so i used it as the mcu and camera.

Its a camera where you can take photos without sound and getting caught. It could even send the photo to your telegram account and it is powered by a battery. A photo can be taken by touching a button in the touch screen. It may sound like a joke but its not.

# PCB 3D
![](https://github.com/sasukeop108/ESP32-CAM-Photo-camera/blob/main/Assets/camerafront.png)
![](https://github.com/sasukeop108/ESP32-CAM-Photo-camera/blob/main/Assets/cameraback.png)
# PCB
[![](https://github.com/sasukeop108/ESP32-CAM-Photo-camera/blob/main/Assets/camera-pcb.png)
]
# Schematic

[![](https://github.com/sasukeop108/ESP32-CAM-Photo-camera/blob/main/Assets/Schematic.png)

# BOM

| Item                                                                       | Quantity | Unit Price (INR) | Line Total (INR) | Line Total (USD) | Category     | Link                                                                 |
|----------------------------------------------------------------------------|----------|-----------------|-----------------|-----------------|-------------|----------------------------------------------------------------------|
| LiPo Battery (2000 mAh, 3.7 V)                                            | 1        | ₹314            | ₹314            | $3.49           | Robu        | [Link](https://robu.in/product/nova-103450-2000mah-3-7v-lipo-battery-pack/) |
| 5V 3A DC Boost Step-Up Module                                             | 1        | ₹129            | ₹129            | $1.43           | Robu        | [Link](https://robu.in/product/5v-3a-dc-boost-step-up-module/)       |
| 2.4″ SPI 240×320 TFT Display Module                                       | 1        | ₹732            | ₹732            | $8.13           | Robu        | [Link](https://robu.in/product/2-4-inch-spi-interface-240x320-touch-screen-tft-colour-display-module/) |
| TP4056 1A Li‑Ion Battery Charging Module                                   | 2        | ₹9              | ₹18             | $0.20           | Robu        | [Link](https://robu.in/product/tp4056-1a-li-ion-battery-charging-board-micro-usb-with-current-protection-type-c-connector/) |
| *Note: Robu.in minimum order price for TP4056 above ₹10*                  |          |                 |                 |                 | Robu        |                                                                      |
| ESP32-CAM (Self-Sourced)                                                  | 1        |                 |                 |                 | Self-Sourced| Self-Sourced                                                         |
| Power Switch (Self-Sourced)                                               | 1        |                 |                 |                 | Self-Sourced| Self-Sourced                                                         |
| Shipping Charges (Robu.in)                                                | -        | ₹0              | ₹0              | $0.00           | Robu        |                                                                      |
| PCB (JLCPCB Prototype / Fabrication)                                      | 1        | ₹914            | ₹914            | $10.15          | PCB         | [Link](https://jlcpcb.com/)                                          |
| **Robu Total**                                                            |          |                 | **₹1193**       | **$13.26**      |             |                                                                      |
| **Grand Total**                                                           |          |                 | **₹2107**       | **$23.41**      |             |                                                                      |

# Cart

[![](https://github.com/sasukeop108/ESP32-CAM-Photo-camera/blob/main/BOM%2BCart/robu1.png)
[![](https://github.com/sasukeop108/ESP32-CAM-Photo-camera/blob/main/BOM%2BCart/robu2.png)
[![](https://github.com/sasukeop108/ESP32-CAM-Photo-camera/blob/main/BOM%2BCart/jlcphoto1.png)
[![](https://github.com/sasukeop108/ESP32-CAM-Photo-camera/blob/main/BOM%2BCart/jlcphoto2.png)

# Libraries used
- WiFi
- WiFiClientSecure
- UniversalTelegramBot
- lvgl
- TFT_eSPI
- TJpg_Decoder
- esp_camera
- FS
- SD_MMC
