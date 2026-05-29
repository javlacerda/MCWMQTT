/*
** MCWMQTT - Omnis / MQTT Broker Integration
** DLL Entry point
*/

#include "MCWMQTT.h"
#include "Utils.h"
#include <memory>

/*
** Global variables
*/
ECOobject oMQTTObjects[] =
{
    {cObject_MQTT, 2000, 0, 0}
};

ECOparam paramsSetAddress[] =
{
    {7000, fftCharacter, 0, 0}
};

ECOparam paramsSetTimeout[] =
{
    {7001, fftInteger, 0, 0}
};

ECOparam paramsSetClientID[] =
{
    {7002, fftCharacter, 0, 0}
};

ECOparam paramsSetTopic[] =
{
    {7003, fftCharacter, 0, 0}
};

ECOparam paramsSetQoS[] =
{
    {7004, fftInteger, 0, 0}
};

ECOparam paramsSetUsername[] =
{
    {7005, fftCharacter, 0, 0}
};

ECOparam paramsSetPassword[] =
{
    {7006, fftCharacter, 0, 0}
};

ECOparam paramsSetKeepAliveInterval[] =
{
    {7007, fftInteger, 0, 0}
};

ECOparam paramsSetCleanStart[] =
{
    {7008, fftBoolean, 0, 0}
};

ECOparam paramsPublish[] =
{
    {7009, fftCharacter, 0, 0}
};

ECOparam paramsSetRetained[] =
{
    {7010, fftBoolean, 0, 0}
};

ECOparam paramsSetConnectTimeout[] =
{
    {7011, fftInteger, 0, 0}
};

ECOparam paramsSetSessionExpiryInterval[] =
{
    {7012, fftInteger, 0, 0}
};

ECOparam paramsSetMessageExpiryInterval[] =
{
    {7013, fftInteger, 0, 0}
};

ECOparam paramsSetAutomaticReconnect[] =
{
    {7014, fftBoolean, 0, 0}
};

ECOmethodEvent oMQTTFunctions[] =
{
    {cSetAddressFunction,               6000, fftBoolean,   sizeof(paramsSetAddress) / sizeof(ECOparam),                  paramsSetAddress,               0, 0},
    {cSetTimeoutFunction,               6001, fftBoolean,   sizeof(paramsSetTimeout) / sizeof(ECOparam),                  paramsSetTimeout,               0, 0},
    {cSetClientIDFunction,              6002, fftBoolean,   sizeof(paramsSetClientID) / sizeof(ECOparam),                 paramsSetClientID,              0, 0},
    {cSetTopicFunction,                 6003, fftBoolean,   sizeof(paramsSetTopic) / sizeof(ECOparam),                    paramsSetTopic,                 0, 0},
    {cSetQoSFunction,                   6004, fftBoolean,   sizeof(paramsSetQoS) / sizeof(ECOparam),                      paramsSetQoS,                   0, 0},
    {cSetUsernameFunction,              6005, fftBoolean,   sizeof(paramsSetUsername) / sizeof(ECOparam),                 paramsSetUsername,              0, 0},
    {cSetPasswordFunction,              6006, fftBoolean,   sizeof(paramsSetPassword) / sizeof(ECOparam),                 paramsSetPassword,              0, 0},
    {cSetKeepAliveIntervalFunction,     6007, fftBoolean,   sizeof(paramsSetKeepAliveInterval) / sizeof(ECOparam),        paramsSetKeepAliveInterval,     0, 0},
    {cSetCleanStartFunction,            6008, fftBoolean,   sizeof(paramsSetCleanStart) / sizeof(ECOparam),               paramsSetCleanStart,            0, 0},
    {cConnectFunction,                  6009, fftBoolean,   0, 0, 0, 0},
    {cDisconnectFunction,               6010, fftBoolean,   0, 0, 0, 0},
    {cPublishFunction,                  6011, fftBoolean,   sizeof(paramsPublish) / sizeof(ECOparam),                     paramsPublish,                  0, 0},
    {cSetRetainedFunction,              6012, fftBoolean,   sizeof(paramsSetRetained) / sizeof(ECOparam),                 paramsSetRetained,              0, 0},
    {cSetConnectTimeoutFunction,        6013, fftBoolean,   sizeof(paramsSetConnectTimeout) / sizeof(ECOparam),           paramsSetConnectTimeout,        0, 0},
    {cSetSessionExpiryIntervalFunction, 6014, fftBoolean,   sizeof(paramsSetSessionExpiryInterval) / sizeof(ECOparam),    paramsSetSessionExpiryInterval, 0, 0},
    {cSetMessageExpiryIntervalFunction, 6015, fftBoolean,   sizeof(paramsSetMessageExpiryInterval) / sizeof(ECOparam),    paramsSetMessageExpiryInterval, 0, 0},
    {cSetAutomaticReconnectFunction,    6016, fftBoolean,   sizeof(paramsSetAutomaticReconnect) / sizeof(ECOparam),       paramsSetAutomaticReconnect,    0, 0},
    {cGetErrorMessageFunction,          6017, fftCharacter, 0, 0, 0, 0},
    {cGetIsConnectedFunction,           6018, fftBoolean,   0, 0, 0, 0}
};

