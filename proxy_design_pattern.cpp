// In this suppose we have a receiver and a user and user sends request to reciever to access the resource now we dont want that user directly communicate with the resource and we need someone in between that checks and validate user request:
// Like we can use a proxy Object in between that does:
// Uses: Authenticate the user , Perform checks on request like data validation and all and if resource is on other server(over the internet) then proxy will maintain connection with that server(through the internet) and gives the response to the user
// user -------> proxy --------> Resource
// user <------- proxy <-------- Resource
// Proxy resource ki treh hi act krti h to user ko pta hi nhi chlta ki user proxy ko request bhej rha h ya resource ko....So Proxy and Resource indifferentiable for user....
// Proxy hogi aur uska ek resource hoga or proxy resource ki representative hogi....
// Type: Virtual, Protection and Remote

// Virtual Proxy: Kisi bhi expensive resource ko protect krna h through proxy then we use Virtual proxy like we have an Image Display class which display the image and it also applies varius agorithms (like image compression , And cleaning) so we dont want to create ImageDisplay object directly so we have to make a Virtual Proxy i.e. ImageProxy class and then we need to inherit it also and we need to make a composition relation also with the IImageDisplay class(abstract class) so that it can also have behavioural properties through inheritence and also can call its methods (through composition) 
// Now when user call display method in proxy the it will assign the object to its refernce (It will create object only when display method got called because as it is an expensive operation...)


// Protection Proxy: To provide restriction on premium features 

#include<bits/stdc++.h>
using namespace std;

int main(){
    
}