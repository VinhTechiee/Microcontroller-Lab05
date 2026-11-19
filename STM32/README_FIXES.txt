Lab 5 UART - patched source
===========================

Fixes included
--------------
1. ADC retransmission:
   ADC is sampled once when !RST# is accepted. If !OK# is not received
   within 3 seconds, the same stored ADC_value is retransmitted.

2. Command parser:
   !RST# and !OK# are accepted immediately when '#' arrives.
   Enter/CR/LF after '#' is not required.

3. UART receive buffer:
   Replaced the shared index with a 30-byte ring buffer. One slot is
   reserved to distinguish full from empty, so 29 bytes can be queued.
   If full, the newest byte is dropped; unread data is not overwritten
   and there is no out-of-bounds write.

4. volatile:
   Ring-buffer data/head/tail and software-timer flag/counter are volatile
   because they are shared between interrupt and main contexts.
   isRST/isOK remain non-volatile because they are only used in main
   execution context.

Build and Proteus
-----------------
1. Open the Lab5 project in STM32CubeIDE.
2. Run Project > Clean, then Build Project.
3. The new firmware should be generated at Lab5/Debug/Lab5.hex.
4. Set the STM32 Program File in Proteus to this newly generated HEX.
5. Test:
   - Send !RST# without pressing Enter.
   - Confirm the terminal receives !ADC=...#
   - Wait more than 3 seconds without sending !OK#.
   - Confirm the same ADC number is retransmitted.
   - Send !OK# and confirm the transaction ends.

The old Debug build folder is excluded from this archive so an old HEX
cannot be mistaken for the patched firmware. Rebuild before simulation.
