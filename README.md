# oat++ benchmark
This repository contains code to reproduce performance benchmarks oatpp vs other frameworks

More about oatpp see [https://oatpp.io/](https://oatpp.io/)  
Latest benchmark results [https://oatpp.io/benchmark/aws](https://oatpp.io/benchmark/aws)

## What's in the repo
```c
- oatpp
  |- http           // Multithreaded minimal oatpp HTTP-server with hello world endpoint
  |- http-async     // Asynchronous minimal oatpp HTTP-server with hello world endpoint
  |- https          // Multithreaded minimal oatpp HTTPS-server with hello world endpoint
  |- https-async    // Asynchronous minimal oatpp HTTPS-server with hello world endpoint
  |- lib            // oatpp git-submodules

- go
  |- http.go        // minimal go HTTP-server with hello world endpoint
  |- https.go       // minimal go HTTPS-server with hello world endpoint
  
- cert              // folder with test certificates for HTTPS
  
```

## How to start

Before you start make sure to have ```build-essentials``` and ```golang``` installed.
In order to build and run oatpp HTTPS servers you have to also install ```libressl```.

- clone repo with submodules: ```git clone --recurse-submodules https://github.com/oatpp/benchmark```
- build oatpp services, ex: ```$ cd <this-repo>/oatpp/http``` then ```$ ./build_app.sh```
- build go services, ex: ```$ cd <this-repo>/go``` then ```$ go build http.go```

Now you can run services and start loading them.

**Recommended tools for load-testing:**  
- HTTP - wrk, apache benchmark(ab)
- HTTPS - apache benchmark(ab)

