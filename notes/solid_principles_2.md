## SOLID Design Principles

# Interface Segregation Principle

It is better to have multiple client facing interfaces rather than having all methods in one interface because many classes that will implement the interface does not need all methods but if they implement interface then they need to define all methods of interfaces.
Ex: For 2D shapes we will have only Area
    For 3D shapes we will have volume and area both

# Dependency Inversion Principle

High level module should not depend on low level module rather they both should depend on abstraction

High level Module : Like business logic Application layer
Low level Module : Like jo kisi system se interact kre like databases (sql, mongo) ya file system

To agar hme different db's (sql,mongo db) me data save krana h to hm interface ke through in dono classes ko bnayenge jisse application uss interface se interact kre or instance ka method call hojaye like strategy principle.