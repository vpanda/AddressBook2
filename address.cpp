#include "address.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <cctype>

using namespace std;

Address::Address()
  :haveFile(false)
{
}

Address::Address(string str)
{
  haveFile=false;
  setFile(str);
}

Address::~Address()
{
  if(haveFile)
    fin.close();
}
    
bool Address::isHaveFile()
{
  return haveFile;
}

void Address::setFile(string str)
{
  if(haveFile)
  {
    fin.close();
    haveFile=false;
  }

  fin.open(str.c_str());
  if(!fin.is_open())
  {
    cout<<"open file error"<<endl;
    haveFile=false;
  }
  else
    haveFile=true;
}

void Address::changeFile()
{
  if(haveFile)
  {
    fin.close();
    haveFile=false;
  }

  std::string str;
  while(!haveFile)
  {
    cout<<"input the file name: ";
    cin>>str;
    setFile(str);
  }
  char ch=getchar();

}

void Address::go()
{
  changeFile();
  //setFile("sample1.txt");
  Json::Reader reader;
  Json::Value root;
  string str;
  vector<string> com;

  //解析json数据
  if(!reader.parse(fin, root, false))
  {
    cout<<"parse error"<<endl;
    return;
  }

  stack<Json::Value *> st;
  st.push(&root);

  while(true)
  {
    cout<<"ad>> ";
    getline(cin, str);
    parseCommand(com, str);

    if(com.size()<=0 || com.size()>2)
      cout<<"command error"<<endl;
    else if(com[0]==string("!quit")) //quit
    {
      cout<<"quit now"<<endl;
      
      ofstream fout;
      fout.open("data.txt");
      fout<<root;
      fout.close();

      break;
    }
    else if(com[0]==string("!help") && com.size()==1)
    {
      cout<<"help messages"<<endl;
      cout<<"command: ls"<<endl;
      cout<<"command: cd <key>"<<endl;
      cout<<"command: cat <key>"<<endl;
      cout<<"command: add"<<endl;
      cout<<"command: remove"<<endl;
      cout<<"when the app is exit, the data will save as data.txt"<<endl;   
    }
    else if(com[0]==string("ls") && com.size()==1) //ls
    {
      Json::Value *tmp=st.top();

      if(tmp->empty() || !tmp->isObject())
      {
        cout<<"there was nothing in it"<<endl;
        continue;
      }
      Json::Value::Members mem=tmp->getMemberNames();
      int x;
      for(x=0; x<mem.size(); x++)
        cout<<mem[x]<<" ";
      cout<<endl;
    }
    else if(com[0]==string("cd") && com.size()==2) //cd
    {
      if(com[1]==string(".."))
      {
        if(st.size()==1)
          cout<<"you can't return anymore, this is the root"<<endl;
        else
        {
          st.pop();
          cout<<"return "<<endl;
        }
        continue;
      }
      Json::Value *tmp=st.top();
      if(tmp->empty() || !tmp->isObject())
      {
        cout<<"there is have nothing"<<endl;
        continue;
      }
      Json::Value::Members mem=tmp->getMemberNames();
      int x;
      for(x=0; x<mem.size(); x++)
      {
        if(mem[x]==com[1])
          break;
      }
      
      if(x==mem.size())
        cout<<"can't find "<<com[1]<<endl;
      else
      {
        st.push(&(*tmp)[com[1]]);
        cout<<"enter into "<<com[1]<<endl;
      }
    }
    else if(com[0]==string("cat") && com.size()==2) //cat
    {
      Json::Value *tmp=st.top();
      bool flag=true;
      
      if(tmp->empty() || !tmp->isObject())
        flag=false;
      else
      {
        Json::Value::Members mem=tmp->getMemberNames();
        int x;
        for(x=0; x<mem.size(); x++)
        {
          if(mem[x]==com[1])
            break;
        }
        if(x==mem.size())
          flag=false;
      }
      if(flag)
      {
        Json::FastWriter writer;
        cout<<com[1]<<" : "<<writer.write((*tmp)[com[1]]);
      }
      else
        cout<<"cat command is error"<<endl;
    }
    else if(com[0]==string("add") && com.size()==1) //add
    {
      string keystr;
      string valstr;
      cout<<"key: ";
      getline(cin, keystr);
      cout<<"value: ";
      getline(cin, valstr);
      vector<string> a;
      vector<string> b;
      bool flag=parseAddress(a, b, valstr);
      if(flag)
      {
        Json::Value item;
        int x,y,sum=0;
        for(x=0;x<a.size();x++)
        {
          if(a[x]==string("age"))
          {
            for(y=0; y<b[x].size() && isdigit(b[x][y]); y++)
              sum=sum*10+(int)(b[x][y]-'0');
            item[a[x]]=sum;
          }
          else
            item[a[x]]=b[x];
        }
        Json::Value *tmp=st.top();
        (*tmp)[keystr]=item;
            
      }
      else
        cout<<"value parse error"<<endl;
    }
    else if(com[0]==string("remove") && com.size()==1) //remove
    {
      cout<<"please give the key: ";
      string rname;
      getline(cin, rname);
      
      //寻找给定的节点是否存在
      Json::Value *tmp=st.top();
      bool flag=true;
      
      if(tmp->empty() || !tmp->isObject())
        flag=false;
      else
      {
        Json::Value::Members mem=tmp->getMemberNames();
        int x;
        for(x=0; x<mem.size(); x++)
        {
          if(mem[x]==rname)
            break;
        }
        if(x==mem.size())
          flag=false;
      }

      if(flag)
      {
        tmp->removeMember(rname);
        st.pop();
        st.push(tmp);

        cout<<rname<<" was deleted from JSON"<<endl;
      }
      else
        cout<<"we can't find the key "<<rname<<endl;
    }
    else                       //other
      cout<<"command error"<<endl;
  }
}

