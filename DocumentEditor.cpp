// #include<bits/stdc++.h>
// using namespace std;

// class DocumentEditor{
//   vector<string> documentElements;
//   string renderedDocument;
//   public:
//   void addText(string text){
//     documentElements.push_back(text);
//   }
//   void addImage(string path){
//     documentElements.push_back(path);
//   }

//   string renderDocument(){
//      if(renderedDocument.empty()){
//           string result = "";
//           for(string element:documentElements){
//              if(element.size()>4 && (element.substr(element.size()-4))==".jpg" || (element.substr(element.size()-4)==".png")){
//                 result += "[Image: "+element+"]"+"\n";
//              }
//              else{
//                 result += element+"\n";
//              }
//           }
//         renderedDocument = result;

//      }
//      return renderedDocument;
//   } 

//   void saveToFile(){
//     ofstream file("document.txt");
//     if(file.is_open()){
//        file<<renderDocument();
//        file.close();
//        cout<<"Document saved in document.txt successfully!!"<<endl;
//     }
//     else{
//         cout<<"Error: Unable to open file for writing."<<endl;
//     }
//   }
// };

#include<bits/stdc++.h>
using namespace std;

class DocumentElement{
   public:
   virtual string render() = 0;
};

class DocumentRenderer{
    Document* doc;
    public:
    DocumentRenderer(Document* d){
      doc = d;
    }
    vector<DocumentElement*> documentElements = doc->getElements();

    string render(){
      string result = "";
      for(auto& element:documentElements){
        result += element->render();
      }
      return result;
    }

};

class Document{
   vector<DocumentElement*> documentElements;

   public:
   
   void addElement(DocumentElement* element){
     documentElements.push_back(element);
   }

   vector<DocumentElement*> getElements(){
      return documentElements;
   }
   // string render(){
   //    string result = "";
   //    for(auto& element:documentElements){
   //      result += element->render();
   //    }
   //    return result;
   // }
};


class TextElement:public DocumentElement{
   string text;
   public:
   TextElement(string t){
      this->text = t;
   }
   string render() override{
      return text;
   }
};

class ImageElement:public DocumentElement{
   string imgPath;
   public:
   ImageElement(string path){
      imgPath = path; 
   }
   string render() override{
       return "[Image: "+imgPath+"]";
   }
};


class NewLineElement:public DocumentElement{
   public:
   string render() override{
      return "\n";
   }
};

class TabSpaceElement:public DocumentElement{
   public:
   string render() override{
      return "\t"; 
   }
};

class Persistence{
    public:
    virtual void save(string content) = 0;
};

class FileStorage: public Persistence{
  public:
  void save(string content) override{
    ofstream file("document.txt");
    if(file.is_open()){
       file<<content;
       file.close();
       cout<<"Document saved in file successfully!!"<<endl;
    }
    else{
      cout<<"Error: Upable to open file for writing."<<endl;
    }
  }
};

class DBStorage:public Persistence{
  public:
  void save(string content) override{
     cout<<"Content saved to db successfully: "<<content<<endl;
  }
};



class DocumentEditor{
  Document* doc;
//   Persistence* storage;
//   string renderedDocument;
  public:
  DocumentEditor(Document* d,Persistence* store){
   doc = d;
   // storage = store;
  }
  void addText(string text){
     doc->addElement(new TextElement(text));
  }
  void addImage(string path){
     doc->addElement(new ImageElement(path));
  }
  void addNewLine(){
   doc->addElement(new NewLineElement());
  }
  void addTabSpace(){
   doc->addElement(new TabSpaceElement());
  }

//   string renederDocument(){
//      if(renderedDocument.empty()){
//        renderedDocument = doc->render();
//      }
//      return renderedDocument;
//   }

   // void saveDocument(){
   //    storage->save(renederDocument());
   // }

};

int main(){
   Document* d = new Document();
   Persistence* p = new FileStorage();
   DocumentEditor* user = new DocumentEditor(d,p);
   Docume
   user->addText("Hi i am Varun");
   user->addTabSpace();
   user->addNewLine();
   user->addImage("./profile.jpg");

   p->save();
   // user->saveDocument();
   // Document* d2 = new Document();
   // Persistence* p2 = new DBStorage();
   // DocumentEditor* user2 = new DocumentEditor(d2,p2);
   // user2->addText("Hi there this is the second user!!");
   // user2->addNewLine();
   // user2->addImage("./user2-profile.jpg");
   // user2->saveDocument();
}


//Problem is that DocumentEditor class need to know about the Classes type like Persistence(FileStorage/DBStorage) or document need to know about the types and all