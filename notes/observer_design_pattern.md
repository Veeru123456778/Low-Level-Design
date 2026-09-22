## Observer Design Pattern

Observable Class like youtube channel

Multiple Observers - Subscribers

So we have the interfaces of Observable and Observer and then we have the concrete classes of these Observalble and have methods of subscribe, unsubscribe, notify() upload() so when video gets uploaded then we internally call the notify to notify all the Observers that are there and have subscribed to the Observable.

So Concrete Observable will hold a list of all the observers which has subscribed to the method.

Use cases of observer design pattern are:

1. Notification Service

2. Event Handling (When multiple consumers needs to read the events when they got fired)

