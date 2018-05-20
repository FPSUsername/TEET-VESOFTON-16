# TEET-VESOFTON-16
Development board: [STM32F407VG](http://www.st.com/en/microcontrollers/stm32f407vg.html)
VGA output API

[![Waffle.io - Columns and their card count](https://badge.waffle.io/FPSUsername/TEET-VESOFTON-16.svg?columns=all)](https://waffle.io/FPSUsername/TEET-VESOFTON-16)

## **Features:**
### *Draw:*
  - ~~Line~~
  - ~~Arrow~~
  - Ellipse _(filled)_
  - Rectangular _(line/filled)_
  - ~~Triangle~~
  - Single character
  - Text _(Latin and Greek)_
  - Bitmaps
- Clearscreen
- Delay

## **Usage:**
Terminal baud rate: `115200`

Data string format: `function, param1, param2, paramN`

## **Example:**
```
bitmap, 0, 50, 50, 1
tekst, 10, 10, the quick brown fox jumps over the lazy dog, wit, norm
lijn, 1, 1, 100, 100, rood
```

## **Todo:**
- [ ] Line
- [ ] Arrow
- [ ] Triangle
- [ ] Font styles
