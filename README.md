# stm32-boiler

## Overview
The STM32 is controlling a heater to maintain setpoint temperature which the user can set using an IR remote. Set temperature
is displayed on 7-segment display, LEDs indicate whether the heater is ON or OFF.
RPI receives data via UART to visualize the system state, set temperature and actual temperature using Grafana.

## Hardware
- STM32L476RGTX
- Raspberry Pi 4 B
- ds18b20 temperature sensor
- relay module with opto-isolation
- 7-segment display
- IR Pilot
- Infrared Receiver Module

## Architecture
STM32 → UART → Python → MQTT → Grafana

## Technologies
- STM32 + HAL
- Python 3
- MQTT (Mosquitto)
- Grafana
