#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <unordered_map>
#include "hashopen.h"

using namespace std;
using namespace std::chrono;

vector<pair<string, string>> loadCSV(string file);

int main()
{
  vector<pair<string, string>> data = loadCSV("data_small.csv");
  
  // Definición de la tabla hash
  //
  // Reemplazar "unordered_map" con el "hash" implementado

  Hash<string, string> map(50);
  //unordered_map<string, string> map;

  auto start = high_resolution_clock::now();  
  for (auto par : data)
    map[par.first] = par.second;
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);
  cout << "Time:" << duration.count() << endl;
  cout << "Size of Hash Table: " << map.bucket_count() << endl;
  
  /*for (unsigned i = 0; i < map.bucket_count(); ++i)
  {
    cout << "bucket #" << i << " contains: ";
    for (auto it = map.begin(i); it != map.end(i); ++it)
      cout << "[" << it->first << ":" << it->second << "] ";
    cout << "\n";
  } */ 
  //cout << "Hash Code:" << map.hash_function()("Heider") + 1 << endl;
}

vector<pair<string, string>> loadCSV(string file)
{
  vector<pair<string, string>> data;
  fstream fin;
  fin.open(file, ios::in);
  vector<string> row;
  string line, word, temp;
  int i = 0;
  while (!fin.eof())
  {
    row.clear();
    getline(fin, line);
    if (i++ == 0)
      continue;
    stringstream s(line);
    while (getline(s, word, ';'))
    {
      row.push_back(word);
    }
    if (row.size() == 2)
      data.push_back({row[0], row[1]});
  }
  return data;
}