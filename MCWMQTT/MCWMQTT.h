#ifndef _MCW_MQTT_H
#define _MCW_MQTT_H

#include <mqtt/client.h>
#include <extcomp.he>

const qshort LIB_RES_NAME = 1000;
const qlong RES_CONST_PREFIX = 19999;
const qlong RES_CONST_START = 20000;
const qlong RES_CONST_END = 20002;

const qshort VERSION_MAJOR = 1;
const qshort VERSION_MINOR = 0;

const qshort cObject_MQTT = 1;

const qlong cSetAddressFunction = 1;
const qlong cSetTimeoutFunction = 2;
const qlong cSetClientIDFunction = 3;
const qlong cSetTopicFunction = 4;
const qlong cSetQoSFunction = 5;
const qlong cSetUsernameFunction = 6;
const qlong cSetPasswordFunction = 7;
const qlong cSetKeepAliveIntervalFunction = 8;
const qlong cSetCleanStartFunction = 9;
const qlong cConnectFunction = 10;
const qlong cDisconnectFunction = 11;
const qlong cPublishFunction = 12;
const qlong cSetRetainedFunction = 13;
const qlong cSetConnectTimeoutFunction = 14;
const qlong cSetSessionExpiryIntervalFunction = 15;
const qlong cSetMessageExpiryIntervalFunction = 16;
const qlong cSetAutomaticReconnectFunction = 17;
const qlong cGetErrorMessageFunction = 18;
const qlong cGetIsConnectedFunction = 19;

const qlong kMQTTQoS0 = 0;
const qlong kMQTTQoS1 = 1;
const qlong kMQTTQoS2 = 2;

class CMQTT
{
private:
    std::string errorMessage;
    std::string address;
    int timeout;
    int connectTimeout;
    std::string clientID;
    std::string topic;
    int qos;
    std::string username;
    std::string password;
    int keepAliveInterval;
    int sessionExpiryInterval;
    int messageExpiryInterval;
    bool cleanStart;
    bool connected;
    bool retained;
    bool automaticReconnect;

    mqtt::async_client *client;

public:
    qobjinst mObjPtr;

public:
    CMQTT(qobjinst pObjPtr);
    CMQTT(qobjinst pObjPtr, const CMQTT*src);
    ~CMQTT();
    void setObject(qobjinst pObjPtr, const CMQTT*src);

    qbool methodCall(EXTCompInfo *pEci);
    qbool setAddress(EXTCompInfo *pEci);
    qbool setTimeout(EXTCompInfo *pEci);
    qbool setClientID(EXTCompInfo *pEci);
    qbool setTopic(EXTCompInfo *pEci);
    qbool setQoS(EXTCompInfo *pEci);
    qbool setKeepAliveInterval(EXTCompInfo *pEci);
    qbool setCleanStart(EXTCompInfo *pEci);
    qbool setUsername(EXTCompInfo *pEci);
    qbool setPassword(EXTCompInfo *pEci);
    qbool setRetained(EXTCompInfo* pEci);
    qbool setConnectTimeout(EXTCompInfo* pEci);
    qbool setSessionExpiryInterval(EXTCompInfo *pEci);
    qbool setMessageExpiryInterval(EXTCompInfo *pEci);
    qbool setAutomaticReconnect(EXTCompInfo *pEci);
    void getIsConnected(EXTCompInfo *pEci);
    void getErrorMessage(EXTCompInfo *pEci) const;

    qbool connect(EXTCompInfo *pEci);
    qbool disconnect(EXTCompInfo *pEci);
    qbool publish(EXTCompInfo *pEci);

};

#endif