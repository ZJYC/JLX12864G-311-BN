
# brief introduction #

One day,My boss gave me a LCD module which named "JLX12864G-311-BN" and asked me to write a driver. According to the document "12864液晶资料-JLX12864G-330-BN中文说明书.pdf" I write a simple driver for it,In the end I added a memory block,Every operation was done to the memory,We just "synchronize"it to module.I think this way is more faster and convenient.

Because the LCD module only has two colors which were black and white,We could use a bit to represent a pixel,My LCD is 128*64 so we need [128/8]*[64/8] = 128 Bytes,Here we need two functions--Input and Output for this memory block.The input function write data into the memory block and the output function synchronize the memory block to the LCD moudle.

# some API #

    LCD12864_Init()

This function was used to init GPIO register and LCD register.This is the first step.


    LCD12864RamWrite(uint16_t X_Start,uint16_t X_End,uint16_t Y_Start,uint16_t Y_End,uint8_t * Buff,uint8_t Set)

This function is the INPUT function for memory block.
The LCD is 128*64:
X_Start:(1~64)
X_End:(1~64)
Y_Start:(1~128)
Y_End:(1~128)
Buff:The data to write in
Set:

LCD12864_SET		(1 << 0)//set the correspond pixel to 1 "A black dot"

LCD12864_CLR		(1 << 1)//clear the correspond pixel to 0 

LCD12864_REVERSE	(1 << 2)//Contrary to LCD12864_NORMAL

LCD12864_NORMAL		(1 << 3)//write '1' mean black while '0' mean clear

    LCD12864Sync()

synchronize the data to LCD module.
