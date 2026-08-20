## Decorator Pattern:

Decorator Pattern attaches additional responsibilities to an object dynamically. Decorator provides a flexible alternative to subclassing for extending functionality.

Matlab decorator pattern is like recursion hm object ke constructor me object bnate rhenge and then wo base output ko decorate krta rhega with wrappers

Ex: Hmare pass character h ek class
 
                            is a (inheritance)
Character Class (abstract) <|--------- Decorator Class (abstract)
 getAbility()                           |                  |
    |                     <-----------  |                  |
    | inheritance           has a          AbilityWithGun    AbilityWithHeight
                         (composition)
Mario Class                                getAbility()     getAbility()     
getAbility()     

So decorator class has inheritance as well as composition relationship.

All will be having the getAbility method and they can decorate it in order

Ex: Character * mario = new Mario()
ch = AbilityWithGun(mario) 
ch->getAbility()         // I can do this now firstly mario getAbility method gets called (we will have that logic in AbilityWithGun's getAbility method) it will return something then it will just add its text (for ex: with gun) on top of what gets returned by the mario get ability.


Another example can be Instead of Character we have Text and in that Text we can apply operations like bold, underline (these are concrete classes of decorator)

Another example is we have a form filled by a user and now we need to have different validation layers into it such as email validation, phone validation etc.
So we can think these as decorators