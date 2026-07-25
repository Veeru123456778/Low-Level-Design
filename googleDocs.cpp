#include<bits/stdc++.h>
using namespace std;

class DocumentElement{
   public:
   virtual string render() = 0;
};

class Document{
   vector<DocumentElement*> documentElements;
   public:
   void addElement(DocumentElement* docElement){
      documentElements.push_back(docElement);
   }
   vector<DocumentElement*> getDocumentElements(){
      return documentElements;
   }
};



class DocumentRenderer{
  Document* doc;
  public:
  DocumentRenderer(Document* d){
      doc = d;
  }

  string render(){
   vector<DocumentElement*> docElements = doc->getDocumentElements();

   string result = "";
   for(auto& d:docElements){
      result+=d->render();
   }
   return result;
  }

};

class DocumentEditor{
   Document* doc;
//    DocumentRenderer* docRender;
   string renderedDocument;
   public:
//    DocumentEditor(Document* d,DocumentRenderer* dR){
   DocumentEditor(Document* d){
      doc = d;
    //   docRender = dR;
   }
   void addElement(DocumentElement* dElement){
      doc->addElement(dElement);
   }
//    string render(){
//      if(renderedDocument.empty()){
//         renderedDocument = docRender->render();
//      }
//      return  renderedDocument;
//    }
};


class TextElement: public DocumentElement{
   string text;
   public:
   TextElement(string data){
      text = data;
   }
   string render(){
    return text;
   }
};
class ImageElement: public DocumentElement{
   string path;
   public:
   ImageElement(string p){
    path = p;
   }
   string render(){
      return "[Image: "+path+"]";
   }
};

class NewLineElement: public DocumentElement{
    public:
    string render(){
        return "\n";
    }
};

class TabSpaceElement: public DocumentElement{
    public:
    string render(){
        return "\t";
    }
};

class Persistence{
    public:
    virtual void save(string) = 0;
};

class FileStorage : public Persistence{
    public:
    void save(string content) override{
       ofstream file("document.txt");
       if(file.is_open()){
          file<<content;
          file.close();
       }
       else{
          cout<<"Error: Unable to open the file to write."<<endl;
       }
    }
};


class DBStorage: public Persistence{
    public:
    void save(string content){
       cout<<"Content Saved to DB Successfully: "<<content<<endl;
    }
};

int main(){
    Document* doc = new Document();
    DocumentRenderer* dRenderer = new DocumentRenderer(doc);

    DocumentEditor* editor = new DocumentEditor(doc);
    editor->addElement(new TextElement("Hi this is Varun!!"));
    editor->addElement(new NewLineElement());
    editor->addElement(new ImageElement("/user-image.png"));
    Persistence* p = new FileStorage();
    Persistence* pDb = new DBStorage();
    // p->save(editor->render());
    pDb->save(dRenderer->render());
}

// Ham Render Vali class ko client se directly interact krwa skte h bina use Document Editor p depend kraye kyuki one class should only interact with its next class(adjacent class) that is another design pattern..