package main

import (
    "fmt"
    "net/http"
    "log"
)

func HelloServer(w http.ResponseWriter, req *http.Request) {
    fmt.Fprintf(w, "Hello World!!!")
}

func main() {
    http.HandleFunc("/hello", HelloServer)
    err := http.ListenAndServeTLS(":8443", 
        "../cert/test_cert.crt", 
        "../cert/test_key.pem", 
        nil)
    if err != nil {
        log.Fatal("ListenAndServe: ", err)
    }
}