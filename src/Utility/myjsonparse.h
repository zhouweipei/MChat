#ifndef MYJSONPARSE_H
#define MYJSONPARSE_H
#include <QJsonDocument>

class ItemInfo;
class FriendGroupList;
class MyJsonParse
{
public :
    MyJsonParse(const QJsonDocument &doc);
    ~MyJsonParse();

    void setJsonDocument(const QJsonDocument &doc);
    QJsonDocument jsonDocument() const;

public:
    ItemInfo* userInfo();
    void createFriend(FriendGroupList *friendGroupList, QMap<QString, ItemInfo *> *friendList);
    bool updateInfo(ItemInfo *info);

private:
    QJsonDocument m_jsonDoc;
};

#endif
