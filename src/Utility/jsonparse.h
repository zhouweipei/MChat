#ifndef JSONPARSE_H
#define JSONPARSE_H

#include <QJsonDocument>

class FriendGroup;
class ItemInfo;
class JsonParser
{
public :
    JsonParser(const QJsonDocument &doc);
    ~JsonParser();

    void setJsonDocument(const QJsonDocument &doc);
    QJsonDocument jsonDocument() const;

public:
    ItemInfo* userInfo();
    void createFriend(FriendGroup *friendGroup, QMap<QString, ItemInfo *> *friendList);
    QByteArray infoToJson(ItemInfo *info);
    ItemInfo* jsonToInfo(const QByteArray &data);

private:
    QJsonDocument m_doc;
};

#endif //JSONPARSE_H
