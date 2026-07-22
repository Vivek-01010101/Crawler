#include "../../include/Fetcher.h"
#include <curl/curl.h>
#include <iostream>
#include <thread> // Required for std::this_thread::sleep_for
#include <chrono> // Required for std::chrono::seconds

Fetcher::Fetcher() {
    // Constructor
}

Fetcher::~Fetcher() {
    // Destructor
}

// This callback function is called by libcurl every time a chunk of data arrives over the network.
size_t Fetcher::writeCallback(void* incomingBytes, size_t size, size_t nmemb, void* userPointer) {
    // 1. Calculate the total size of this incoming chunk
    size_t chunkSize = size * nmemb;

    // 2. Convert the generic userPointer back into our std::string pointer
    std::string* outputString = static_cast<std::string*>(userPointer);

    // 3. Append the incoming network bytes directly to our string
    outputString->append(static_cast<char*>(incomingBytes), chunkSize);

    // 4. Return the number of bytes processed so libcurl knows everything went fine
    return chunkSize;
}

std::string Fetcher::fetch(const std::string& url) {
    // STEP 1: Start a new libcurl easy session handle
    CURL* curlHandle = curl_easy_init();
    
    if (curlHandle == nullptr) {
        std::cerr << "Error: Could not initialize libcurl!\n";
        return "";
    }

    // This string will hold the HTML content as it downloads
    std::string downloadedHtml = "";

    // STEP 2: Configure libcurl settings (options)
    
    // Set the web page URL to fetch
    curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());

    // Tell libcurl to follow HTTP redirects (e.g., HTTP 301/302 -> new location)
    curl_easy_setopt(curlHandle, CURLOPT_FOLLOWLOCATION, 1L);

    // Set a maximum timeout of 10 seconds for the total download process
    curl_easy_setopt(curlHandle, CURLOPT_TIMEOUT, 10L);

    // Set a User-Agent header so web servers identify us as a standard browser
    curl_easy_setopt(curlHandle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64)");

    // Tell libcurl WHICH function to call when data arrives
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, writeCallback);

    // Pass the memory address of downloadedHtml so writeCallback can write to it
    curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &downloadedHtml);

    // STEP 3: Execute the network request (This line blocks until finished)
    CURLcode result = curl_easy_perform(curlHandle);

    // STEP 4: Check if the download succeeded or failed
    if (result == CURLE_OK) {
        // Fetch the HTTP response code (e.g., 200 for Success, 404 for Not Found)
        long httpStatusCode = 0;
        curl_easy_getinfo(curlHandle, CURLINFO_RESPONSE_CODE, &httpStatusCode);

        if (httpStatusCode != 200)
        {
            downloadedHtml.clear();
        }
        
        std::cout << "Successfully fetched: " << url << " [HTTP " << httpStatusCode << "]\n";
    } 
    else {
        // Print the error message if something went wrong (e.g., connection timed out, DNS failed)
        std::cerr << "Failed to fetch: " << url << " | Error: " << curl_easy_strerror(result) << "\n";
        
        // Clear the string so we don't return partial or corrupted data
        downloadedHtml = "";
    }

    // STEP 5: Clean up memory allocated by libcurl
    curl_easy_cleanup(curlHandle);

    // STEP 6: Rate Limiting / Politeness Delay
    // Pauses execution for 1 second to avoid spamming the target server
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // STEP 7: Return the downloaded HTML content
    return downloadedHtml;
}