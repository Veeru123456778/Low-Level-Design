// Real Life Adapter Use Cases-> LAN C Type Adapter -> converts lan cable to c type to plug in to laptop , Charger Socket adpater -> International sockets are different so need to use adapter to plug in charger....
// Similarly, Adapters helps us as an intermediate between two different interfaces(Contracts, abstract class) 
// Interface1 --------- Adapter --------- Interface2
// Agar hmare paas (Existing Code) h or ham isme kuch (Third party service -> Payment Service) ko integrate krna chahte h to ham Ya to Existing code m hi Third Party service k functions ko call krade -> par isse hmara code tightly coupled hojayega means agar kl ko hmari third party service m modifications hue / ya hmne third party service hi change krdi to hme sab kuch Apne Existing code m bhi change krna pdega jo ki (Open Close Principle ko break krta h)
// Adapter Existing code and Third Party service dono se interact krega but existing code ko third party service ke bare me kuch nhi pta hoga...

#include<bits/stdc++.h>
using namespace std;

class XMLDataProvider{
   public:
   string getReportInXML(string rawData){
      size_t startName = rawData.find("Name:");
      size_t endName = rawData.find(",");
      string name = rawData.substr(startName,endName-startName);
      size_t startAge = rawData.find("Age:");
      string age = rawData.substr(startAge);
      cout<<"<name>"+name+"</name>"+"<age>"+age+"</age>"<<endl;
      return "<name>"+name+"</name>"+"<age>"+age+"</age>";
   }
};

class IReport{
  public:
  virtual string getReportInJson(string rawData) = 0;
  virtual ~IReport(){}
};

class XMLDataProviderAdapter:public IReport{
  XMLDataProvider* xmlData;
  public:
  XMLDataProviderAdapter(XMLDataProvider* x){
    xmlData = x;
  }
  string getReportInJson(string rawData) override{
      string data = xmlData->getReportInXML(rawData);
      // Convert Xml Data To Json
      size_t startName = data.find("<name>");
      size_t endName = data.find("</name>");
      size_t startAge = data.find("<age>");
      size_t endAge = data.find("</age>");
      string name = data.substr(startName,endName);
      string age = data.substr(startAge,endAge);
       
      string jsonData = "{\n"+name+"\n"+age+"\n}";
      return jsonData;
  }
};

class Client{
   public:
   
   string getReport(IReport* obj,string rawData){
      return obj->getReportInJson(rawData);
   }
};

int main(){
    XMLDataProvider* xml = new XMLDataProvider();
    IReport* adapter = new XMLDataProviderAdapter(xml);
    string data = "Name:Varun,Age:20";

    Client* varun = new Client();
    cout<<varun->getReport(adapter,data)<<endl;
    
    delete adapter;
    delete xml;
    return 0; 
}