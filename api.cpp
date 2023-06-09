#include "api.h"

API::API(const QString& sUrl,QObject *parent)
    : QObject{parent},url_s(sUrl),man_ptr(new QNetworkAccessManager(this)),m_isAvailable(true)
{
    data = new QByteArray();
    //connect(reply,&QNetworkReply::finished,this,&API::getData);
}

API::~API()
{
    delete man_ptr;
}

void API::Register(const QString &uname, const QString &pass)
{
    // http://api.barafardayebehtar.ml:8080/signup?username=sara&password=1234&firstname=sara&lastname=baradaran
    if(m_isAvailable)
    {
        m_isAvailable = false;
        QString temp = url_s+"/signup?username="+uname+"&password="+pass;
        reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
        connect(reply,&QNetworkReply::finished,this,&API::RegisterResponder);
    }
    else
    {
        qDebug() << "API::Register => API is not available";
    }
}

void API::Login(const QString &uname, const QString &pass)
{
    if(m_isAvailable)
    {
        m_isAvailable = false;
        QString temp = url_s+"/login?username="+uname+"&password="+pass;
        reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
        connect(reply,&QNetworkReply::finished,this,&API::LoginResponder);
    }
    else
    {
        qDebug()<< "API::Login => API is not available";
    }
}

void API::Logout(const QString &uname, const QString &pass)
{
    //if(m_isAvailable)
  //  {
     //   m_isAvailable = false;
        QString temp = url_s + "/logout?username="+uname+"&password="+pass;
        reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
        connect(reply,&QNetworkReply::finished,this,&API::LogoutResponder);
 //   }
  //  else{
      //  qDebug()<< "API::Logout => API is not available";
   // }
}

void API::SendMessageToUser(const QString &token,const QString& dst,const QString& body)
{
    /*
     *  /sendmessageuser?token=7a3c48f7c7939b7269d01443a431825f&dst=ali&body=hi
    */
    if(m_isAvailable)
    {
        m_isAvailable =false;
        QString temp = url_s +"/sendmessageuser?token="+token+"&dst="+dst+"&body="+body;
        reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
        connect(reply,&QNetworkReply::finished,this,&API::SendMessageToUserResponder);
    }
    else{
        qDebug()<< "API::SendMessageToUser => API is not available";
    }
}

void API::sendMessageToGroup(const QString &token, const QString& dst,const QString& body)
{
    /*
     *  /sendmessagegroup?token=7a3c48f7c7939b7269d01443a431825f&dst=ap&body=hello%20all
    */
    if(m_isAvailable){
        m_isAvailable =false;
        QString temp = url_s +"/sendmessagegroup?token="+token+"&dst="+dst+"&body="+body;
        reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
        connect(reply,&QNetworkReply::finished,this,&API::sendMessageToGroupResponder);
    }
    else{
        qDebug()<< "API::sendMessageToGroup => API is not available";
    }
}

void API::sendMessageToChannel(const QString &token, const QString &dst, const QString &body)
{
    /*
         /sendmessagechannel?token=7a3c48f7c7939b7269d01443a431825f&dst=mychannel&body=hello%20all
    */
    if(m_isAvailable){
        m_isAvailable = false;
        QString temp = url_s +"/sendmessagechannel?token="+token+"&dst="+dst+"&body="+body;
        reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
        connect(reply,&QNetworkReply::finished,this,&API::sendMessageToChannelResponder);
    }else
    {
        qDebug() << "API::getMsgUser => API is not available";
    }
}


void API::createGroup(const QString &token, const QString &groupName)
{
    /*
     * /creategroup?token=7a3c48f7c7939b7269d01443a431825f&group_name=G1&group_title=Group1
     */
    if(m_isAvailable){
        m_isAvailable = false;
        QString temp = url_s + "/creategroup?token="+token+"&group_name="+groupName;
        reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
        connect(reply,&QNetworkReply::finished,this,&API::createGroupResponder);
    }else
    {
        qDebug() << "API::getMsgUser => API is not available";
    }
}

