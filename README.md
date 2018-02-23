# UK-Pedestrian-Crossing
Arduino sketch replicating a UK pedestrian crossing

Why am I here?
==============

That's a big question, I know, but I'm referring to me being here making a big fuss about traffic lights. No quite as big a question, but still, a good one. It started a couple of days ago when I thought I'd introduce my 11 year old daughter to Arduino. "Traffic lights!" "What a great place to start with arduino!" "Junction lights are pretty complicated, let's start with a simple pedestrian crossing!". NO! PEDESTRIAN TRAFFIC LIGHTS ARE NOT SIMPLE!http://www.football-data.co.uk/englandm.php

Okay, my daughter quickly got bored of the coding side of things. I think she was a bit tired and it's not her main 'thing'. I didn't want to be pushy, but I was enjoying the project so I thought I'd continue it. Wow! What a headache! First off, you can't really use the delay() feature of the Arduino programming language (wiring?). This is because, while delay is running, you can't poll for button presses. Okay, technically, there are points where button presses don't need to be detected, but, if you're avoiding the use of delay() in part of the code, it only feels right to eliminate it. 

Do you remember the "Blink without delay" example that is packaged with the Arduino software? Remember trying to get your head around that? That's the route this project is taking.

Well, I did manage to get a decent prototype working. I shared it on an Arduino page on Facebook and got a bit of attention. Somebody requested the code which meant I had to tidy it up a bit (a lot) and find somewhere to share it. Somebody else questioned why I didn't just use delay() throughout and argued that it could be done (absoulutely nothing wrong with somebody asking these questions and arguing their point!). Ultimately, GitHub seems to be a great place to share the code and, if anybody wants to improve it or create a branch, it's perfect for that too.

What is a UK Pedestrian Crossing?
=================================

A basic UK pedestrian crossing consists of four sets of traffic lights, two sets of pedestrian lights, two wait lights and two buttons.

The traffic light sets have a red light, an amber light and a green light. Two sets face one direction and two sets face the other.
The pedestrian light sets have a green man light and a red light. Each set faces the opposite side of the road.
At each side of the road, for pedestrians, there is a wait light and a button.

If nobody is waiting to cross, the traffic lights are green, the pedestrian red man is on and the wait light is off. In this code example, this is the default status.

If somebody presses a button, the wait lights come on. After a set amount of time the green lights go off and the amber traffic lights come on to warn drivers that the red lights are about to come on. After the amber traffic lights have been on for a set amount of time they go off and the red lights come on. After a set delay, for safety, the green man lights come on advising the public that it is safe to cross. The wait light goes off.

After the green man lights have been on for a set amount of time they start to flash to warn that it is only safe to cross if you have started crossing. From this point, it is possible for pedestrians to press the button again, triggering the wait light to come on and th eprocess to start again once some traffic has passed.

After the green man lights have finished flashing they go off and the red man lights come on. A set amount of time after that the red traffic lights go off and the amber traffic lights flash to indicate to drivers that they can go if it is safe to do so. After a set amount of time the amber traffic lights start flashing and the green traffic lights come on.

Can the code be improved?
=========================

Absolutely!

I was quite happy to have what I thought would be working code within an hour of opening the Arduino sketch pad. After editing the 10th typo while trying to compile for the first time, I had an idea that it wasn't going to be so easy. 2-3 hours of debugging later I had some working code. Doing it this way came at a price though. I hade to implement a "stage" system. Throughout the code various "stages" are set. If conditions can only be true if the system stage is at a certain level. This gives a great level of control when all of your if statements are being tested on every cycle. However, this means that some of the existing test cases I had previously included are probably now redundant. You will see things like "redState = True". If you comment it out it'll cause problems, but, if you really wanted to I'm sure you could work purely off the stage system in some cases, saving unnecessary variables making the code easier to read.

Can the code be further developed?
==================================

Aside from the tidying options above, this code could be used as a basis for improving the current system. Various sensors, timing algorithms, extra lights, buzzers etc. could be added as a project or even to suggest a real life improvement of the current system.
