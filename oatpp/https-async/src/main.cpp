//
//  main.cpp
//  benchmark-http
//
//  Created by Leonid on 9/7/18.
//  Copyright © 2018 lganzzzo. All rights reserved.
//

#include "oatpp/web/protocol/http/outgoing/BufferBody.hpp"

#include "oatpp/web/protocol/http/incoming/Request.hpp"
#include "oatpp/web/protocol/http/outgoing/Response.hpp"

#include "oatpp-libressl/server/ConnectionProvider.hpp"
#include "oatpp-libressl/Config.hpp"

#include "oatpp/web/server/AsyncHttpConnectionHandler.hpp"
#include "oatpp/web/server/HttpRouter.hpp"
#include "oatpp/core/Types.hpp"

#include <iostream>

/* typedef for convenience */
typedef oatpp::web::protocol::http::Status Status;
typedef oatpp::web::protocol::http::incoming::Request Request;
typedef oatpp::web::protocol::http::outgoing::Response Response;

/**
 * Coroutine for request processing
 */
class HandlerCoroutine : public oatpp::async::CoroutineWithResult<HandlerCoroutine, std::shared_ptr<Response>> {
public:
  
  Action act() override {
    auto body = oatpp::web::protocol::http::outgoing::BufferBody::createShared("Hello World!!!");
    return _return(Response::createShared(Status::CODE_200, body));
  }
  
};

/**
 * Handler to handle requests for URL to which it subscribed via Router
 * In this example it just calls HandlerCoroutine to process request
 */
class Handler : public oatpp::web::url::mapping::Subscriber<std::shared_ptr<Request>, std::shared_ptr<Response>> {
public:
  
  /**
   * method to handle Synchronous requests (NOT USED HERE)
   */
  std::shared_ptr<Response> processUrl(const std::shared_ptr<Request>& request) override {
    throw std::runtime_error("this method is not used in the test");
  }
  
  /**
   * method to handle Asynchronous requests
   */
  Action processUrlAsync(oatpp::async::AbstractCoroutine* parentCoroutine,
                         AsyncCallback callback,
                         const std::shared_ptr<Request>& request) override {
    return parentCoroutine->startCoroutineForResult<HandlerCoroutine>(callback);
  }
  
};

/**
 *  Run server method
 */
void run() {
  
  /* create libressl config */
  
  // if you get:
  // runtime_error failed call to tls_config_set_key_file() - double check
  // key and cert file paths.
  
  auto key = "../../cert/test_key.pem"; // full path to .pem file
  auto cert = "../../cert/test_cert.crt"; // full path to .crt file
  auto config = oatpp::libressl::Config::createDefaultServerConfig(key, cert);
  
  /* init server components */
  auto connectionProvider = oatpp::libressl::server::ConnectionProvider::createShared(config, 8443, true /* non blocking */);
  auto router = oatpp::web::server::HttpRouter::createShared();
  auto connectionHandler = oatpp::web::server::AsyncHttpConnectionHandler::createShared(router);
  
  /* Handler subscribed to the root URL */
  router->addSubscriber("GET", "/", std::make_shared<Handler>());
  
  /* create server and run server */
  oatpp::network::server::Server server(connectionProvider, connectionHandler);
  server.run();
    
}

/**
 * main()
 * init Environment and run server
 */
int main(int argc, const char * argv[]) {
  
  oatpp::base::Environment::init();
  run();
  oatpp::base::Environment::destroy();
  
  return 0;
  
}