void API::createChannel(const QString &token, const QString &channelName)
{
    /*
     * /createchannel?token=7a3c48f7c7939b7269d01443a431825f&channel_name=mychannel&channel_title=Channel1
     */
    if(m_isAvailable){
        m_isAvailable = false;
        QString temp = url_s + "/createchannel?token="+token+"&channel_name="+channelName;
        reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
        connect(reply,&QNetworkReply::finished,this,&API::createChannelResponder);
    }else
    {
        qDebug() << "API::getMsgUser => API is not available";
    }
}

void API::joinGroup(const QString &token, const QString &gruopName)
{
    /*
  * /joingroup?token=7a3c48f7c7939b7269d01443a431825f&group_name=ap
  */
    if(m_isAvailable){
        m_isAvailable = false;
        QString temp = url_s + "/joingroup?token="+token+"&group_name="+gruopName;
        reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
        connect(reply,&QNetworkReply::finished,this,&API::joinGroupResponder);
    }else
    {
        qDebug() << "API::getMsgUser => API is not available";
    }

}

void API::joinChannel(const QString &token, const QString &channelName)
{
    /*
  * /joinchannel?token=7a3c48f7c7939b7269d01443a431825f&channel_name=aplab
  */
    if(m_isAvailable){
        m_isAvailable = false;
        QString temp = url_s + "/joinchannel?token="+token+"&channel_name="+channelName;
        reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
        connect(reply,&QNetworkReply::finished,this,&API::joinChannelResponder);
    }
    else
    {
        qDebug() << "API::getMsgUser => API is not available";
    }

}

void API::getMsgUser(const QString &token, const QString &dst)
{
    if(m_isAvailable){
        m_isAvailable = false;
        QString temp = url_s + "/getuserchats?token=" + token + "&dst=" + dst;
        reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
        connect(reply,&QNetworkReply::finished,this,&API::getMsgUserResponder);
    }
    else
    {
        qDebug() << "API::getMsgUser => API is not available";
    }
}

void API::getMsgGroup(const QString &token, const QString &dst)
{
    if(m_isAvailable){
        m_isAvailable = false;
        QString temp = url_s + "/getgroupchats?token=" + token + "&dst=" + dst;
        reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
        connect(reply,&QNetworkReply::finished,this,&API::getMsgGroupResponder);
    }
    else
    {
        qDebug() << "API::getMsgGroup => API is not available";
    }
}

void API::getMsgChannel(const QString &token, const QString &dst)
{
    if(m_isAvailable){
        m_isAvailable = false;
        QString temp = url_s + "/getchannelchats?token=" + token + "&dst=" + dst;
        reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
        connect(reply,&QNetworkReply::finished,this,&API::getMsgChannelResponder);
    }
    else
    {
        qDebug() << "API::getMsgChannel => API is not available";
    }
}

void API::getGroupList(const QString &token)
{
    /*
     * getgrouplist?token=7a3c48f7c7939b7269d01443a431825f
     */
    if(m_isAvailable){
        m_isAvailable = false;
        QString temp = url_s + "/getgrouplist?token=" + token;
        reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
        connect(reply,&QNetworkReply::finished,this,&API::getGroupListResponder);
    }
    else
    {
        qDebug() << "API::getGroupList => API is not available";
    }
}

void API::getChannelList(const QString &token)
{
    /*
     * getchannellist?token=7a3c48f7c7939b7269d01443a431825f
     */
    if(m_isAvailable){
        m_isAvailable = false;
        QString temp = url_s + "/getchannellist?token=" + token;
        reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
        connect(reply,&QNetworkReply::finished,this,&API::getChannelListResponder);
    }
    else
    {
        qDebug() << "API::getChannelList => API is not available";
    }
}

void API::getUserList(const QString &token)
{
    /*
     * getuserlist?token=7a3c48f7c7939b7269d01443a431825f
     */
    if(m_isAvailable){
        m_isAvailable = false;
        QString temp = url_s + "/getuserlist?token=" + token;
        reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
        connect(reply,&QNetworkReply::finished,this,&API::getUserListResponder);
    }
    else
    {
        qDebug() << "API::getUserList => API is not available";
    }
}

