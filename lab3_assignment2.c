// Assignment 2: BOX GAME
 
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

 int main(void)
  {
    volatile int*switchptr =(int*)0xFF200030; //What is the SW slider switch address for SW1?
    int switch_value;
    int temp_x1 = rand() %319; // x cordinate of one corner of our box1
    int temp_x2 = rand() %239; // x cordinate of one corner of our box2
    int temp_y1 = rand() %319; // y cordinate of one corner of our box1
    int temp_y2 = rand() %239; // y cordinate of one corner of our box2
    char text_row[50] = "Box 1 is RED and Box 2 is GREEN\0";
   
    //randomly place one corner of box and then extrapolate to create the full box
    box1 = VGA_box(temp_x1, temp_y1, temp_x1+49, temp_y1+49, 0xF800); // box 1 = temp_x1, temp_y1, temp_x1+49, temp_y1+49; displays red
    box2 = VGA_box(temp_x2, temp_y2, temp_x2+49, temp_y2+49, 0x07E0); // box 2 = temp_x2, temp_y2, temp_x2+49, temp_y2+49; displays green 
  
   VGA_text (0, 0, text_row);  
   
   // check to make sure that the boxes are not overlaping to beging with 
   // needs to be done after every time boxes are created
   if ( box1 and box2 overlap)
      generate new random numbers;

   //create legend of the color of box and corresponding number
   

   
    while(1)
    {
      switch_value=*(switchptr);
      
      if (switch_value = 8); // player has chosen to reset the game by selecting SW3
      // new game and box values
      // reset timer
      // clear any saved values
    
      else if (switch_value = 2); // switch 1 is on // SW1 = box 1 selected to move
      {
        // Timer should start and display time on displays
        
        int i;
        time_t t1,t2;

        (void) time(&t1); // start time
  
        for (i=1;i<=999;++i) printf("%d %d %d\n",i, i*i, i*i*i);
   
        (void) time(&t2); // end time 
   
        printf("\nTime= %d seconds\n", (int) t2-t1);
        
        //While this switch remains on only box 1 can be moved
        when (key = 1)
          move box right //+x direction 
        when (key = 2)
          move box left //-x direction
        When (key = 4)
          move box up //+y direction
        when (key = 8)
          move box down //-y direction
       }
      
      else if (switch_value = 1) // switch 0 is on //SW0 = box 2 selected to move
       {
        //Timer should also start here. 
        
        int i;
        time_t t1,t2;

        (void) time(&t1); // start time
  
        for (i=1;i<=999;++i) printf("%d %d %d\n",i, i*i, i*i*i);
   
        (void) time(&t2); // end time 
   
        printf("\nTime= %d seconds\n", (int) t2-t1);
        
        when (key = 1)
          move box right //+x direction 
        when (key = 2)
          move box left //-x direction
        when (key = 4)
          move box up //+y direction
        when (key = 8)
          move box down //-y direction
          
      //when they overlap for the first time the box that was selected needs to be moved back to where it originally was so that the second player can take their turn
      // If they overlap, save the time in time1 & time2
      when (x1 == x2 && y1 == y2) // the boxes are overlaping
          // Stop the timer and save the value 
          if (first_time)
          {
            if (switch_value = 1)
              move box 2 back to original position
              and return to start of else if (switch value == 1)
              display player one time
            if (switch_value = 2)
              move box 1 back to original position
              and return to start of else if (switch value == 2)
               display player one time
          }           
          else
             display player two time
            return 0;
      }
    }
   
    // Compare times
        //display time1 on HEX2 to HEX0
       //display time2 on HEX5 to HEX3
   
        if (time1>time2)
          player one wins, and LED5 to LED2 light up
        if (time2>time1)
          player two wins, and LED9 to LED6 light up 
        if (time1=time2,)
          there is a tie, and all LEDs light up
  }
