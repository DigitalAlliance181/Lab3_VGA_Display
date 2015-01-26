// Lab 3 Part IV Assignment 2
// BOX GAME for two players
// Chris Bird, Kaila Balacio, Lillie Deas

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
  

 int main(void)
  {
    volatile int*switchptr =(int*)0xFF200030; //What is the SW slider switch address for SW1?
    int switch_value;
    int temp_x1 = rand() %319; // x cordinate of one corner of our box1
    int temp_x2 = rand() %239; // x cordinate of one corner of our box2
    int temp_y1 = rand() %319; // y cordinate of one corner of our box1
    int temp_y2 = rand() %239; // y cordinate of one corner of our box2
   
    //randomly place one corner of box and then extrapolate to create the full box
    box1 = VGA_box(temp_x1, temp_y1, temp_x1+49, temp_y1+49); // box 1 = temp_x1, temp_y1, temp_x1+49, temp_y1+49;
    box2 = VGA_box(temp_x2, temp_y2, temp_x2+49, temp_y2+49); // box 2 = temp_x2, temp_y2, temp_x2+49, temp_y2+49;
  
    while(1)
    {
      switch_value=*(switchptr);

      if (switch_value = 2); // switch 1 is on // SW1 = box 1 selected to move
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
      
      if (switch_value = 1) // switch 0 is on //SW0 = box 2 selected to move
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
          if (first_time)
          {
            if (switch_value = 1)
              move box 2 back to original position
            if (switch_value = 2)
              move box 1 back to original position
          }           
          else
            return 0;
      }
    }
    // Compare times
        if (time1>time2)
          player one wins, and LED5 to LED2 light up
        if (time2>time1)
          player two wins, and LED9 to LED6 light up 
        if (time1=time2,)there is a tie, and all LEDs light up
  }
