#include <iostream>
#include <string>
#include <curl/curl.h>
#include<bits/stdc++.h>
#include <jsoncpp/json/json.h>
#include <ctime>
//#include <chrono>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)    //https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html  
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
std::string glo;
int main(void)
{
  CURL *curl;
  CURLcode res;
  std::string readBuffer;

  curl = curl_easy_init();                                                            //curl_easy_init - Start a libcurl easy session
  if(curl) {                                                                          //curl_easy_setopt - set options for a curl easy handle
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.publicapis.org/entries");        //CURLOPT_URL - URL for this transfer
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);                     //CURLOPT_WRITEFUNCTION - callback for writing received data
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);                           // CURLOPT_WRITEDATA - pointer passed to the write callback - A common technique is to use the write callback to store the incoming data into a dynamically growing allocated buffer, and then this CURLOPT_WRITEDATA is used to point to a struct or the buffer to store data in.
    res = curl_easy_perform(curl);                                                    //curl_easy_perform - perform a blocking file transfer
    curl_easy_cleanup(curl);                                                          //curl_easy_cleanup - End a libcurl easy handle
    glo=readBuffer;
    //std::cout << readBuffer << std::endl;
  }
  //std::cout <<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<std::endl;
  //std::cout <<glo<<std::endl;
  //std::cout <<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++?????"<<std::endl;

Json::Reader reader;
Json::Value root;

    reader.parse(glo, root, false);
 auto entriesArray = root["entries"];

    auto firstelem = entriesArray[0];
    std::string describe = firstelem["Description"].asString();

// Time
// auto start = std::chrono::system_clock::now();
// auto end = std::chrono::system_clock::now();
 
//     std::chrono::duration<double> elapsed_seconds = end-start;
//     std::time_t end_time = std::chrono::system_clock::to_time_t(end);

  // current date/time based on current system
   time_t now = time(0);
   
   // convert now to string form
   char* dt = ctime(&now);
dt[strlen(dt) - 1] = '\0';

    std::cout << "{"<< "\n" <<"\"response_time\" : " << "\""<<dt<<"\","<<"\n";        
    std::cout<<"\"destripyion\" : "<< "\""<<describe<< "\""<<"\n"<<"}"<<"\n";                                                                      // std::ctime(&end_time) 
    //<< "\"elapsed time\" : " << "\""<< elapsed_seconds.count() << "s"<< "\","<< std::endl;

  return 0;
}

//g++ api.cpp -o api -lcurl -ljsoncpp
//./api

////cc api.cpp -lcurl

//JSON(compile) : g++ -o profile profile.cpp -ljsoncpp