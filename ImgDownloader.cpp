//
// Created by smz on 3/10/19.
//


#include <stdio.h>
#include <curl/curl.h>
#include "ImgDownloader.h"
#include <iostream>

void ImgDownloader::download(std::string url, int num) {
    CURL *curl;
    curl = curl_easy_init();
    FILE *fp;
    int result;

    std::string str = "/home/smz/CLionProjects/P1_TECFLIX/moviesIMG/img";
    str+= std::to_string(num);
    str+=".jpg";



    fp= fopen((const char*) str.data(), "wb");
    std::cout<<"URL: "<<url.data()<<std::endl;
    curl_easy_setopt(curl, CURLOPT_URL,url.data());

    curl_easy_setopt(curl, CURLOPT_WRITEDATA,fp);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR,1L);
    result = curl_easy_perform(curl);
    if(result == CURLE_OK){
        printf("Download successful!\n");
    }else{
        printf("ERROR: %s\n", curl_easy_strerror(static_cast<CURLcode>(result)));
    }
    fclose(fp);

    curl_easy_cleanup(curl);
}