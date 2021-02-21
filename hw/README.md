Hardware realization
====================
I have not actually tried to implement any circuits yet, but I have some thoughts on what the HW designs might look like.

1. The classic diode AND and OR gates are actually MIN and MAX gates, respectively in the analog domain
2. The classic CMOS push pull design could be used with both transistors off to allow for a third state. Maybe the output float connected to a pull up, down or to ground resistor.
3. Need to pick a voltage range to test at. 5V power supplies are pretty ubiquitous, and +5V, 0, -5V would feel very classic. Though splitting the 5V to +5, +2.5, 0V has certain practicalities. I'm currently leaning toward +3V, 0, -3V, with the valid ranges targeted at +5V...+2V, +1V...-1V, -2V...-5V. This couldhelp with compatibility with some existing 5 and 3.3 volt devices.
4. Need to pick a functionally complete set of gates to implement.


Links
-----
- <https://en.wikipedia.org/wiki/CMOS>
- <https://en.wikipedia.org/wiki/Setun>
- <https://en.wikipedia.org/wiki/Ternac>
- <https://en.wikipedia.org/wiki/Ternary_signal>
- <https://en.wikipedia.org/wiki/Diode_logic>

