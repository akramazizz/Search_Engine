

#include <iostream>
#include <string>
#include<vector>
# include <sstream>
#include <fstream>

using namespace std;
struct edge
{
   
    int index;
    string source;
    string dest;
};
struct pagerank
{
    string name;
    double value;
};
void swap(pagerank* a, pagerank* b)
{
    pagerank t = *a;
    *a = *b;
    *b = t;
}
int partition (vector<pagerank> &arr, int low, int high)
{
    
    double pivot = arr[high].value;
    int i = (low - 1);
  
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j].value < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
  
void quickSort(vector<pagerank> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
  

class graph
{
    int indices;
    int V;
   vector<vector<edge> > adjList;
 vector<edge> *transposed;
    vector<int> clickOfPage;
    vector<string> edges;
    vector<pagerank> pr;
    vector<double>impressions;
    vector<double> ctr;
    vector<vector<string> > keyWords;
    vector<pagerank> scores;
    vector<pagerank> res;
    void addEdge(int x, string v, string w);
    void addTransposedEdge(int x, string v, string w);
    void PageRank ();
public:
    graph(int N);
    void updatePR();
    void IniatePR();
    void addEdgeWrap (string v, string w);
    void TransposeGraph ();
    void PageRankWrap ();
    void CTR();
    void Score();
    void impressionCalculator();
    void keywords();
    void UpdateCTR(string url);
    void UpdateImpressions(string url);
    vector<pagerank> searchResult(vector<string> word);
    void cover();
    vector<pagerank> searching(vector<string> x);
    void displaytrans()
    {
        for(int i=0;i<indices;i++)
        {
           { cout<<edges[i]<<": ";
            for(int j=0;j<transposed[i].size();j++)
            {
                cout<<transposed[i][j].dest<<"\t";
            }
            cout<<endl;}
        }
    }
    void display()
    {
        //cout<<indices<<endl;
        for(int i=0;i<indices;i++)
        {
           { cout<<edges[i]<<": ";
               
            for(int j=0;j<adjList[i].size();j++)
            {
                cout<<adjList[i][j].dest<<"\t";
            }
            cout<<endl;}
        }
    }
};


graph::graph(int N)
{
    adjList.clear();
    adjList.resize(N);
    transposed = new vector<edge>[N];
    V=N;
}
void graph::addEdgeWrap (string v, string w)
{
    int index=-1;
    for(int i=0;i<edges.size();i++)
    {
        if(v==edges[i])
        {
            index=i;
        }
    }
    if(index==-1)
    {
        edges.push_back(v);
        index=edges.size()-1;
        indices=index+1;
    }
    if(index!=-1)
    {
        addEdge(index,v, w);
      
    }
    int count=0;
    for(int j=0;j<edges.size();j++)
    {
        if(w==edges[j])
        {
            count++;
        }
    }
    if (count==0)
    {
        edges.push_back(w);
        index=edges.size()-1;
        indices=index+1;
    }
}
void graph::addEdge(int x,string v,string w)
{
    edge c;
    c.dest=w;
    c.source=v;
    c.index=x;
    adjList[x].push_back(c);
}
void graph::addTransposedEdge(int x,string v,string w)
{
    edge c;
    c.dest=w;
    c.source=v;
    c.index=x;
    transposed[x].push_back(c);
}
void graph::PageRankWrap() {
    
    for(int i=0;i<indices;i++)
    {
        pr[i].name=edges[i];
        pr[i].value=(1/indices);
    }
    
}
void graph:: TransposeGraph ()
{
    for(int i=0;i<V;i++)
    {
        
        for(int j=0;j<adjList[i].size();j++)
        {
            
            for(int k=0;k<edges.size();k++)
            {
                if(edges[k]==adjList[i][j].dest)
                {
                    addTransposedEdge(k,adjList[i][j].dest , adjList[i][j].source);
                }
                
            }}}}
void graph::IniatePR()
{
    pr.resize(edges.size());
    for(int i=0;i<edges.size();i++)
    {
        double v=(1.0/edges.size());
        pr[i].name=edges[i];
        pr[i].value=v;;
    }}
void graph::updatePR()
{
    vector<double> templet;
    templet.resize(pr.size());
    for(int i=0;i<edges.size();i++)
    {
        double temp=0.0;
        for(int j=0;j<transposed[i].size();j++)
        {
            
            for(int k=0;k<edges.size();k++)
            {if(transposed[i][j].dest==edges[k])
            {
               // cout<<pr[k].name<<" : ";
              // cout<<pr[k].value<<" divided "<<transposed[k].size();
                temp=temp+(pr[k].value/adjList[k].size());
            }
                
            }
        }
        templet[i]=temp;
    }
    for(int l=0;l<pr.size();l++)
    {
        pr[l].value=templet[l];
    }
   /* for(int l=0;l<pr.size();l++)
    {
        cout<<pr[l].name<<" With "<<pr[l].value<<endl;
    }*/
}
void graph::impressionCalculator()
{
    for(int i=0;i<edges.size();i++)
    {
        impressions.push_back(1);
    }
    ifstream impres;
    vector<string> substring;
    double x;
    impres.open("impressions.txt");
    if(impres.is_open())
    {
        string imp;
      
        while(!impres.eof())
        {
            getline(impres,imp);
            stringstream ss(imp);
            while(ss.good())
            {
                string sub;
                getline(ss,sub,',');
                substring.push_back(sub);
            }
        }
        for(int i=0;i<substring.size();i=i+2)
        {
            for(int j=0;j<edges.size();j++)
            {
                if(substring[i]==edges[j])
                {
                    x=stod(substring[i+1]);
                    impressions[j]=x;
                }
            }
        }
    }

}
void graph::CTR()
{
    ifstream numberOfClicks;
   
   
    numberOfClicks.open("num.txt");
    if (numberOfClicks.is_open())
    {
        string click;
        double clk;
        while(!numberOfClicks.eof())
        {
            getline(numberOfClicks,click);
            clk=stod(click);
            clickOfPage.push_back(clk);
        }
    }
    for(int i=0;i<clickOfPage.size();i++)
    {
        ctr.push_back((clickOfPage[i]/impressions[i]));
    }
   /* for(int i=0;i<edges.size();i++)
    {
        cout<<edges[i]<<": "<<ctr[i]<<endl;
    }*/
}
void graph::UpdateCTR(string url)
{
    ofstream ctr_update;
    for(int i=0;i<edges.size();i++)
    {
        if(url==edges[i])
        {
            clickOfPage[i]++;
            ctr[i]=(clickOfPage[i]/impressions[i]);
        }
    }
    Score();
    ctr_update.open("num.txt");
    for (int i=0;i<edges.size()-1;i++)
    {  ctr_update<<clickOfPage[i]<<endl;}
    ctr_update<<clickOfPage[edges.size()-1];
    ctr_update.close();
}
void graph::UpdateImpressions(string url)
{
    ofstream impression_out;
    for(int i=0;i<edges.size();i++)
    {
        if(url==edges[i])
        {
            impressions[i]++;
        }
    }
    Score();
    impression_out.open("impressions.txt");
    for(int i=0;i<edges.size()-1;i++)
    {
        impression_out<<edges[i]<<','<<impressions[i]<<endl;
    }
    impression_out<<edges[edges.size()-1]<<','<<impressions[edges.size()-1];
    impression_out.close();
}
void graph::Score()
{
    scores.resize(edges.size());
    for(int i=0;i<edges.size();i++)
    {
        double temp1;
        temp1=(0.1*impressions[i])/(1.1*impressions[i]);
        double temp2=1-temp1;
        double temp3= (((temp2*pr[i].value)+(temp1*ctr[i]))*0.6);
        scores[i].value= (0.4*pr[i].value)+temp3;
        scores[i].name=edges[i];
    }
    quickSort(scores, 0,edges.size()-1);
}
void graph:: keywords()
{
    ifstream key;
    keyWords.resize(edges.size());
    vector<string> substring;
    key.open("keywords.txt");
    if(key.is_open())
    { int count=0;
        string k;
        while(!key.eof())
        {
            getline(key, k);
            stringstream ss(k);
            int subcount=0;
            string sub;
            while(ss.good())
            {
                getline(ss,sub,',');
                if(subcount!=0)
               { keyWords[count].push_back(sub);}
                subcount++;
            }
            count++;
        }
    }
}
vector<pagerank> graph::searchResult(vector<string> word)
{
    res.clear();
    vector<pagerank> r;
    vector<int> ind;
    for(int k=0;k<word.size();k++)
    {for(int i=0;i<keyWords.size();i++)
    {
        for(int j=0;j<keyWords[i].size();j++)
        {
            if(word[k]==keyWords[i][j])
            {
                ind.push_back(i);
            }
        }
    }}
    if(ind.size()!=0)
    {   for(int i=edges.size()-1;i>=0;i--)
        {
            for(int j=0;j<ind.size();j++)
            {
                if(edges[ind[j]]==scores[i].name)
                {
                    pagerank x;
                    x.name=scores[i].name;
                    x.value=ind[j];
                    res.push_back(x);
                }
            }
        }
        for(int i=0;i<res.size()-1;i++)
        {
            if(res[i].value==res[i+1].value)
            {
                res.erase(res.begin()+i+1);
            }
        }
    }
 //   for(int i=0;i<res.size();i++)
    //    cout<<res[i].name<<": "<<res[i].value<<endl;
    
    return res;
}
void graph::cover()
{
    
    
    TransposeGraph();
    IniatePR();
    updatePR();
    updatePR();
    impressionCalculator();
    CTR();
    Score();
    keywords();
    
    
   
}
vector<pagerank> graph::searching(vector<string> x)
{
    vector<pagerank> result;
    
    cover();
    result=searchResult(x);
    return result;
}
int main() {
    vector<pagerank> result;
    vector<string> urls;
    ifstream in ;
    vector<string> substring;
    int line_count= 0;
    in.open("web.txt");
    if (in.is_open())
    {
        string d;
        while(!in.eof())
        {
            getline(in,d);
            line_count++;
            stringstream ss(d);
            while(ss.good())
            {
                string sub;
                getline(ss,sub,',');
                substring.push_back(sub);
            }
         
        }
       
    }
   
    
    
   for(int i=0;i<substring.size();i=i+2)
    {
        if(urls.size()==0)
        {
            urls.push_back(substring[i]);
        }
        else
            {
                int count=0;
                for(int j=0;j<urls.size();j++)
                {
                    if(substring[i]==urls[j])
                       {
                        count++;
                    }
                }
                if (count==0)
                {
                    urls.push_back(substring[i]);
                }
            }
    }
    for(int i=1;i<substring.size();i=i+2)
     {
         int count=0;
         for(int j=0;j<urls.size();j++)
         {
             if(substring[i]==urls[j])
                {
                 count++;
             }
         }
         if (count==0)
         {
             urls.push_back(substring[i]);
         }
     }
    graph g(urls.size());
    for(int i=0;i<substring.size();i=i+2)
      {
          g.addEdgeWrap(substring[i], substring[i+1]);
      }
   
    int choice1=1;
    vector<string> substrings;
    cout<<"What Would you like to do"<<endl<<"1.New Search"<<endl<<"2.Exit"<<endl;
    cin>>choice1;
    while(choice1==1)
    {
        substrings.clear();
        string search;
        cout<<"What do You want to search for"<<endl<<"type here: ";
        cin>>search;
        if(search[0]=='"')
        {
            string x="";
            for(int i=1;i<search.length()-1;i++)
           {
               x=x+search[i];
           }
            cout<<x<<"<"<<endl;
            stringstream sm(x);
            while(sm.good())
            {
                string sub;
                getline(sm,sub,' ');
                substrings.push_back(sub);
            }
        }
        else
        {
            cout<<search<<endl;
            stringstream ss(search);
            while(ss.good())
            {
                string sub;
                getline(ss,sub,' ');
                substrings.push_back(sub);
            }
        }
        cout<<endl;
        int secondchoice=0;
        result= g.searching(substrings);
        if(result.size()==0)
        {
            cout<<"The word you are searching for is not clear"<<endl;
            choice1=0;
        }
        else
       { cout<<"Search Result: "<<endl;
        for(int i=0;i<result.size();i++)
        {
            cout<<i+1<<". "<<result[i].name<<endl;
            g.UpdateImpressions(urls[result[i].value]);
        }
        cout<<endl;
        cout<<"What Would you like to"<<endl<<"1. Choose a webpage to open"<<endl<<"2.New search"<<endl<<"3.Exit"<<endl;
        cin>>secondchoice;
        while(secondchoice==1)
        {
            int webpage;
            cout<<"Which Web Page"<<endl;
            for(int i=0;i<result.size();i++)
            {
                cout<<i+1<<". "<<result[i].name<<endl;
            }
            cout<<"Type your choice here :";
            cin>>webpage;
            int third=0;
           
            cout<<"You are currently Viewing "<<result[webpage-1].name<<endl<<endl<<"What Would You like to do"<<endl<<"1. Back to search result"<<endl<<"2. New Search"<<endl<<"3 Exit"<<endl<<"Type your choice here :";
            cin>>third;
            g.UpdateCTR(urls[result[webpage-1].value]);
            if(third==2)
            {
                secondchoice=0;
            }
            if(third==3)
            {
                secondchoice=0;
                choice1=0;
            }
        }
        result.clear();
        if(secondchoice==3)
        {
            choice1=0;
        }
           
       }
    }
}
