﻿#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "chatmanager.h"
#include "protocol.h"

#include <QObject>
#include <QPointer>

namespace NetworkMode
{
    Q_NAMESPACE

    enum Mode
    {
        Internet = 0,   //互联网
        LocalInternet   //局域网
    };

    Q_ENUMS(Mode)
}

class ChatMessage;
class DatabaseManager;
class FriendGroup;
class FriendInfo;
class ItemInfo;
class JsonParser;
class TcpManager;
class UdpManager;
class NetworkManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(NetworkMode::Mode mode READ mode WRITE setMode NOTIFY modeChanged)

public:
    static NetworkManager* instance();
    ~NetworkManager();

    NetworkMode::Mode mode() const { return m_mode; }
    void setMode(NetworkMode::Mode mode);

    ItemInfo* getUserInfo();
    void checkLoginInfo();
    void createFriend(FriendGroup *FriendGroup, QMap<QString, ItemInfo *> *friendList);

    //用于连接服务器
    Q_INVOKABLE void connectServer();
    //用于取消登陆(终止连接)
    Q_INVOKABLE void cancelLogin();
    //用于更新用户信息
    Q_INVOKABLE void updateInfomation();
    //用于注册新账户
    Q_INVOKABLE void registerUser(const QString &json);
    //发送获取指定用户信息
    Q_INVOKABLE void requestUserInfo(const QString &username);
    //发送添加好友的请求
    Q_INVOKABLE void requestAddFriend(const QString &username);
    //发送接受好友请求
    Q_INVOKABLE void acceptFriendRequest(const QString &username);
    //发送拒绝好友请求
    Q_INVOKABLE void rejectFriendRequest(const QString &username);
    //发送状态改变的消息
    Q_INVOKABLE void sendStateChange(Chat::ChatStatus status);
    //发送聊天的消息
    Q_INVOKABLE void sendChatMessage(msg_t type, const QString &receiver, ChatMessage *chatMessage);

signals:
    void modeChanged();
    void loginError(const QString &error);
    void loginFinshed(bool ok);
    void hasRegister(const QString &result);
    void hasSearchResult(FriendInfo *info);
    void hasFriendRequest(const QString &username);
    void hasNewShake(const QString &sender);
    void hasNewText(const QString &sender, const QString &message);

public slots:
    void onLogined(bool ok);
    void onInfoGot(const QByteArray &infoJson);

private slots:
    void disposeNewMessage(const QString &sender, msg_t type, const QByteArray &data);

private:
    NetworkManager(QObject *parent = nullptr);

    QPointer<TcpManager> m_tcpManager;
    QPointer<UdpManager> m_udpManager;
    DatabaseManager *m_databaseManager;
    JsonParser *m_jsonParser;
    NetworkMode::Mode m_mode = NetworkMode::Internet;   //默认局域网
};

#endif
