#include <QtTest>
#include <QJsonObject>
#include <QDebug>

// add necessary includes here
#include "../Client/serverstatusmessage.h"
#include "../Client/useridnotification.h"
#include "../Client/usermessage.h"

class JsonTests : public QObject
{
    Q_OBJECT

public:
    JsonTests();
    ~JsonTests();

private slots:
    void test_case1();
    void test_case2();
    void test_case3();
};

JsonTests::JsonTests() {}

JsonTests::~JsonTests() {}

void JsonTests::test_case1() {
    QJsonObject obj;
    obj["StatusInfo"] = "Test";

    ServerStatusMessage msg;

    msg.fromJson(obj);
    qDebug() << msg.toJson();
    qDebug() << obj;
    QVERIFY(obj == msg.toJson());
}

void JsonTests::test_case2() {
    QJsonObject obj;
    obj["ID"] = 6;

    UserIDNotification msg;

    msg.fromJson(obj);
    qDebug() << msg.toJson();
    qDebug() << obj;
    QVERIFY(obj == msg.toJson());
}

void JsonTests::test_case3() {
    QJsonObject obj;
    obj["Content"] = "Test";

    UserMessage msg;

    msg.fromJson(obj);
    qDebug() << msg.toJson();
    qDebug() << obj;
    QVERIFY(obj == msg.toJson());
}
QTEST_APPLESS_MAIN(JsonTests)

#include "tst_jsontests.moc"
