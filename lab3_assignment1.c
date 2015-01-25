//This is fuckin cool isnt it

//Function to send a string of text to the VGA monitor
void VGA_text(int x, int y, char * text_ptr)
{
  int offset;
  
  //VGA char_buffer_slave location address - Base address is 0xC4004000 in Qsys
  volatile char * character_buffer = (char*)0xC4004000;
  
  //Note: Assumes all characters will fit on a single line
  offset = (y << 7) + x;
  while (*(text_ptr))
  {
      *(character_buffer + offset) = *(text_ptr); // write to the character buffer
      ++text_ptr;
      ++offset;
  }
}

// Function to draw a filled rectangle on the VGA monitor
void VGA_box (int x1, int y1, int x2, int y2, short pixel_color)
  {
  int offset, row, col;
  
  //VGA picel buffer location adress in On-Chip Memory Address in Qsys
  //Remeber Pixel DMA does not have embedded memory
  //VGA SDRAM location address - Base address is 0xC0000000 in Qsys
  volatile short * pixel_buffer = (short *) 0xC0000000;
  
  //Note: Assume that the box coordinates are valid on the screen
  //If cordinates are off the screen it is helpful to set cordinates within the screen
  //resolution
  //Each pixel value is represented as a 16-bit halfword, with five bits for the blue,
  //five bits for the red, and six bits for green.

  for (row = y1; row <= y2; ++row)
  {
    for (col = x1; col <= x2; ++col
    {
      offset = (row << 9) + col;
      *(pixel_buffer + offset) = pixel_color; // compute halfword address, set pixel color
    }
  }
}

void VGA_bounce (int x, int y, char * text_ptr)
{
  
// Create a loop that runs forever and checks wheather or not the  x and y values are close to the edge of the screen.
// Then based on if the x and y are at 0 or their upperbound either subtract or add to get them closer to the edge.
// We might wanna add to both x and y to move them in a more "natural" bouncing motion.

// Should we detect when we are close to an edge?  Turn around when we are 2 pixles away from the edge?

}

int main(void)
{
  /* create a message to be displayed on the VGA and LCD
  displays */
  char text_row[50] = "Digital Alliance\0"
  char text_bounce[50] = "Digital Swagga!" // Text that bounces around the screen 
  
  /* output text message in the middle of the VGA monitor */
  VGA_text (35, 29, text_row); // are the x and y values within the new square?
  VGA_bounce(?,?,text_bounce); // Create code to tell the  text to bounce.
  
  // Pixel Color is in Red_Green_Blue format - 0x0001.1_000.011_1.1111 = 0x1878
  //VGA_box (1*4-2, 28*4, 79*4+1, 32*4, 0xF800); // Display Pixel X:0 to 319, 16-Bit RGB
    // (x1=2, y1=112, x2=317, y2=128, color) and those are colums/rows to increment through, ahh  
    
 
  //code below will fill the whole screen with red, row 0:239 and colum 0:319
  VGA_box (0*4, 0*4, 80*4-1, 60*4-1,0xF800); //Fills whole screen with a red box? Will it override?
  
  //code below will create a green box in the center of the screen, row 109:129 and colum 149:169
  VGA_box (37*4+1, 27*4+1, 32*4+1, 32*4, 0x07E0); //Creates a green box in the center of the screen. It is not square.
  
  
  while(1); //What is this for? I think this is where we would put the bounce code 
  // how do we put the bounce code here?
  
  return 0;
}
