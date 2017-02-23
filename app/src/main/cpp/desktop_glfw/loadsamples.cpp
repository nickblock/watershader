#include "rapidjson/document.h"
#include <fstream>
#include <string>
#include <streambuf>
#include <iostream>
#include <vector>


struct Sample {
  float peakDecay;
  float averageDecay;
  float peak;
  float timeStamp;
  float average;
};
int main()
{
  std::fstream f("data/samples.json"); 
  std::string str((std::istreambuf_iterator<char>(f)),
                 std::istreambuf_iterator<char>());

  rapidjson::Document doc;
  doc.Parse(str.c_str());
  std::vector<Sample> samples;

  std::ofstream out("data/samples.bin", std::ios::binary|std::ios::out);

  if(doc.IsArray()) {
    std::cout << "array " << doc.Size() << std::endl;

    samples.resize(doc.Size());

    for(int i=0; i<doc.Size(); i++) {
      rapidjson::Value& val = doc[i];
      Sample& sample = samples[i];
      sample.peakDecay = val["peakDecay"].GetDouble();
      sample.averageDecay = val["averageDecay"].GetDouble();
      sample.peak = val["peak"].GetDouble();
      sample.timeStamp = val["timeStamp"].GetDouble();
      sample.average = val["average"].GetDouble();


      out.write((const char*)&sample.peakDecay, sizeof(float));
      out.write((const char*)&sample.averageDecay, sizeof(float));
      out.write((const char*)&sample.peak, sizeof(float));
      out.write((const char*)&sample.timeStamp, sizeof(float));
      out.write((const char*)&sample.average, sizeof(float));;
    }
  }
  return 0;
}