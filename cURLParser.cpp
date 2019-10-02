//
// Created by smz on 2/10/19.
//

#include "cURLParser.h"
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <QtCore/QString>


static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string cURLParser::getURL(std::string url)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL,url.data());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        //std::cout << readBuffer << std::endl;
        std::string str = readBuffer;
        std::string line;
        for(std::string::iterator it = str.begin(); it != str.end(); ++it) {

            if(*it != '\n') {
                line += *it;
            }else{
                QString lineInQString = QString::fromStdString(line);
                if(lineInQString.contains("182,268")) {
                    std::cout << "Línea: " << line << std::endl;
                }
                line.clear();
            }
        }

    }
    return readBuffer;
}
