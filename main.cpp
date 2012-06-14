#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
#include <curl/curl.h>
 
#include <string>
#include <iostream>

/*
 * jak kompilowac? 
 * nalezy sciagnac http://cygwin.com/install.html setup.exe, wybrac podczas instalacji dowolny mirror, a w liscie pakietow zainstalowac libcurl-devel z podlisy developer. 
 * nastepnie nalezy uruchomic srodowisko cygwin, przejsc do katalogu z programem za pomoca polecenia change dir (cd). 
 * wykonac polecenie 
 * g++ main.cpp -o main -llibcurl && ./main
 * ktore kompiluje plik oraz dolacza do niego biblioteke curl. 
 */

using namespace std;

class Browser { 
  std::string content;
  static Browser *instance;
CURL *curl_handle;
  explicit Browser() {
    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();
  }
public: 
  //wykorzystuje wzorzec singleton. przegladarka moze byc tylko jedna, przydatne, bo jest potrzebna tylko jedna 
  static Browser &getInstance() {
    if(instance==NULL) {
      instance=new Browser();
      printf("initialized Browser\n");
    }
    return *instance;
  }
std::string str;
friend size_t writefunc(const char *src, size_t size, size_t nmemb, void *dest) {
    printf("wczytano: %c", *src);
    std::string &str=*(std::string*)dest;
    str.append(src,size*nmemb);
    return size*nmemb;
  }
  string returnUrlContent(const char *url) {
    //    std::string str;
    str="";
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    //curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)&str);
    cout<<"wykonywanie2\n";
    curl_easy_perform(curl_handle);
    return str;
  }
  ~Browser() {
    curl_easy_cleanup(curl_handle);
  }
  static void clean() {
    delete instance;
  }
};
Browser *Browser::instance=NULL;

void exiting() {
  Browser::clean();
  printf("cleaned sucessfuly\n");
}

int main(void)
{
  atexit(exiting);
  std::string url="example";
  while(!url.empty()) {
    cout<<"podaj adres strony do zaladowania (lub pusty wiersz dla przykladowej strony)\n";
    //    cin>>url;
    getline(cin,url);
    if(url==string("exit")) break;
    if(url.length()<=1) url="http://www.wp.pl";
      std::cout<<Browser::getInstance().returnUrlContent(url.c_str());
  }
  return 0;
}
