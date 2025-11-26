#pragma once
#ifndef HttpRequestHandler_h__
#define HttpRequestHandler_h__
#include "axmol.h"
#include "extensions/axmol-ext.h"
#include "network/HttpRequest.h"
#include "network/HttpResponse.h"

using namespace ax;
using namespace ax::network;
class HttpRequestHandler : public ax::Object
{
public:
	HttpRequestHandler(void);
	~HttpRequestHandler(void);

	void onCompleteGetVersion(ax::network::HttpClient *client, ax::network::HttpResponse *response);
	void onCompleteGetFake(ax::network::HttpClient *client, ax::network::HttpResponse *response);
	void onCompleteGetPackage(ax::network::HttpClient *client, ax::network::HttpResponse *response);;
	void onCompleteGetIP(ax::network::HttpClient *client, ax::network::HttpResponse *response);

};
#endif // HttpRequestHandler_h__

