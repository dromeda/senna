# Senna

Senna is a simple software that allows you to perform load testing on a website or web service by making multiple HTTP requests in a row. It is written in C and uses the libcurl library to handle the requests.

## Getting started
To use Senna, you will need to have the libcurl library installed on your machine. You can download it from the [official website](https://curl.haxx.se/libcurl/) or install it using your package manager.

Once you have the dependencies installed, you can download the Senna source code from the official repository on [GitHub](https://github.com/dromeda/senna). Compile it using your preferred C compiler and link it with the libcurl library.

Usage
To use Senna, run the binary file with the following command:

```bash
./senna http://example.com number_of_requests
```

Where "http://example.com" is the address of the website or web service you want to test, and "number_of_requests" is the number of requests you want Senna to make.

For example, if you want to perform 10,000 requests on the website "http://example.com", you would run the following command:

```bash
./senna http://example.com 10000
````

After Senna finishes making the requests, it will generate a report with statistics about the performance of the website or web service. The report will include information such as the average response time, the fastest and slowest requests, and the percentage of requests that returned a 200 OK status code.

### Limitations
Senna is a simple tool that does not support advanced features such as cookies, authentication, or custom headers. If you need to perform more complex load testing, you should consider using a more advanced tool such as Apache JMeter or Gatling.