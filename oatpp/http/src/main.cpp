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

#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/web/server/HttpRouter.hpp"
#include "oatpp/network/server/SimpleTCPConnectionProvider.hpp"
#include "oatpp/core/Types.hpp"

#include <iostream>

/* typedef for convenience */
typedef oatpp::web::protocol::http::Status Status;
typedef oatpp::web::protocol::http::incoming::Request Request;
typedef oatpp::web::protocol::http::outgoing::Response Response;

/**
 * Handler to handle requests for URL to which it subscribed via Router
 */
class Handler : public oatpp::web::url::mapping::Subscriber<std::shared_ptr<Request>, std::shared_ptr<Response>> {
public:
  
  /**
   * method to handle Synchronous requests
   */
  std::shared_ptr<Response> processUrl(const std::shared_ptr<Request>& request) override {
    auto body = oatpp::web::protocol::http::outgoing::BufferBody::createShared("Hello World!!!");
    return Response::createShared(Status::CODE_200, body);
  }
  
  /**
   * method to handle Asynchronous requests (NOT USED HERE)
   */
  Action processUrlAsync(oatpp::async::AbstractCoroutine* parentCoroutine,
                         AsyncCallback callback,
                         const std::shared_ptr<Request>& request) override {
    throw std::runtime_error("this method is not used in the test");
  }
  
};

/**
 *  Run server method
 */
void run() {
  
  /* init server components */
  auto connectionProvider = oatpp::network::server::SimpleTCPConnectionProvider::createShared(8000);
  auto router = oatpp::web::server::HttpRouter::createShared();
  auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);
  
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
