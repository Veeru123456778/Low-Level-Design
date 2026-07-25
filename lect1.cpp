#include<bits/stdc++.h>
using namespace std;

class Product{
    private:
    int price;
    string name;
    public:
    Product(int p,string n){
        price = p;
        name = n;
    }
    int getProdPrice(){
        return price;
    }
};

class ShoppingCart{
    vector<Product*> products;
    public:
    ShoppingCart(){
        
    }

    void addProduct(Product* p){
        products.push_back(p);
    }

    void printTotalPrice(){
        int total = 0;
        for(auto& p:products){
            total += p->getProdPrice();
        }
        cout<<"Your total Price equals to: "<<total<<endl;
    }
};


class InvoicePrint{
    ShoppingCart* cart;
    public:
    InvoicePrint(ShoppingCart* c){
     this->cart = c;
    }
    void printInvoice(){
        cout<<"Your total amount bill is: "<<endl;
        cart->printTotalPrice();
    }
};

class DBPersistence{
    public:
    virtual void saveToDB()=0;
};

class SaveToDBSQL: public DBPersistence{
    ShoppingCart* cart;
    public:
    SaveToDBSQL(ShoppingCart* c){
        this->cart = c;
    }

    void saveToDB() override{
        cout<<"All Items Saved to DB SQL Successfully"<<endl;
    }
};

class SaveToDBMongoDB: public DBPersistence{
    ShoppingCart* cart;
    public:
    SaveToDBMongoDB(ShoppingCart* c){
        this->cart = c;
    }

    void saveToDB() override{
        cout<<"All Items Saved to DB MongoDB Successfully"<<endl;
    }
};



int main(){
   ShoppingCart* cart = new ShoppingCart();
   Product* p1 = new Product(100,"Bag");
   Product* p2 = new Product(200,"Shoes");
   Product* p3 = new Product(300,"Phone");
   cart->addProduct(p1);
   cart->addProduct(p2);
   cart->addProduct(p3);

   cart->printTotalPrice();

   InvoicePrint* inv = new InvoicePrint(cart);
   inv->printInvoice();
   
   int x;
    cout<<"Print 0 to exit and 1 to save the cart in DB!!"<<endl;

    cin>>x;
    if(x==1){
        DBPersistence* dbSaveSQL = new SaveToDBSQL(cart);
        DBPersistence* dbSaveMongo = new SaveToDBMongoDB(cart);
        dbSaveSQL->saveToDB();
        dbSaveMongo->saveToDB();
    }
}  