QByteArray *API::getResponse()
{
    return data;
}

void API::RegisterResponder()
{
    // If the request was successful
    if (reply->error() == QNetworkReply::NoError) {
        //read the response
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        QJsonObject jObj = jDoc.object();
        QString respond_code =  jObj.value("code").toString();
        QString respond_message =jObj.value("message").toString();
        if(respond_code == "200")
        {
            emit SuccessOnRegister();
        }
        else
        {
            emit FailureOnRegister(respond_message);
        }


    } else {
        // If there was an error, display the error message
        // qDebug() << "Error:" << reply->errorString();
        data = NULL;
        emit FailureOnRegister(reply->errorString());
    }
    reply->deleteLater();
    m_isAvailable = true;
}

void API::LoginResponder()
{
    if (reply->error() == QNetworkReply::NoError) {
        //read the response
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        QJsonObject jObj = jDoc.object();
        QString respond_code =  jObj.value("code").toString();
        QString respond_message =jObj.value("message").toString();
        QString respond_token = jObj.value("token").toString();
        if(respond_code == "200")
        {
            emit SuccessOnLogin(respond_token);
        }
        else
        {
            emit FailureOnLogin(respond_message);
        }
    }
    else {
        // If there was an error, display the error message
        // qDebug() << "Error:" << reply->errorString();
        data = NULL;
        emit FailureOnLogin(reply->errorString());
    }
    reply->deleteLater();
    m_isAvailable = true;
}

void API::LogoutResponder()
{
    if (reply->error() == QNetworkReply::NoError) {
        //read the response
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        QJsonObject jObj = jDoc.object();
        QString respond_code =  jObj.value("code").toString();
        QString respond_message =jObj.value("message").toString();

        if(respond_code == "200")
        {
            emit SuccessOnLogout();
        }
        else
        {
            emit FailureOnLogout(respond_message);
        }
    }
    else {
        // If there was an error, display the error message
        // qDebug() << "Error:" << reply->errorString();
        data = NULL;
        emit FailureOnLogout(reply->errorString());
    }
    reply->deleteLater();
    //m_isAvailable = true;
}

void API::createGroupResponder()
{
    if (reply->error() == QNetworkReply::NoError) {
        //read the response
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        QJsonObject jObj = jDoc.object();
        QString respond_code =  jObj.value("code").toString();
        QString respond_message =jObj.value("message").toString();

        if(respond_code == "200")
        {
            emit SuccessOnCreateGroup();
        }
        else
        {
            emit FailureOnCreateGroup(respond_message);
        }
    }
    else {
        // If there was an error, display the error message
        // qDebug() << "Error:" << reply->errorString();
        data = NULL;
        emit FailureOnCreateGroup(reply->errorString());
    }
    reply->deleteLater();
    m_isAvailable = true;
}

void API::createChannelResponder()
{
    if (reply->error() == QNetworkReply::NoError) {
        //read the response
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        QJsonObject jObj = jDoc.object();
        QString respond_code =  jObj.value("code").toString();
        QString respond_message =jObj.value("message").toString();

        if(respond_code == "200")
        {
            emit SuccessOnCreateChannel();
        }
        else
        {
            emit FailureOnCreateChannel(respond_message);
        }
    }
    else {
        // If there was an error, display the error message
        // qDebug() << "Error:" << reply->errorString();
        data = NULL;
        emit FailureOnCreateChannel(reply->errorString());
    }
    reply->deleteLater();
    m_isAvailable = true;
}

void API::getMsgUserResponder()
{
    if (reply->error() == QNetworkReply::NoError) {
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        if(jDoc.isObject())
        {
            QJsonObject jObj = jDoc.object();
            QString respond_code =  jObj.value("code").toString();
            QString respond_message =jObj.value("message").toString();
            if(respond_code == "200"){

                emit SuccessOnGetMsgUser(jDoc);
            }
            else {
                emit FailureOnGetMsgUser(respond_message);
            }
        }
        else {
            data = NULL;
            emit FailureOnGetMsgUser(reply->errorString());
        }
    }
    else
    {
        qDebug("getMsgUserResponde: jdoc is not a object\n");
    }
    reply->deleteLater();
    m_isAvailable = true;
}

