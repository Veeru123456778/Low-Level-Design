## Create an Interface When:

# Multiple Implementations Exist: 

You expect different behaviors for the same actions (e.g., PaymentProcessor having StripeProcessor and PayPalProcessor).

# Using Third-Party Boundaries:
Isolating external dependencies or APIs (e.g., DatabaseRepository) so you can mock them out during unit testing.

So Repository can be an interface in which DatabaseRepository and MockDBRepository can be the concrete classes and we can use Mock for testing.

# Designing Plugins or Extensible Architectures:
You want consumers to provide custom logic that plugs into your system framework.

# Decoupling Modules: 
You want to protect Module A from knowing the implementation details of Module B, establishing a strict communication contract.


## Do NOT Create an Interface When:

The Class Has Only One Implementation: If there is no real-world scenario where a second variation of the class will exist, code directly to the concrete class.

The Class is a Simple Data Container: Value objects, Data Transfer Objects (DTOs), and domain entities (e.g., User, Product) do not have varying behaviors and never need interfaces.

The Logic is Internal and Stable: Internal utility helper classes or core private services that will not be swapped or mocked.

# What interfaces will have:

So interfaces will consisting the behaviours that will not get changed anytime and whatever the classes we have these will be having all those behaviours.
But if the behaviours will change (business logic) then we need to have that in the concrete class of a specific behaviour or business logic.
So separate what will get change and what will not.
Put not change into interfaces and put changing behaviour into concrete classes of that interfaces.


