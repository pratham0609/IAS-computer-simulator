# IAS-computer-simulator
Implemented the IAS computer (fetch the  instruction, decode and  execute)

IAS Computer :
In the function fetch,opcode of the next instruction is loaded in the IR and address in MAR, while left instruction waits in IBR.
Here, first Load is carried out, then next no. is subtracted, then after completion, we jump to the other half of instruction,
and load the no. presnt in accumulator and carry out rsh ( divide it by 2 ) and store it and halt the process.