void API::getMsgChannelResponder()
{
    if (reply->error() == QNetworkReply::NoError) {
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        if(jDoc.isObject())
        {
            QJsonObject jObj = jDoc.object();
            QString respond_code =  jObj.value("code").toString();
            QString respond_message =jObj.value("message").toString();
            if(respond_code == "200"){

                emit SuccessOnGetMsgChannel(jDoc);
            }
            else {
                emit FailureOnGetMsgChannel(respond_message);
            }
        }
        else {
            data = NULL;
            emit FailureOnGetMsgChannel(reply->errorString());
        }
    }
    else
    {
        qDebug("getMsgChannelResponde: jdoc is not a object\n");
    }
    reply->deleteLater();
    m_isAvailable = true;
}

void API::getMsgGroupResponder()
{
    if (reply->error() == QNetworkReply::NoError) {
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        if(jDoc.isObject())
        {
            QJsonObject jObj = jDoc.object();
            QString respond_code =  jObj.value("code").toString();
            QString respond_message =jObj.value("message").toString();
            if(respond_code == "200"){

                emit SuccessOnGetMsgGroup(jDoc);
            }
            else {
                emit FailureOnGetMsgGroup(respond_message);
            }
        }
        else {
            data = NULL;
            emit FailureOnGetMsgGroup(reply->errorString());
        }
    }
    else
    {
        qDebug("getMsgGroupResponde: jdoc is not a object\n");
    }
    reply->deleteLater();
    m_isAvailable = true;
}

void API::getGroupListResponder()
{
    if (reply->error() == QNetworkReply::NoError) {
        //read the response
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        QJsonObject jObj = jDoc.object();
        QString respond_code =  jObj.value("code").toString();
        QString respond_message =jObj.value("message").toString();

        if(respond_code == "200")
        {
            emit SuccessOnGetGroupList(jDoc);
        }
        else
        {
            emit FailureOnGetGroupList(respond_message);
        }
    }
    else {
        // If there was an error, display the error message
        // qDebug() << "Error:" << reply->errorString();
        data = NULL;
        emit FailureOnGetGroupList(reply->errorString());
    }
    reply->deleteLater();
    m_isAvailable =true;
}

void API::getChannelListResponder()
{
    if (reply->error() == QNetworkReply::NoError) {
        //read the response
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        QJsonObject jObj = jDoc.object();
        QString respond_code =  jObj.value("code").toString();
        QString respond_message =jObj.value("message").toString();

        if(respond_code == "200")
        {
            emit SuccessOnGetChannelList(jDoc);
        }
        else
        {
            emit FailureOnGetChannelList(respond_message);
        }
    }
    else {
        // If there was an error, display the error message
        // qDebug() << "Error:" << reply->errorString();
        data = NULL;
        emit FailureOnGetChannelList(reply->errorString());
    }
    reply->deleteLater();
    m_isAvailable =true;
}

void API::getUserListResponder()
{
    if (reply->error() == QNetworkReply::NoError) {
        //read the response
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        QJsonObject jObj = jDoc.object();
        QString respond_code =  jObj.value("code").toString();
        QString respond_message =jObj.value("message").toString();

        if(respond_code == "200")
        {
            emit SuccessOnGetUserList(jDoc);
        }
        else
        {
            emit FailureOnGetUserList(respond_message);
        }
    }
    else {
        // If there was an error, display the error message
        // qDebug() << "Error:" << reply->errorString();
        data = NULL;
        emit FailureOnGetUserList(reply->errorString());
    }
    reply->deleteLater();
    m_isAvailable =true;
}


void API::SendMessageToUserResponder()
{
    if (reply->error() == QNetworkReply::NoError) {
        //read the response
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        QJsonObject jObj = jDoc.object();
        QString respond_code =  jObj.value("code").toString();
        QString respond_message =jObj.value("message").toString();

        if(respond_code == "200")
        {
            emit SuccessOnSendMsgToUser();
        }
        else
        {
            emit FailureOnSendMsgToUser(respond_message);
        }
    }
    else {
        // If there was an error, display the error message
        // qDebug() << "Error:" << reply->errorString();
        data = NULL;
        emit FailureOnSendMsgToUser(reply->errorString());
    }
    reply->deleteLater();
    m_isAvailable =true;
}

