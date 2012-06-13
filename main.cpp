/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2011, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at http://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
#include <curl/curl.h>
 
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  int written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

#include <string>

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

  string returnUrlContent(const char *url) {
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L); //nie pokazuj 
    return string("");
  }
};
Browser *Browser::instance=NULL;

int main(void)
{
  Browser::getInstance().returnUrlContent("http://wp.pl");
  // 
  // static const char *headerfilename = "head.out";
  // FILE *headerfile;
  // static const char *bodyfilename = "body.out";
  // FILE *bodyfile;
 
  // 
 
  // /* init the curl session */ 
  // 
 
  // /* set URL to get */ 
  // 
 
  // /* no progress meter please */ 
  // 
 
  // /* send all data to this function  */ 
  // curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
 
  // /* open the files */ 
  // headerfile = fopen(headerfilename,"w");
  // if (headerfile == NULL) {
  //   curl_easy_cleanup(curl_handle);
  //   return -1;
  // }
  // bodyfile = fopen(bodyfilename,"w");
  // if (bodyfile == NULL) {
  //   curl_easy_cleanup(curl_handle);
  //   return -1;
  // }
 
  // /* we want the headers to this file handle */ 
  // curl_easy_setopt(curl_handle,   CURLOPT_WRITEHEADER, headerfile);
 
  // /*
  //  * Notice here that if you want the actual data sent anywhere else but
  //  * stdout, you should consider using the CURLOPT_WRITEDATA option.  */ 
 
  // /* get it! */ 
  // curl_easy_perform(curl_handle);
 
  // /* close the header file */ 
  // fclose(headerfile);
 
  // /* cleanup curl stuff */ 
  // curl_easy_cleanup(curl_handle);
 
  return 0;
}