#define cFunctionsCount (sizeof(oMQTTFunctions) / sizeof(ECOmethodEvent))
#define cObjectsCount (sizeof(oMQTTObjects) / sizeof(ECOobject))

/*
** DLL entry point function
*/
extern "C" LRESULT OMNISWNDPROC MCWMQTTWndProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam, EXTCompInfo *eci)
{
   ECOsetupCallbacks(hwnd, eci);

   switch (Msg) {
   case ECM_CONNECT:
      return EXT_FLAG_LOADED | EXT_FLAG_ALWAYS_USABLE | EXT_FLAG_REMAINLOADED | EXT_FLAG_NVOBJECTS;

   case ECM_GETOBJECT:
      return ECOreturnObjects(gInstLib, eci, &oMQTTObjects[0], cObjectsCount);

   case ECM_OBJCONSTRUCT:
      if (eci->mCompId == cObject_MQTT) {
         CMQTT *mqtt = reinterpret_cast<CMQTT *>(ECOfindNVObject(eci->mOmnisInstance, lParam));
         if (mqtt == nullptr) {
            CMQTT *obj = new CMQTT(reinterpret_cast<qobjinst>(lParam));
            ECOinsertNVObject(eci->mOmnisInstance, lParam, reinterpret_cast<void *>(obj));
         }
         return qtrue;
      }
      return qfalse;

   case ECM_OBJDESTRUCT:
      if (eci->mCompId == cObject_MQTT && wParam == ECM_WPARAM_OBJINFO) {
         void *object = ECOremoveNVObject(eci->mOmnisInstance, lParam);
         if (object) {
            CMQTT *obj = reinterpret_cast<CMQTT *>(object);
            delete obj;
            obj = nullptr;
         }
      }
      return qtrue;

   case ECM_OBJECT_COPY: {
      objCopyInfo *copyInfo = reinterpret_cast<objCopyInfo *>(lParam);
      CMQTT *srcObject = reinterpret_cast<CMQTT *>(ECOfindNVObject(eci->mOmnisInstance, copyInfo->mSourceObject));
      if (srcObject) {
         CMQTT *destObj = reinterpret_cast<CMQTT *>(ECOfindNVObject(eci->mOmnisInstance, copyInfo->mDestinationObject));
         if (destObj == nullptr) {
            destObj = new CMQTT(reinterpret_cast<qobjinst>(copyInfo->mDestinationObject), srcObject);
            ECOinsertNVObject(eci->mOmnisInstance, copyInfo->mDestinationObject, reinterpret_cast<void *>(destObj));
         }
         else {
            destObj->setObject(reinterpret_cast<qobjinst>(copyInfo->mDestinationObject), srcObject);
         }
         return qtrue;
      }
      return qfalse;
   }

   case ECM_GETMETHODNAME:
      if (eci->mCompId == cObject_MQTT) {
         return ECOreturnMethods(gInstLib, eci, &oMQTTFunctions[0], cFunctionsCount);
      }
      return qtrue;

   case ECM_METHODCALL: {
      void *object = ECOfindNVObject(eci->mOmnisInstance, lParam);
      if (object) {
         if (eci->mCompId == cObject_MQTT) {
            CMQTT *mqtt = reinterpret_cast<CMQTT *>(object);
            return mqtt->methodCall(eci);
         }
      }
      return qfalse;
   }

   case ECM_CONSTPREFIX: {
      EXTfldval exfldval;
      EXTParamInfo *newparam = ECOaddParam(eci, &exfldval);
      str80 conPrefix;
      RESloadString(gInstLib, RES_CONST_PREFIX, conPrefix);
      exfldval.setChar(conPrefix);
      return qtrue;
   }

   case ECM_GETCONSTNAME:
      return ECOreturnConstants(gInstLib, eci, RES_CONST_START, RES_CONST_END);

   case ECM_GETCOMPLIBINFO:
      return ECOreturnCompInfo(gInstLib, eci, LIB_RES_NAME, 0);

   case ECM_ISUNICODE:
      return qtrue;

   case ECM_GETVERSION:
      return ECOreturnVersion(VERSION_MAJOR, VERSION_MINOR);
   }

   return WNDdefWindowProc(hwnd, Msg, wParam, lParam, eci);
}