void Address::parseCommand(std::vector<string > &com, const string &str)
{
  com.clear();
  int s,t;
  s=0;

  //去除前导空格
  while(s<str.size() && str[s]==' ')
    s++;

  while(s<str.size())
  {
    t=s;
    while(t<str.size() && str[t]!=' ')
      t++;
    com.push_back(str.substr(s, t-s));
    
    s=t;
    //去除前导空格
    while(s<str.size() && str[s]==' ')
      s++;
  }
}


bool Address::parseAddress(std::vector<std::string > &a, std::vector<std::string > &b, std::string &str)
{
  //寻找'{'
  int i,j,k;
  for(i=0;i<str.size();i++)
    if(str[i]=='{')
      break;
  if(i==str.size()) //没找到'{'，返回失败
    return false;

  a.clear();
  b.clear();
  i++;
  while(true)
  {
    //找age mobile address
    while(i<str.size() && str[i]!='"')
      i++;
    if(i>=str.size())
    {
      //cout<<"111"<<endl;
      return true;
    }
    
    i++;
    j=i;
    while(j<str.size() && str[j]!='"')
      j++;
    if(i>=str.size() || j>=str.size())
    {
      //cout<<"222"<<endl;
      return false;
    }
    a.push_back(str.substr(i, j-i));

    //找对应的数值
    i=j;
    while(i<str.size() && str[i]!=':')
      i++;
    if(i>=str.size())
    {
      //cout<<"333"<<endl;
      return false;
    }

    i++;
    while(i<str.size() && !isdigit(str[i]) && !isalpha(str[i]) && str[i]!='"')
      i++;
    if(i>=str.size())
    {
      //cout<<"444"<<endl;
      return false;
    }

    bool flag=false;
    if(str[i]=='"')
    {
      flag=true;
      k=i;
      i++;
    }
    j=i;
    while(j<str.size() && (isdigit(str[j]) || isalpha(str[j]) || str[j]==' '))
      j++;
    if(j==i ||(flag && (j>=str.size() ||str[j]!='"')))
    {
      //cout<<"555"<<endl;
      return false;
    }
    b.push_back(str.substr(i, j-i));
    i=j+1;
  }
}
