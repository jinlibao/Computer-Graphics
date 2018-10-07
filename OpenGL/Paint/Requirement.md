# COSC 5450-01 Computer Graphics Project 01

## Requirements

Out of 50 possible points. Due Sept 18, 2018 by 11:59pm.

* Purpose: is to understand how the event loop works and what role interactivity places a part with how the display functions.
* Overall: Create your very own paint program. Your project should have the following 5 elements:

1. (a) DRAW: Draw a continuous line with the mouse. When you click the mouse button (and hold) using the mouse it must continuously draw until mouse button is lifted without gaps in the line. Hint: Check that if you draw fast that there are not gaps between one movement to the next. (b) ERASE: Additionally you should be able to erase with the mouse.
2. Be able to change size of brush (at least 3 sizes), color of brush (at least 3 different colors), and have at least 3 options of filled paint shape {circular, square, triangle, polygon, etc.}. Hint: This is where parameterizing your code comes in handy! You can create your own shape (i.e. a stamp tool). Note: Continuous lines do not need to be drawn with your optional shapes- but 2 points extra bonus if you do!
3. As a part of your project, you must have a toolbar on the side where you have drawn shapes/icons (these can be very simple) and you have identified this ‘pick’ region to execute your code when the mouse clicks in this area. Note you do not have to create multiple viewports for your toolbar.
Attached is a picture of just one example of what your toolbar area might look like. You can create how you think would be best.
Additional Tasks for 5450:
4. Incorporate a delete tool which will use the mouse to identify a rectangular region and delete what was drawn
in that region. Hint: Your solution for 1b) should be similar except with use of glRect function.
5. Set up two viewports – one for the toolbar and one for the drawing area

You will be graded on elegance of code and the completion of implementation details for elements specified. Elegant code should include programming concepts and formation of classes and functions that you have learned in Data Structures and Algorithms course. Point values are distributed among the categories as follows