/*
** Constructor
*/
CMQTT::CMQTT(qobjinst pObjPtr) :
   mObjPtr(pObjPtr),
   timeout(10),
   qos(1),
   connected(false),
   client(nullptr),
   retained(false),
   connectTimeout(30),
   cleanStart(false),
   keepAliveInterval(60),
   sessionExpiryInterval(-1),
   messageExpiryInterval(-1),
   automaticReconnect(false)
{
}

/*
** Copy constructor
*/
CMQTT::CMQTT(qobjinst pObjPtr, const CMQTT *sourceObject)
{
   setObject(pObjPtr, sourceObject);
}

/*
** Copy object
*/
void CMQTT::setObject(qobjinst pObjPtr, const CMQTT *sourceObject)
{
   mObjPtr = sourceObject->mObjPtr;
   address = sourceObject->address;
   timeout = sourceObject->timeout;
   clientID = sourceObject->clientID;
   topic = sourceObject->topic;
   qos = sourceObject->qos;
   username = sourceObject->username;
   password = sourceObject->password;
   keepAliveInterval = sourceObject->keepAliveInterval;
   cleanStart = sourceObject->cleanStart;
   retained = sourceObject->retained;
   connectTimeout = sourceObject->connectTimeout;
   sessionExpiryInterval = sourceObject->sessionExpiryInterval;
   messageExpiryInterval = sourceObject->messageExpiryInterval;
   automaticReconnect = sourceObject->automaticReconnect;

   errorMessage = "";
   connected = false;
   client = nullptr;
};

/*
** Destructor
*/
CMQTT::~CMQTT()
{
   disconnect(nullptr);
}

/*
** Entry method for calling object's methods
*/
qbool CMQTT::methodCall(EXTCompInfo *pEci)
{
   qlong funcId = ECOgetId(pEci);

   if (funcId == cGetErrorMessageFunction) {
      getErrorMessage(pEci);
      return qtrue;
   }

   EXTfldval rtnVal;
   qbool rtnCode = qfalse;
   errorMessage = "";

   switch (funcId) {
   case cSetAddressFunction:
      rtnCode = setAddress(pEci);
      break;
   case cSetTimeoutFunction:
      rtnCode = setTimeout(pEci);
      break;
   case cSetClientIDFunction:
      rtnCode = setClientID(pEci);
      break;
   case cSetTopicFunction:
      rtnCode = setTopic(pEci);
      break;
   case cSetQoSFunction:
      rtnCode = setQoS(pEci);
      break;
   case cSetUsernameFunction:
      rtnCode = setUsername(pEci);
      break;
   case cSetPasswordFunction:
      rtnCode = setPassword(pEci);
      break;
   case cSetKeepAliveIntervalFunction:
      rtnCode = setKeepAliveInterval(pEci);
      break;
   case cSetCleanStartFunction:
      rtnCode = setCleanStart(pEci);
      break;
   case cSetRetainedFunction:
      rtnCode = setRetained(pEci);
      break;
   case cSetConnectTimeoutFunction:
      rtnCode = setConnectTimeout(pEci);
      break;
   case cSetSessionExpiryIntervalFunction:
      rtnCode = setSessionExpiryInterval(pEci);
      break;
   case cSetMessageExpiryIntervalFunction:
      rtnCode = setMessageExpiryInterval(pEci);
      break;
   case cSetAutomaticReconnectFunction:
      rtnCode = setAutomaticReconnect(pEci);
      break;
   case cConnectFunction:
      rtnCode = connect(pEci);
      break;
   case cDisconnectFunction:
      rtnCode = disconnect(pEci);
      break;
   case cPublishFunction:
      rtnCode = publish(pEci);
      break;
   case cGetIsConnectedFunction:
      getIsConnected(pEci);
      return qtrue;
   }

   rtnVal.setBool((rtnCode == qtrue) ? preBoolTrue : preBoolFalse);
   ECOaddParam(pEci, &rtnVal);
   return rtnCode;
}

