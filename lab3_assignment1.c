int vSlope = 1; //Up is positive, down is negative
int hSlope = 1; //Right is positive, left is negative
int x = 5;
int y = 5;
char text_row[50] = "Digital Alliance\0";
char text_bounce[50] = "Digital Swagga!\0"; // Text that bounces around the screen

void VGA_text(int x, int y, char * text_ptr) //Function to send a string of text to the VGA monitor
{
  int offset;
  volatile char * character_buffer = (char*)0xC4004000;
  offset = (y << 7) + x; //Note: Assumes all characters will fit on a single line
  while (*(text_ptr))
  {
      *(character_buffer + offset) = *(text_ptr); // write to the character buffer
      ++text_ptr;
      ++offset;
  }
}

void VGA_box (int x1, int y1, int x2, int y2, short pixel_color)
  {
    int offset, row, col;
    volatile short * pixel_buffer = (short *) 0xC0000000;
    //Each pixel value is represented as a 16-bit halfword, with five bits for the blue,
    //five bits for the red, and six bits for green.

    for (row = y1; row <= y2; ++row)
    {
      for (col = x1; col <= x2; ++col)
      {
        offset = (row << 9) + col;
        *(pixel_buffer + offset) = pixel_color; // compute halfword address, set pixel color
      }
    }
}

void VGA_bounce (int x, int y) 
{
    printf("BEFORE; hSlope: %d --- vSlope: %d --- x: %d --- y: %d\n", hSlope, vSlope, x, y);
    if(x == 0 || x == 319)
      hSlope = (hSlope * -1); //change hSlope to positive or negative
     
    if(y == 0 || y == 239)
      vSlope = (vSlope * -1);

      
   if(vSlope > 0) //vSlope is positive
      y++;
   else if(vSlope < 0)
      y--;
      
  if(hSlope > 0) //hSlope is positive
      x++;
  else if(hSlope < 0) //hSlope is negative
      x--;
   printf("AFTER; hSlope: %d --- vSlope: %d --- x: %d --- y: %d\n", hSlope, vSlope, x, y);         
   VGA_text(x, y, text_bounce); 
}

int main(void)
{
  // create a message to be displayed on the VGA display  
  VGA_text (35, 29, text_row);
  
  // Pixel Color is in Red_Green_Blue format - 0x0001.1_000.011_1.1111 = 0x1878
  //VGA_box (1*4-2, 28*4, 79*4+1, 32*4, 0xF800); // Display Pixel X:0 to 319, 16-Bit RGB    
 
  VGA_box (0*4, 0*4, 80*4-1, 60*4-1,0xF800); //code below will fill the whole screen with red, row 0:239 and colum 0:319
  VGA_box (37*4+1, 27*4+1, 32*4+1, 32*4, 0x07E0); //code below will create a green box in the center of the screen, row 109:129 and colum 149:169
  
  
  while(1)
  {
   VGA_bounce(x, y); 
  }
  
  
  return 0;
}
