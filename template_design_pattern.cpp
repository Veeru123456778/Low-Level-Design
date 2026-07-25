// Ye design pattern pipeline ki dikkat solve kar deta h.. 
// Ex: Hmare paas bhot saare ML Algorithms h like (SVM,Random Forest , etc) or hme chchiye ki jo procedure hona chahiye kisi bhi model ko train krne ka vo ek same template(pipeline) follow krna chahiye so ham iss case m lagate h template design pattern
// Template Like : Load Data -----> PreProcesses Data ------>  Train Model ------> Evaluate ------> Save Model

// Hmm loadData, PreProcess and saveResults ko parent class (Model Trainer class) me bhi define kar skte h or agar kisi child class ko change krne h ye methods to vo override bhi kar skti h 
// More Ex: Like Payment steps -> Fixed template to validate the balance and process the payment request....


#include<bits/stdc++.h>
using namespace std;

class ModelTrainer{
   public:
   virtual void loadData() = 0;
   virtual void preProcessData() = 0;
   virtual void trainModel() = 0;
   virtual void evaluateModel() = 0;
   virtual void saveResults() = 0;

    void templateMethod(){
     cout<<"Pipeline Started Executing...."<<endl;
     loadData();
     preProcessData();
     trainModel();
     evaluateModel();
     saveResults();
     cout<<"Pipeline Executed Successfully...."<<endl;
   }
};

class SVMModelTrainer:public ModelTrainer{
   public:
   void preProcessData(){
      cout<<"-----Data Pre-Processing Started-----"<<endl;
      cout<<"Data Pre-Processing Completed...."<<endl;
   }
   void loadData(){
      cout<<"Data Loaded Successfully...."<<endl;
   }
   void evaluateModel(){
      cout<<"-----Model Evaluation Started-----"<<endl;
      cout<<"Model Evaluation Completed...."<<endl;
   }
   void trainModel(){
      cout<<"-----Model Training Started using SVM Model Trainer-----"<<endl;
      cout<<"Model Training Completed...."<<endl;
   }

   void saveResults(){
      cout<<"Results Saved Successfully...."<<endl;
   }

};

class NeuralNetworkModelTrainer: public ModelTrainer{
  public:
   void preProcessData(){
      cout<<"-----Data Pre-Processing Started-----"<<endl;
      cout<<"Data Pre-Processing Completed...."<<endl;
   }
   void loadData(){
      cout<<"Data Loaded Successfully...."<<endl;
   }
   void evaluateModel(){
      cout<<"-----Model Evaluation Started-----"<<endl;
      cout<<"Model Evaluation Completed...."<<endl;
   }
   void trainModel(){
      cout<<"-----Model Training Started using Neural Network Model Trainer-----"<<endl;
      cout<<"Model Evaluation Completed...."<<endl;
   }

   void saveResults(){
      cout<<"Results Saved Successfully...."<<endl;
   }
};

int main(){
   ModelTrainer* svm = new SVMModelTrainer();
   svm->templateMethod();
}