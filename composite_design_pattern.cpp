// jO Bhi real problem jise ham hierarchical tree ki form m represent kar skte h vha composite design pattern lag skta h
// Ex: Designing a folder system...
// Composite design pattern composes objects into tree like structure representing a part- whole hierarchy (Ek leaf node and ek composite class hogi(like Folder) jo ki Components ki list maintain kregi ) . It let client treats individual object and composition of object uniformly (Client keval Component class se baat krega aur use mtlb ni Leaf or Composite class se)....

// Ex: Component -> FileSystemItem 
// Leaf -> File(We can not expand file furthur so this is the leaf)
// Composite -> Folder(where we can expand it further and it can have many files and folders in it. And it has (has-a) and (is-a) both relationships with the Component(FileSystemItem) because it also need to maintain a list of files and folders so has (1....*) 1 to many realtion with Component)

// Use cases:
// Any problem that contains tree like structure -> Ex: File System, Frontend Dropdown list (Ex: Menu of Restaurant and it has many options and then somewhere in tree we have leaf also)....


#include<bits/stdc++.h>
using namespace std;


class FileSystemItem{
   public:

   virtual void openAll(int indent = 0) = 0;
   virtual int getSize() = 0;
   virtual FileSystemItem* cd(const string& name) = 0;
   virtual string getName() = 0;
   virtual void ls(int indent=0) = 0;
   virtual bool isFolder() = 0; 
   virtual void createFile(FileSystemItem* file) = 0;
   virtual ~FileSystemItem(){}
};

class File: public FileSystemItem{
   private:
   string name;
   int size;
   public:
   File(string n,int s){
    name = n;
    size = s;
   }

   void ls(int indent) override{
      cout<<string(indent,' ')<<name<<endl;
   }

   void openAll(int indent = 0) override{
       cout<<string(indent,' ')<<name<<endl;
   }

   int getSize() override{
    return size;
   }
   string getName() override{
    return name;
   }
   bool isFolder(){
    return false;
   }
   
   FileSystemItem* cd(const string& name){
      cout<<"File can not show cd command"<<endl;
      return nullptr;
   }
   void createFile(FileSystemItem* file){
      cout<<"File can not create file."<<endl;
   }
};


class Folder: public FileSystemItem{
  private:
  vector<FileSystemItem*> contentList;
  string name;
  int size ;
  public:
  Folder(string n,int s){
     name = n;
     size = s;
  }

  void createFile(FileSystemItem* file){
     contentList.push_back(file);
  }

  string getName(){
    return name;
  }
  int getSize(){
    return size;
  }

  void ls(int indent = 0){
     cout<<name<<endl;
     for(auto folderItem:contentList){
          string itemName = folderItem->getName();
          if(folderItem->isFolder()){
          cout<<"+"<<itemName<<endl;
          }
          else{
            cout<<"-"<<itemName<<endl;
          }
      }
  }

  void openAll(int indent = 0){
      string result = "";
      for(auto folderItem:contentList){
        folderItem->openAll();
      }
      return;
  }

  FileSystemItem* cd(const string& name){
    for(auto item: contentList){
        if(item->getName()==name){
            return item;
        }
    }
    cout<<"Folder with name: "<<name<<" does not exist in current directory."<<endl;
    return nullptr;
  }

  bool isFolder(){
    return true;
  }
};


int main(){
   FileSystemItem* file = new File("file1.txt",20);
   FileSystemItem* folder = new Folder("folder1",100);
   folder->createFile(file);
   cout<<"LS Command: "<<endl;
   folder->ls();
   cout<<"Open All Command: "<<endl;
   folder->openAll();
}