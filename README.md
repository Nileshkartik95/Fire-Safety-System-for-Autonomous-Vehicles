# Fire-Safety-System-for-Autonomous-Vehicles
## Objective

The world is moving towards the Internet of Things (IoT), so things are getting automated nowadays, so it is very important to protect human life from hazardous situations. The predominant objective of this project is to develop a "Fire Safety System for Autonomous Vehicles” to detect a spark or fire from the battery or any part of the vehicle. Whenever a hazardous situation occurs, it stops the vehicle and sends an email from the MSP432P401R microcontroller to the Fire Safety Department with the fire alert message, which has the exact location, date, and time and shares the Google Map link.

## Hardware Components
1) OLED Display (128 x 64)
2) ESP8266 Wifi module
3) NEO6M GPS sensor
4) KY026 flame sensor
5) l293D motor Driver
6) ARM Cortex M4F MSP432P401R development board

## Hardware Block Diagram
![image](https://user-images.githubusercontent.com/112504087/211223395-375a48b6-4555-48d5-93fe-3e615ead3347.png)

## Firmware Design
![image](https://user-images.githubusercontent.com/112504087/211223424-a56826b5-ea7a-439d-85ca-584070a06d6c.png)

## Firmware Specifications for the MSP432P401R
> The MCU shall be able to initialize the I2C bus for the OLED.
>> Interface info: oled_init()

> The MCU shall be able to initialize the UART for the GPS module.
>> Interface info: uart0_init(),uart2_init()

> The MCU shall be able to initialize the Clock Select CS Module
>> Interface info: CS_Config()

> The MCU shall be able to initiate the PWM signals for the MOTOR CONTROL.
>> Interface info: pwm_init()

> The MCU (MSP432) must be able to initialize and read the Flame sensor digital out value with the GPIO pin.
>> Interface info: init_ir_sensor(), read operation: (P2->IN & 0x10) 10

> The MCU must be able to detect the changes in the flame sensor value with the GPIO peripherals.
>> read operation: (P2->IN & 0x10) == 0x10 → Flame detected

> The MCU must Continuously monitor the GPIO pin connected to the Flame sensor.

> The MCU shall then detect the GPS module input received through the UART Channel2 when a flame is detected. Polling until EUSCI_A2->IFG & EUSCI_A_IFG_RXIFG receive is generated

> THE MCU shall then Check if the Input received through the UART is a '$' character
>> Polling until EUSCI_A2->RXBUF != '$'
>> Note: The strings received from the GPS module start a new line with '$'

> The MCU shall then poll for the '\r' which indicates the completion of the string.
>>Store Char until recd_rxchar != '\r'

> the MCU should Convert the string NEMA format into tokens.
>>Function used for tokenization : process_command(str_gpsdata,argv);

> The MCU should then Check if the NEMA string starts with GPRMC
>> Condition: strcasecmp(argv[0],gprmc_str) == 0

> The MCU shall be able to store the latitude and longitude coordinates in a buffer

>  THE MCU shall be able to store 'TEXT_ARR' with each line to be displayed on the OLED

> The MCU shall display the following message in case of a fire alert

1. Dashboard
2. FIRE ALERT
3. Lat: xxxxxxxxN (x indicates coordinates here)
4. Lo: xxxxxxxxxw (x indicates coordinates here)

> The MCU shall be able to store the 'LOGO_ARR' with each unique logo.

> The MCU shall display the Alert Logo on the OLED and switch back to TEXT_ARR, this sequence shall be persistent when the flame is continuously present

> The MCU shall be able to gradually reduce the PWM of the Motor eventually stopping the Motor.
>> Interface Info: stop_motor()
>> INFO: the Intention of reducing the PWM of the motor is to reduce the speed of

> The vehicle and bring the vehicle to safely drive in case of the fire

> The MCU shall not poll for the GPS signal in the DRIVE MODE when no fire is detected

> The MCU shall be able to gradually increase the PWM of the Motor eventually driving the Motor at its max capacity.
>>Interface Info: start_motor()
>> INFO: the Intention of increasing the PWM of the motor is to increase the speed of the vehicle when no alert is detected

> THE MCU shall display the following message in case of DRIVE mode
1. Dashboard
2. DRIVE MODE

## Testing Process
### Test Case no: TC_01_00
Test Area: Normal Mode after powering on

Test Criteria: Equivalence Test (Happy case)

Test procedure:
1. Turn on the MCU
2. flame is not detected
3. Observe the OLED display and Motor

Test Expectation:
1. The motor shall gradually increase its speeds 
2. OLED shall Display
	1. DASHBOARD
	2. DRIVE MODE

### Test Case no: TC_02_00
Test Area: Fire alert mode after power on

Test Criteria: Equivalence Test (Happy case)

Test procedure:

1. Turn on the MCU
2. flame is detected
3. Observe the OLED display and Motor

Test Expectation:

1. The motor shall gradually reduce its speeds and stop eventually
2. OLED shall periodically Display the following message
	1. DASHBOARD	
	2. FIRE ALERT
	3. LAT: 4000.5684N
	4. LON: 5000.7283W
	5. ALERT symbol on the top left corner of the OLED

### Test Case no: TC_03_00
Test Area: Normal Mode, fire alert and recovery

Test Criteria: Boundary condition

Test procedure:

1. Turn on the MCU
2. flame is not detected
3. Observe the OLED display and Motor
4. flame is detected
5. Observe the OLED display and Motor
6. flame is not detected
7. Observe the OLED display and Motor

Test Expectation:

1. At step 3, The motor shall gradually increase its speeds
2. OLED shall Display
	1. DASHBOARD
	2. DRIVE MODE
3. At step 5, OLED shall periodically Display the following message
	1. DASHBOARD
	2. FIRE ALERT
	3. LAT: 4000.5684N
	4. LON: 5000.7283W
	5. ALERT symbol on the top left corner of the OLED
4. At step 7, The motor shall gradually increase its speeds
5. OLED shall Display
	1. DASHBOARD
	2. DRIVE MODE


## Result and Error Analysis
NEO6M GPS data extraction:
1. NEMA Msg format received through the UART was decoded by storing the string information.
2. The Stringified message was then decoded to obtain the latitude and longitude information.
3. I have used the string token from the GPRMC, as you can see in the below figure the Latitude information displayed is 4000.47682 N and 10515.80136 W.
4. The Latitude information is in the Format DDMM.MMMM (DD: degree, MM:Minutes) and the same is the case with the longitude.

![image](https://user-images.githubusercontent.com/112504087/211224164-14a07f9e-9293-4657-8742-818b5cbe9e74.png)


Write and Read operation in I2C for OLED Display :
The below figure shows the testing of the OLED display where the address is directly
written to i2c by commands and tested whether character is displaced and also verified
using Logic Port. The data written to the memory where 58A is the given address by the
user which contains the page block address and word address. The figure 18 , clearly
shows the page block as 5 and the word address as 8A. Data written to the memory is
‘A’.

![image](https://user-images.githubusercontent.com/112504087/211224235-6d6f21b5-c893-4155-9fde-0f22fbeee4c9.png)

After the start operation, it contains an 8 bit slave address, acknowledgement is
received from the slave after every 8 bits. then word address along with that data and at
last once the transmission is done slave receives the stop bit

![image](https://user-images.githubusercontent.com/112504087/211224253-5da30fee-c5f6-4d95-b8a2-58b518204579.png)


![image](https://user-images.githubusercontent.com/112504087/211224292-3edad554-5571-4f9d-9728-43ef2e080a00.png)




