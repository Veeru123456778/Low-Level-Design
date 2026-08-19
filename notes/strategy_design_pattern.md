## Inheritance has certain problems:

1. Code Reuse
2. To add new feature a lot of code is required
3. Breaking Open Close Principle

## Strategy Design Pattern

To ye kisi bhi permutation / combination ko support kar skta h

We need to favour composition over inheritance, inheritance can be very messy, so we need to use composition.

For ex: we have robots that may be walkable, talkable, flyable.
So some robots may be flyable , some may not be flyable, so it is better to use composition so that we can change the behaviour at runtime.

Robot Class - This is Client Class (Ab hm isme bhi bna skte h classes jo inherit kre like CompanionRobot and )

    Talkable t; // Composition
    Walkable w;
    Flyable f;

## These are strategies:

Talkable Class - 
    talk()    // abstract class (interface) and multiple behaviours can be there     (noTalk() and normalTalk())

Walkable Class - 
    walk()   // abstract class (interface) and multiple behaviours can be there     (noWalk() and normalWalk())

Flyable Class  - 
    fly()   // abstract class (interface) and multiple behaviours classes implements these inerface can be there (normalFly() and jetFly())

## Notes: Strategy Design Pattern (Key Points)

Definition: Strategy pattern defines a family of algorithms, encapsulates each one, and makes them interchangeable at runtime.

## Problem it solves:

Applications evolve and need to support new features without changing existing code.
Separate "varying" behavior (algorithms) from the static parts of the system.
Core idea:

Identify behaviors that vary (e.g., talking, walking, flying).
Put each behavior into its own separate class (often via an interface or abstract class).
The client (context) holds references to these behavior objects and delegates work to them.

## Key components:

Strategy interface (e.g., TalkStrategy, WalkStrategy, FlyStrategy) that declares the method(s) to implement.

Concrete strategies that implement the interface (e.g., NormalTalk, NoTalk, NormalWalk, NoWalk, FlyWithWings, FlyWithJet).

Context (Client/Robot) that uses the strategies via composition (holds references to strategy instances and delegates calls).

## Benefits:

Favor composition over inheritance: change behavior by replacing strategy objects instead of extending classes.

Open/Closed Principle: software is open for extension (new strategies) but closed for modification (existing code unchanged).

Run-time flexibility: can switch strategies at runtime to alter behavior.

Reduces the need for deep inheritance trees; avoids brittle hierarchies.
Implementation approach:

Extract changing parts (e.g., talk, walk, fly) into separate interfaces and concrete classes.

In the main object, hold references to these interfaces (composition).
Provide constructors or setters to assign different strategies.
Call the appropriate delegate methods on the strategy objects.
Example storyline (robot simulation):

Base Robot has behaviors: Talk, Walk, Proj (Projection).
Create interfaces: TalkBehavior, WalkBehavior, ProjectionBehavior.
Implement concrete strategies: NormalTalk, NoTalk; NormalWalk, NoWalk; ProjectionNormal, ProjectionJet, etc.
Use composition: Robot has fields of type TalkBehavior, WalkBehavior, ProjectionBehavior.
At runtime, swap behaviors to create new robot variants without changing Robot’s code.

## Practical patterns in action:

If new behavior variants arrive (e.g., new flying method), add a new concrete strategy instead of altering existing classes.
To support “washable” combinations, create multiple concrete strategies and assign them dynamically.
Comparison with inheritance:

Inheritance can lead to a “strange loop” of combinations and brittle trees as features vary.
Strategy avoids this by encapsulating each variation and combining at runtime.
Related principles:

DRY: reduce duplication by delegating to shared strategy implementations.
Polymorphism: client code works with interfaces/abstract classes, not concrete implementations.
Open/Closed: extend with new strategies, not modify existing robot class.
Common pitfalls:

Overusing interfaces; keep strategies cohesive and small.
Not decoupling enough (the context should not expose internal strategy details).
If multiple strategies need to coordinate, ensure proper interaction patterns between them.
Real-world takeaways:

Strategy is widely used for flexible payment methods, sorting algorithms, and general feature pluggability.
When designing, think about which parts of your code are likely to change and encapsulate them as separate strategies.
Minimal recap: Define a family of interchangeable algorithms, extract them into separate classes, compose them in the host object, and switch at runtime to adapt behavior without modifying existing code.