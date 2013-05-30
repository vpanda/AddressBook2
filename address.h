#ifndef ADDRESS_H
#define ADDRESS_H

#include "json/json.h"
#include <string>
#include <fstream>
#include <vector>
class Address
{
public:
  Address();
  Address(std::string str);
  virtual ~Address();

  void init();
  bool isHaveFile(); //返回当前是否有文件已经读入
  void setFile(std::string str); //设置要解析的文件明
  void changeFile();
  virtual void go(); //运行ls等命令

  void parseCommand(std::vector<std::string > &com, const std::string &str); //解析读入的命令，例如ls
  bool parseAddress(std::vector<std::string > &a, std::vector<std::string > &b, std::string &str); //解析add命令添加的value，并返回解析是否成功

private:
  std::ifstream fin;
  bool haveFile;
};

#endif //ADDRESS_H
