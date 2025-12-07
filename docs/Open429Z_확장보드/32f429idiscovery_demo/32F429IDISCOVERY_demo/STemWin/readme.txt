/**
  @page Demo_Binary   Description of the 32F429IDISCOVERY Demo firmware's binary files
 
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics  *******************
  * @file    Demonstrations/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the 32F429IDISCOVERY Demo firmware's binary files.
  ******************************************************************************
  *
  * Copyright (c) 2017 STMicroelectronics. All rights reserved.
  *
  * This software component is licensed by ST under Ultimate Liberty license SLA0044,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                       http://www.st.com/SLA0044
  *
  ******************************************************************************
  @endverbatim

@par Demo Description

The STM32Cube Demonstration platform comes on top of the STM32CubeTM as a firmware
package that offers a full set of software components based on a modules architecture
allowing re-using them separately in standalone applications. All these modules are
managed by the STM32Cube Demonstration kernel allowing to dynamically adding new
modules and access to common resources (storage, graphical components and widgets,
memory management, Real-Time operating system)

The demonstration firmware is built around the graphical library STemWin and the FreeRTOS 
real time operating system and uses almost the whole STM32 capability to offer a large scope
of usage based on the STM32Cube HAL, BSP and several Middleware components.
  
Below you find an overview of the diffrent offred module in the demonstration:

 + System
 --------
 The system module provides three control tabs: 
  - system information 
  - general settings
  - date settings
  - clock settings 

 To set the global demonstration settings. The system module retrieves
 demonstration information from internal kernel settings data structures and acts 
 on the several kernel services to changes settings.
 
 + File browser
 --------------
 The File browser module is a system module that allows to explore the connected
 storage unit(s), to delete or to open a selected file. The file list structure 
 is built during the media connection and updated after a connection status change of one
 of the used media.
 
 + Game
 -------
 The game coming in the STM32Cube demonstration is based on the Reversi game. It is a
 strategy board game for two players, played on an 8×8 board. The goal of the game is to
 have the majority of disks turned to display your color when the last playable empty square
 is filled.

 + Benchmark
 -----------
 The Benchmark module is a system module that allows measure the graphical performance
 by measuring the time needed to draw several colored rectangles in random position with
 random size during a specific period. The result is given in pixel per second.
 
 + Video
 -------
 The video player module provides a video solution based on the STM32F4xx and STemWin
 movie API. It supports playing movie in emf format.
 
 + Image viewer
 --------------
 The Image viewer module allows displaying bmp and jpg pictures. It is possible to load the
 full images list from a folder or to add the images manually to the playlist. Once the playlist is
 created, navigation between pictures can be done either via Next and previous buttons or by
 enabling the slide show mode. The slide show timer can be changed on the fly (there is no
 need to restart the module).
 
 For more details about the demonstration modules please refers to  STM32CubeF4 demonstration (UM1743)

@par Hardware and Software environment

  - This example runs on STM32F429xx devices.
    
  - This example has been tested with STMicroelectronics 32F429IDISCOVERY RevC
    boards and can be easily tailored to any other supported device 
    and development board.

@par How to use it ? 
 + Copy the picture and video files provided under "Media/" in the USB key
   USB key must contain the files listed below:
     - .jpg and .bmp files available within the "BMP_240x320" and "BMP_320x240" folder under "Media/Pictures" 
     - .emf files available "Media/Video" 
 + Plug the USB key into the 32F429IDISCOVERY board through 'USB micro A-Male to A-Female' cable(CN6).

You can use any in-system programming tool to reprogram the demonstration 
using these binary files, as described below:

 + Using "in-system programming tool" such as ST-Link Utility
    - Connect the 32F429IDISCOVERY board to a PC with a 'USB type A to Micro-B'
      cable through USB connector CN1 to power the board.
    - Make sure that the embedded ST-LINK/V2 is configured for in-system programming
      (both CN4 jumpers ON)
    - Use "STM32CubeDemo_STM32F429I-Discovery_1.5.0.hex" binary with your preferred 
      in-system programming tool to reprogram the demonstration firmware 
      (ex. STM32 ST-LINK Utility, available for download from www.st.com).

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
 
