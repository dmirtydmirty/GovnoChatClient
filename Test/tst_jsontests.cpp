#include <QtTest>
#include <QJsonObject>
#include <QDebug>
#include <QSharedPointer>

// add necessary includes here
#include "../Client/serverstatusmessage.h"
#include "../Client/useridnotification.h"
#include "../Client/usermessage.h"
#include "../Client/packet.h"

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
    void test_case4();
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

void JsonTests::test_case4()
{
    QJsonObject obj;
    obj["StatusInfo"] = "Test";

    QSharedPointer<ServerStatusMessage> msg(new ServerStatusMessage);

    msg->fromJson(obj);

    Packet p1(msg, MessageType::SERVER_STATUS_MESSAGE, 0);
    Packet p2(p1.pack());


    qDebug() << p1.pack();
    qDebug() << p2.pack();

    QVERIFY(p1.get_sender() == p2.get_sender());
    QVERIFY(p1.get_type() == p2.get_type());
    QVERIFY(p1.pack() == p2.pack());

}
QTEST_APPLESS_MAIN(JsonTests)

#include "tst_jsontests.moc"
