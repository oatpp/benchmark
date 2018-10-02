//
//  main.cpp
//  benchmark-http
//
//  Created by Leonid on 9/7/18.
//  Copyright © 2018 lganzzzo. All rights reserved.
//

#include "Logger.hpp"

#include "oatpp/web/protocol/http/outgoing/BufferBody.hpp"

#include "oatpp/web/protocol/http/incoming/Request.hpp"
#include "oatpp/web/protocol/http/outgoing/Response.hpp"

#include "oatpp/web/server/AsyncHttpConnectionHandler.hpp"
#include "oatpp/web/server/HttpRouter.hpp"
#include "oatpp/network/server/SimpleTCPConnectionProvider.hpp"
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
  
  /* init server components */
  auto connectionProvider = oatpp::network::server::SimpleTCPConnectionProvider::createShared(8001, true /* non blocking */);
  auto router = oatpp::web::server::HttpRouter::createShared();
  auto connectionHandler = oatpp::web::server::AsyncHttpConnectionHandler::createShared(router);
  
  /* Handler subscribed to the root URL */
  router->addSubscriber("GET", "/", std::make_shared<Handler>());
  
  /* create server and run server */
  oatpp::network::server::Server server(connectionProvider, connectionHandler);
  OATPP_LOGD("server", "async server running on port %d", connectionProvider->getPort());
  server.run();
    
}

/**
 * main()
 * init Environment and run server
 */
int main(int argc, const char * argv[]) {
  
  oatpp::base::Environment::init();
  oatpp::base::Environment::setLogger(new Logger());
  run();
  oatpp::base::Environment::setLogger(nullptr);
  oatpp::base::Environment::destroy();
  
  return 0;
  
}