void API::sendMessageToGroupResponder()
{
    qDebug("sendMessageToGroupResponder from API class\n");
    if (reply->error() == QNetworkReply::NoError) {
        //read the response
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        QJsonObject jObj = jDoc.object();
        QString respond_code =  jObj.value("code").toString();
        QString respond_message =jObj.value("message").toString();

        if(respond_code == "200")
        {
            emit SuccessOnSendMsgToGroup();
        }
        else
        {
            emit FailureOnSendMsgToGroup(respond_message);
        }
    }
    else {
        // If there was an error, display the error message
        // qDebug() << "Error:" << reply->errorString();
        data = NULL;
        emit FailureOnSendMsgToGroup(reply->errorString());
    }
    reply->deleteLater();
    m_isAvailable = true;
}

void API::sendMessageToChannelResponder()
{
    qDebug("sendMessageToChannelpResponder from API class\n");
    if (reply->error() == QNetworkReply::NoError) {
        //read the response
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        QJsonObject jObj = jDoc.object();
        QString respond_code =  jObj.value("code").toString();
        QString respond_message =jObj.value("message").toString();

        if(respond_code == "200")
        {
            emit SuccessOnSendMsgToChannel();
        }
        else
        {
            emit FailureOnSendMsgToChannel(respond_message);
        }
    }
    else {
        // If there was an error, display the error message
        // qDebug() << "Error:" << reply->errorString();
        data = NULL;
        emit FailureOnSendMsgToGroup(reply->errorString());
    }
    reply->deleteLater();
    m_isAvailable = true;
}

void API::joinGroupResponder()
{
    qDebug("joinGroupResponder from API class\n");
    if (reply->error() == QNetworkReply::NoError) {
        //read the response
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        QJsonObject jObj = jDoc.object();
        QString respond_code =  jObj.value("code").toString();
        QString respond_message =jObj.value("message").toString();

        if(respond_code == "200")
        {
            if(respond_message == "You are already Joined!")
            {
                emit FailureOnJoinGroup("You are already Joined!");
            }
            else{
                emit SuccessOnJoinGroup();
            }
        }
        else
        {
            emit FailureOnJoinGroup(respond_message);
        }
    }
    else {
        // If there was an error, display the error message
        // qDebug() << "Error:" << reply->errorString();
        data = NULL;
        emit FailureOnJoinGroup(reply->errorString());
    }
    reply->deleteLater();
    m_isAvailable = true;
}

void API::joinChannelResponder()
{
    qDebug("joinGroupResponder from API class\n");
    if (reply->error() == QNetworkReply::NoError) {
        //read the response
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        QJsonObject jObj = jDoc.object();
        QString respond_code =  jObj.value("code").toString();
        QString respond_message =jObj.value("message").toString();

        if(respond_code == "200")
        {
            if(respond_message == "You are already Joined!")
            {
                emit FailureOnJoinGroup("You are already Joined!");
            }
            else{
                emit SuccessOnJoinGroup();
            }

        }
        else
        {
            emit FailureOnJoinChannel(respond_message);
        }
    }
    else {
        // If there was an error, display the error message
        // qDebug() << "Error:" << reply->errorString();
        data = NULL;
        emit FailureOnJoinChannel(reply->errorString());
    }
    reply->deleteLater();
    m_isAvailable = true;
}



//void API::getData()
//{
//    if (reply->error() == QNetworkReply::NoError) {
//        // If the request was successful, read the response
//        *data = reply->readAll();
//        // qDebug() << "Response:" << *data;
//        emit Success(data);

//    } else {
//        // If there was an error, display the error message
//        // qDebug() << "Error:" << reply->errorString();
//        data = NULL;
//        emit Failure(reply);
//    }
//    reply->deleteLater();
//}