/*
** Returns the error message generated in the last function called.
*/
void CMQTT::getErrorMessage(EXTCompInfo *pEci) const
{
   EXTfldval result;
   stringToEXTfldval(errorMessage, result);
   ECOaddParam(pEci, &result);
}

/*
** Returns if te client is connected or not
*/
void CMQTT::getIsConnected(EXTCompInfo *pEci)
{
   bool isConnected = false;

   if (client != nullptr) {
      isConnected = client->is_connected();
   }

   EXTfldval result;
   boolToEXTfldval(isConnected, result);
   ECOaddParam(pEci, &result);
}

/*
** Set the address of the mqtt broker
*/
qbool CMQTT::setAddress(EXTCompInfo *pEci)
{
   if (!getStringFromEXTCompInfo(pEci, 1, address)) {
      errorMessage = "Incorrect number of parameters.";
      return qfalse;
   }
   return qtrue;
}

/*
** Set the timeout value
*/
qbool CMQTT::setTimeout(EXTCompInfo *pEci)
{

   if (!getIntFromEXTCompInfo(pEci, 1, timeout)) {
      errorMessage = "Incorrect number of parameters.";
      return qfalse;
   }
   return qtrue;
}

/*
** Set the identification of the client
*/
qbool CMQTT::setClientID(EXTCompInfo *pEci)
{
   if (!getStringFromEXTCompInfo(pEci, 1, clientID)) {
      errorMessage = "Incorrect number of parameters.";
      return qfalse;
   }
   return qtrue;
}

/*
** Set the topic name
*/
qbool CMQTT::setTopic(EXTCompInfo *pEci)
{
   if (!getStringFromEXTCompInfo(pEci, 1, topic)) {
      errorMessage = "Incorrect number of parameters.";
      return qfalse;
   }
   return qtrue;
}

/*
** Set the quality of service
*/
qbool CMQTT::setQoS(EXTCompInfo *pEci)
{
   if (!getIntFromEXTCompInfo(pEci, 1, qos)) {
      errorMessage = "Incorrect number of parameters.";
      return qfalse;
   }
   return qtrue;
}

/*
** Set the name of the user
*/
qbool CMQTT::setUsername(EXTCompInfo *pEci)
{
   if (!getStringFromEXTCompInfo(pEci, 1, username)) {
      errorMessage = "Incorrect number of parameters.";
      return qfalse;
   }
   return qtrue;
}

/*
** Set the password
*/
qbool CMQTT::setPassword(EXTCompInfo *pEci)
{
   if (!getStringFromEXTCompInfo(pEci, 1, password)) {
      errorMessage = "Incorrect number of parameters.";
      return qfalse;
   }
   return qtrue;
}

/*
** Set the keep interval alive
*/
qbool CMQTT::setKeepAliveInterval(EXTCompInfo *pEci)
{
   if (!getIntFromEXTCompInfo(pEci, 1, keepAliveInterval)) {
      errorMessage = "Incorrect number of parameters.";
      return qfalse;
   }
   return qtrue;
}

/*
** Set the clear start
*/
qbool CMQTT::setCleanStart(EXTCompInfo *pEci)
{
   if (!getBoolFromEXTCompInfo(pEci, 1, cleanStart)) {
      errorMessage = "Incorrect number of parameters.";
      return qfalse;
   }
   return qtrue;
}

/*
** Set the retained property
*/
qbool CMQTT::setRetained(EXTCompInfo *pEci)
{
   if (!getBoolFromEXTCompInfo(pEci, 1, retained)) {
      errorMessage = "Incorrect number of parameters.";
      return qfalse;
   }
   return qtrue;
}

/*
** Set the connection timeout value
*/
qbool CMQTT::setConnectTimeout(EXTCompInfo *pEci)
{

   if (!getIntFromEXTCompInfo(pEci, 1, connectTimeout)) {
      errorMessage = "Incorrect number of parameters.";
      return qfalse;
   }
   return qtrue;
}

/*
** Set the session expiry interval
*/
qbool CMQTT::setSessionExpiryInterval(EXTCompInfo *pEci)
{

   if (!getIntFromEXTCompInfo(pEci, 1, sessionExpiryInterval)) {
      errorMessage = "Incorrect number of parameters.";
      return qfalse;
   }
   return qtrue;
}

