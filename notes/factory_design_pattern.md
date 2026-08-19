## Factory Design Pattern:

notes\images\simple_factory.png

# Simple Factory:

A simple factory class is a class that decides which concrete class to be made.
Isme ek hi factory hogi ho hold kregi ek Product or Factory me conditional logic hoga ki product ki konsi concrete class implement krni h.

# Factory Method:

In this there can be more than 1 factory making different types of a product (But product is 1) for ex: one factory is making normal burgers while other is making wheat burgur

# Abstract Factory Mathod:

In this there may be more than 1 product exists and multiple factory responsible for making all types of products that are there.


Real Example where factory pattern may get used:

Notification system - suppose factory class gets a type and based on that it return different notification system like SMS, Email, Push