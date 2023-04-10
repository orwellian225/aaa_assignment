# Advanced Analysis of Algorithms Assignment

## Data

A set of rectangles in a 2D environment.

### Generation

1. Create a rectangle at origin (0,0) with random dimensions
2. Select a random rectangle that already exists
3. Create a new rectangle constrained to be right side adjacent to the selected rectangle
4. Check if the newly created rectangle overlaps with any other rectangles
    1. If the new rectangle overlaps, go to step 2 without incrementing the number of rectangles counter
    2. If the new rectangle doesn't overlap
        1. Save the rectangle
        2. Increment rectangle counter
5. If the desired number of rectangles has be created then stop, else go to step 2

## Algorithm

### Brute force / Naive

1. Sort the list of rectangles ordering by the rectangles left x value, increasing 
2. Iterate through each rectangle as rect1
3. Iterate through each rectangle that occurs after rect1 as rect2
4. if rect2 is adjacent to rect1's right side, then add rect2 to rect1's adjacencies