/*
** Set the message expiry interval
*/
qbool CMQTT::setMessageExpiryInterval(EXTCompInfo *pEci)
{

   if (!getIntFromEXTCompInfo(pEci, 1, messageExpiryInterval)) {
      errorMessage = "Incorrect number of parameters.";
      return qfalse;
   }
   return qtrue;
}

/*
** Set the automatic reconnect property
*/
qbool CMQTT::setAutomaticReconnect(EXTCompInfo *pEci)
{
   if (!getBoolFromEXTCompInfo(pEci, 1, automaticReconnect)) {
      errorMessage = "Incorrect number of parameters.";
      return qfalse;
   }
   return qtrue;
}

/*
** Connects to the server
*/
qbool CMQTT::connect(EXTCompInfo *pEci)
{
   if (connected)
      return qtrue;

   if (client != nullptr) {
      disconnect(nullptr);
   }

   client = new mqtt::async_client(address, clientID);

   mqtt::properties connectProps;
   if (sessionExpiryInterval != -1) {
      connectProps.add(mqtt::property(mqtt::property::SESSION_EXPIRY_INTERVAL, sessionExpiryInterval));
   }

   mqtt::connect_options connOpts;
   connOpts.set_mqtt_version(MQTTVERSION_5);
   connOpts.set_clean_start(cleanStart);
   connOpts.set_user_name(username);
   connOpts.set_password(password);
   connOpts.set_keep_alive_interval(keepAliveInterval);
   connOpts.set_connect_timeout(connectTimeout);
   connOpts.set_automatic_reconnect(automaticReconnect);
   connOpts.set_properties(connectProps);

   try {
      mqtt::token_ptr token = client->connect(connOpts);
      if (!token->wait_for(std::chrono::seconds(connectTimeout))) {
         throw new mqtt::exception(mqtt::UNSPECIFIED_ERROR, std::string("Connection not established after ") + std::to_string(connectTimeout) + " seconds");
      }
      else if (token->get_return_code() != mqtt::SUCCESS) {
         throw new mqtt::exception(token->get_return_code(), token->get_error_message());
      }
   }
   catch (const mqtt::exception &ex) {
      errorMessage = ex.what();
      return qfalse;
   }

   connected = true;
   return qtrue;
}

/*
** Disconnects from the server
*/
qbool CMQTT::disconnect(EXTCompInfo *pEci)
{
   if (connected) {
      if (client != nullptr) {
         try {
            mqtt::disconnect_options disc;
            disc.set_reason_code(mqtt::NORMAL_DISCONNECTION);
            disc.set_timeout(std::chrono::seconds(timeout));
            mqtt::token_ptr token = client->disconnect(disc);
            if (!token->wait_for(std::chrono::seconds(timeout))) {
               throw new mqtt::exception(mqtt::UNSPECIFIED_ERROR, std::string("Connection not disconnected after ") + std::to_string(timeout) + " seconds");
            }
            else if (token->get_return_code() != mqtt::SUCCESS) {
               throw new mqtt::exception(token->get_return_code(), token->get_error_message());
            }
         }
         catch (const mqtt::exception &ex) {
            errorMessage = ex.what();
            return qfalse;
         }

         delete client;
         client = nullptr;
      }

      connected = false;
   }

   return qtrue;
}

/*
** Publishes one message
*/
qbool CMQTT::publish(EXTCompInfo *pEci)
{
   if (!connected) {
      errorMessage = "Connection not open";
      return qfalse;
   }

   std::string message;
   if (!getStringFromEXTCompInfo(pEci, 1, message)) {
      errorMessage = "Parameter 'message' not provided.";
      return qfalse;
   }

   try {
      mqtt::properties props;
      if (messageExpiryInterval != -1) {
         props.add(mqtt::property(mqtt::property::MESSAGE_EXPIRY_INTERVAL, messageExpiryInterval));
      }

      mqtt::message_ptr mqttMessage = mqtt::make_message(topic, message, qos, retained);

      mqtt::const_delivery_token_ptr token = client->publish(mqttMessage);
      if (!token->wait_for(std::chrono::seconds(timeout))) {
         throw new mqtt::exception(mqtt::UNSPECIFIED_ERROR, std::string("Message not deflivered after ") + std::to_string(timeout) + " seconds");
      }
      else if (token->get_return_code() != mqtt::SUCCESS) {
         throw new mqtt::exception(token->get_return_code(), token->get_error_message());
      }
   }
   catch (const mqtt::exception &ex) {
      errorMessage = ex.what();
      return qfalse;
   }

   return qtrue;
}
