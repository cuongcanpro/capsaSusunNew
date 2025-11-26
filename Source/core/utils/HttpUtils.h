#ifndef HttpUtils_h__
#define HttpUtils_h__
#include <string>
#include <functional>

#include "network/HttpClient.h""
#include "network/HttpClient.h"




typedef std::function<void(bool isSuccess, std::string data)> NetworkRequestCallback;

class HttpUtils {
public:
	static void addRequestPost(std::string url, std::string data, NetworkRequestCallback callback) {
		network::HttpRequest* cRequest = new network::HttpRequest();
		cRequest->setUrl(url.c_str());
		cRequest->setRequestType(network::HttpRequest::Type::POST);
		cRequest->setRequestData(data.c_str(), data.size());
		cRequest->setResponseCallback(
			[callback](network::HttpClient* client, network::HttpResponse* response) {
			if (!response || !response->isSucceed() || response->getResponseCode() == 404)
			{
				callback(false, "");
			}
			else {
                auto buffer = response->getResponseData();
                buffer->push_back('\0');  // to c_str
                // ax::print("response %s ", buffer->data());
                string result(buffer->begin(), buffer->end());
                callback(true, result);
			}

		}
		);
		network::HttpClient::getInstance()->setTimeoutForConnect(15);
		network::HttpClient::getInstance()->setTimeoutForRead(15);
		network::HttpClient::getInstance()->send(cRequest);
		cRequest->release();
	}

	static void addRequestGet(std::string url, NetworkRequestCallback callback = nullptr) {
		network::HttpRequest* cRequest = new network::HttpRequest();
		cRequest->setUrl(url.c_str());
		cRequest->setRequestType(network::HttpRequest::Type::GET);
		if (callback != nullptr) {
			cRequest->setResponseCallback(
				[callback](network::HttpClient* client, network::HttpResponse* response) {
					if (!response || !response->isSucceed() || response->getResponseCode() == 404)
					{
						callback(false, "");
					}
					else {
						auto buffer = response->getResponseData();
                        buffer->push_back('\0');  // to c_str
                        //ax::print("response %s ", buffer->data());

                        string result(buffer->begin(), buffer->end());
                        callback(true, result);
					}

				}
			);
		}
		network::HttpClient::getInstance()->setTimeoutForConnect(15);
		network::HttpClient::getInstance()->setTimeoutForRead(15);
		network::HttpClient::getInstance()->send(cRequest);
		cRequest->release();
	}
	static void addRequestPostJson(std::string url, std::string data, NetworkRequestCallback callback) {
		network::HttpRequest* cRequest = new network::HttpRequest();
		cRequest->setUrl(url.c_str());
		cRequest->setRequestType(network::HttpRequest::Type::POST);
		std::vector<std::string> headers;
		headers.push_back("Content-Type: application/json; charset=utf-8");
		cRequest->setHeaders(headers);
		cRequest->setRequestData(data.c_str(), data.size());
		cRequest->setResponseCallback(
			[callback](network::HttpClient* client, network::HttpResponse* response) {
			if (!response || !response->isSucceed() || response->getResponseCode() == 404)
			{
				callback(false, "");
			}
			else {
                auto buffer = response->getResponseData();
                buffer->push_back('\0');  // to c_str
                // ax::print("response %s ", buffer->data());

                string result(buffer->begin(), buffer->end());
                callback(true, result);
			}

		}
		);
		network::HttpClient::getInstance()->setTimeoutForConnect(15);
		network::HttpClient::getInstance()->setTimeoutForRead(15);
		network::HttpClient::getInstance()->send(cRequest);
		cRequest->release();
	}

};
#endif // HttpUtils
